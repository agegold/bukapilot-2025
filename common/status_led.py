import re
import subprocess

COLORS = {
  "WHITE": "FFFFFF",
  "RED": "00FF00",
  "GREEN": "0000FF",
  "BLUE": "FF0000",
  "ORANGE": "00FF25",
  "YELLOW": "00DD88",
}

_HEX_RE = re.compile(r"^#?[0-9A-Fa-f]{6}$")

def _to_hex(color: str | None) -> str | None:
  if not color:
    return None
  s = str(color).strip()
  name = s.upper()
  if name in COLORS:
    return COLORS[name]
  if _HEX_RE.match(s):
    return s.lstrip("#").upper()
  return s

def set(color=None, mode="solid", rate="fast", duration="1", brightness="100"):
  mode = mode or "solid"
  if rate and not mode:
    mode = "blink"

  args = ["python", "/usr/kommu/ws2812.py", mode]

  if mode in ("solid", "blink", "run"):
    args += ["--brightness", str(brightness)]
    hex_color = _to_hex(color)
    if hex_color:
      args += ["--a-color", hex_color, "--b-color", hex_color]
    if mode == "blink":
      args += ["--rate", str(rate), "--duration", str(duration)]

  subprocess.Popen(args, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

