#!/usr/bin/env python3
import os
import json
import re
from pathlib import Path
from mcp.server.fastmcp import FastMCP, Context
from openpilot.tools.lib.logreader import LogReader, probe_and_download_segments

# MCP server
mcp = FastMCP("bukapilot qlog Reader")

# Constants
SCRIPT_DIR = Path(__file__).resolve().parent
QLOG_JSON_DIR = SCRIPT_DIR / "qlog_json"
QLOG_JSON_DIR.mkdir(exist_ok=True)
# Max safe character limit for raw content per chunk
# To avoid having message exceeding the limit and gets truncated at the end
RAW_SAFE_LIMIT = 50_250

# Precompiled regex for cleaning raw field
_CLEAN_RAW_PATTERN = re.compile(r'(?:\\n|\\r|\\")+|\s+')
# Regex for finding timestamp of a message
_TIMESTAMP_PATTERN = re.compile(r'(timestamp\w*|\w*monotime\w*)\s*=\s*(\d+)', re.IGNORECASE)

def _clean_raw_field(raw) -> str:
  """Cleans raw message field"""
  return _CLEAN_RAW_PATTERN.sub(' ', str(raw)).strip()

def _decode_qlog_to_json(log_paths, file_name: str = None) -> str:
  """Decodes qlog file into structured JSON and saves it to QLOG_JSON_DIR"""
  messages = []
  append = messages.append
  for msg in LogReader(log_paths, sort_by_time=True, default_mode="q"):
    try:
      if (msg_type := msg.which()) and (raw_str := _clean_raw_field(getattr(msg, msg_type))):
        append({"type": msg_type, "raw": raw_str})
    except Exception as e:
      append({"type": "unknown", "raw": f"decode error: {e}"})
  json_path = QLOG_JSON_DIR / (file_name or f"bukapilot_qlog_{os.getpid()}.json")
  with open(json_path, "w", encoding="utf-8") as f:
    json.dump(messages, f, indent=2)
  return str(json_path)

def _generate_filename(dongle_id: str, drive_timestamp: str) -> str:
  """Generates a filename for a qlog JSON using dongle ID and drive timestamp"""
  return f"{dongle_id}---{drive_timestamp}---qlog.json"

def _list_json_files():
  """Lists all qlog JSON files in QLOG_JSON_DIR"""
  return [str(f) for f in QLOG_JSON_DIR.glob("*.json")]

def _delete_json_file(file_path: str) -> bool:
  """Deletes a specific qlog JSON file from QLOG_JSON_DIR"""
  try:
    os.remove(file_path)
    return True
  except OSError:
    return False

def _delete_all_json_files():
  """Deletes all qlog JSON files and removes QLOG_JSON_DIR if empty"""
  for f in QLOG_JSON_DIR.glob("*.json"):
    try: os.remove(f)
    except OSError: pass
  try: QLOG_JSON_DIR.rmdir()
  except OSError: pass

def _extract_car_model(messages):
  """Extracts carName and carFingerprint from carParams message"""
  for m in messages:
    if m.get("type") == "carParams" and (raw := m.get("raw")):
      match_name = re.search(r'carName\s*=\s*"?([^",)]+)"?', raw)
      match_fingerprint = re.search(r'carFingerprint\s*=\s*"?([^",)]+)"?', raw)
      return {
        "car_name": match_name.group(1) if match_name else None,
        "car_fingerprint": match_fingerprint.group(1) if match_fingerprint else None
      }
  return {"car_name": None, "car_fingerprint": None}

def _get_message_type_chunks(messages, message_type: str):
  """Splits messages of a given type into size-safe chunks with optional time range"""
  chunks, current_chunk, current_size, has_timestamp = [], [], 0, False
  for m in (m for m in messages if m.get("type") == message_type):
    if (msg_str := json.dumps(m, ensure_ascii=False)) and (msg_len := len(msg_str)) > RAW_SAFE_LIMIT:
      for i in range(0, msg_len, RAW_SAFE_LIMIT):
        chunks.append({
          "chunk_index": len(chunks) + 1,
          "size_chars": min(RAW_SAFE_LIMIT, msg_len - i),
          "time_range": None
        })
      continue
    if current_size + msg_len > RAW_SAFE_LIMIT:
      chunks.append({
        "chunk_index": len(chunks) + 1,
        "size_chars": current_size,
        "time_range": _get_time_range(current_chunk) if has_timestamp else None
      })
      current_chunk, current_size, has_timestamp = [], 0, False
    current_chunk.append(m)
    current_size += msg_len
    has_timestamp |= _find_timeval(m.get("raw", "")) is not None
  if current_chunk:
    chunks.append({
      "chunk_index": len(chunks) + 1,
      "size_chars": current_size,
      "time_range": _get_time_range(current_chunk) if has_timestamp else None
    })
  return chunks

def _find_timeval(raw):
  """Finds a valid timestamp or monotime value from a raw message string"""
  for match in _TIMESTAMP_PATTERN.finditer(raw):
    value = int(match.group(2))
    if value != 0:
      return value
  return None

_NS_TO_MIN = 1 / 1e9 / 60
def _get_time_range(messages):
  """Calculates time range in minutes from messages based on embedded timestamps"""
  timestamps = [ts for ts in (_find_timeval(m.get("raw", "")) for m in messages) if ts]
  if not timestamps:
    return None
  start_min = round(timestamps[0] * _NS_TO_MIN, 2)
  end_min = round(timestamps[-1] * _NS_TO_MIN, 2)
  return {"start_min": start_min, "end_min": end_min}

def _get_chunk_messages(messages, message_type: str, chunk_index: int):
  """Retrieves all messages in a specific chunk index for a given message type"""
  all_chunks, current_chunk, current_size = [], [], 0
  for m in (m for m in messages if m.get("type") == message_type):
    if (msg_str := json.dumps(m, ensure_ascii=False)) and (msg_len := len(msg_str)) > RAW_SAFE_LIMIT:
      for i in range(0, msg_len, RAW_SAFE_LIMIT):
        all_chunks.append([msg_str[i:i + RAW_SAFE_LIMIT]])
      continue
    if current_size + msg_len > RAW_SAFE_LIMIT:
      all_chunks.append(current_chunk)
      current_chunk, current_size = [], 0
    current_chunk.append(m)
    current_size += msg_len
  if current_chunk:
    all_chunks.append(current_chunk)
  return all_chunks[chunk_index - 1] if 1 <= chunk_index <= len(all_chunks) else []

@mcp.tool()
async def fetch_kommu_qlog_as_json(ctx: Context, dongle_id: str, drive_timestamp: str) -> dict:
  """Fetches a qlog from the Kommu server, decodes it, and stores the JSON in QLOG_JSON_DIR"""
  file_name = _generate_filename(dongle_id, drive_timestamp)
  json_path = QLOG_JSON_DIR / file_name
  if json_path.exists():
    return {"json_file": str(json_path), "cached": True}
  base_url = f"https://web.kommu.ai/depot/upload/{dongle_id}"
  try:
    log_paths = probe_and_download_segments(dongle_id, drive_timestamp, base_url)
    if not log_paths:
      return {"error": "No .qlog segments found on kommu server"}
    json_file = _decode_qlog_to_json(log_paths, file_name)
    for path in log_paths:
      try: os.remove(path)
      except OSError: pass
    return {"json_file": json_file, "cached": False}
  except Exception as e:
    await ctx.error(f"Failed to fetch/decode qlog: {e}")
    return {"error": str(e)}

@mcp.tool()
async def list_qlog_message_types(ctx: Context, json_path: str = None) -> dict:
  """Lists all message types and car info from a qlog JSON file in QLOG_JSON_DIR"""
  if not json_path:
    if not (files := sorted(_list_json_files(), key=os.path.getmtime, reverse=True)):
      return {"error": "No qlog JSON files found."}
    json_path = files[0]
  try:
    with open(json_path, "r", encoding="utf-8") as f:
      messages = json.load(f)
    type_counts = {}
    for m in messages:
      if (t := m.get("type", "unknown")):
        type_counts[t] = type_counts.get(t, 0) + 1
    return {
      "message_types": [{"type": t, "count": c} for t, c in type_counts.items()],
      "car_info": _extract_car_model(messages)
    }
  except Exception as e:
    await ctx.error(f"Failed to list message types: {e}")
    return {"error": str(e)}

@mcp.tool()
async def get_qlog_message_chunks(ctx: Context, message_type: str, json_path: str = None) -> dict:
  """Returns chunk metadata for a specific message type in a qlog JSON file in QLOG_JSON_DIR"""
  if not json_path:
    if not (files := sorted(_list_json_files(), key=os.path.getmtime, reverse=True)):
      return {"error": "No qlog JSON files found."}
    json_path = files[0]
  try:
    with open(json_path, "r", encoding="utf-8") as f:
      if not (messages := json.load(f)):
        return {"error": "Empty or invalid qlog JSON file."}
    chunks = _get_message_type_chunks(messages, message_type)
    return {"message_type": message_type, "chunk_count": len(chunks), "chunks": chunks}
  except Exception as e:
    return {"error": str(e)}

@mcp.tool()
async def get_qlog_message_chunk_content(ctx: Context, message_type: str, chunk_index: int, json_path: str = None) -> dict:
  """Retrieves the content of a specific message chunk from a qlog JSON file in QLOG_JSON_DIR"""
  if not json_path:
    if not (files := sorted(_list_json_files(), key=os.path.getmtime, reverse=True)):
      return {"error": "No qlog JSON files found."}
    json_path = files[0]
  try:
    with open(json_path, "r", encoding="utf-8") as f:
      messages = json.load(f)
    chunk_messages = _get_chunk_messages(messages, message_type, chunk_index)
    return {"chunk_index": chunk_index, "messages": chunk_messages, "count": len(chunk_messages)}
  except Exception as e:
    return {"error": str(e)}

@mcp.tool()
async def manage_qlog_json_files(ctx: Context, action: str, file_path: str = None) -> dict:
  """Manages qlog JSON files in QLOG_JSON_DIR, supporting list, delete, and delete_all actions"""
  try:
    if action == "list":
      return {"files": _list_json_files()}
    if action == "delete" and file_path:
      return {"deleted": _delete_json_file(file_path), "file": file_path}
    if action == "delete_all":
      _delete_all_json_files()
      return {"deleted_all": True}
    return {"error": "Invalid action or missing file_path for 'delete'."}
  except Exception as e:
    return {"error": str(e)}

@mcp.prompt()
def qlog_analysis_guidance() -> dict:
  return {
    "text": (
      "You are an expert AI assistant for **bukapilot** (an openpilot fork) qlog analysis.\n\n"
      "**Analysis Workflow:**\n"
      "1. **Acquire Logs**: Use `fetch_kommu_qlog_as_json` when a `dongle_id` and `drive_timestamp` are provided.\n"
      "2. **Identify Message Types**: Use `list_qlog_message_types` to get all available message types and car details. Where `json_path` is the full absolute path of the json file.\n"
      "3. **Chunk Planning**: Before analysing a message type, call `get_qlog_message_chunks` to learn the total chunks, their sizes, and time ranges.\n"
      "4. **Sequential Analysis**: For multiple chunks, process each chunk in order with `get_qlog_message_chunk_content`."
      "Summarise each chunk separately, then combine all summaries.\n"
      "5. **Time Ranges**: Report start and end times (in minutes) for each chunk if timestamps exist.\n"
      "6. **Cleanup**: After analysis, ask the user whether to clean up cached JSON files via `manage_qlog_json_files`.\n\n"
      "Ensure every chunk is processed — do not skip intermediate chunks."
    )
  }

@mcp.prompt()
def qlog_chunk_guidance() -> dict:
  return {
    "text": (
      "Chunk Analysis Guidance:\n"
      "- If there is only one chunk, analyse it directly.\n"
      "- For multiple chunks, analyse each chunk one by one, and combine all summaries at the end.\n"
      "- Mention how many chunks exist, their sizes, and time ranges if available.\n"
      "- Preserve all information from each message, never truncating.\n"
      "- Ensure intermediate chunks are not skipped during analysis."
    )
  }

@mcp.prompt()
def qlog_user_request_guidance() -> dict:
  return {
    "text": (
      "When a user requests a **full analysis of a message type**:\n"
      "- Use `get_qlog_message_chunks` to determine the total chunks. Where `json_path` is the full absolute path of the json file.\n"
      "- Analyse all chunks sequentially with `get_qlog_message_chunk_content`. Where `json_path` is the full absolute path of the json file.\n"
      "- Summarise each chunk and then merge these into a final summary.\n"
      "- Mention the start and end time ranges for each chunk (if timestamps exist).\n"
      "- After analysis, offer the option to clean up cached JSON files using `manage_qlog_json_files`."
    )
  }

@mcp.prompt()
def qlog_file_management_guidance() -> dict:
  return {
    "text": (
      "To manage cached qlog JSON files:\n"
      "- Call `manage_qlog_json_files` with `action='list'` to view all available files.\n"
      "- To delete a specific file, use `action='delete'` and provide the full `file_path`.\n"
      "- To remove all cached files, use `action='delete_all'`.\n"
      "\nAlways confirm with the user before deleting files to avoid accidental data loss."
    )
  }

if __name__ == "__main__":
  mcp.run()
