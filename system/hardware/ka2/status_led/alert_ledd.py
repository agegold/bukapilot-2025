#!/usr/bin/env python3
"""
Alert LED service (efficient):
- Importable AND directly runnable: `python alert_led_service.py` (no args).
- Blocking, low-CPU loop (no busy sleep).
- Blink runs once, then settles to solid (remembers last non-blink solid by default).
- If controlsState is not running (no updates for > not_running_timeout_s), show SOLID YELLOW.
"""

import time
import threading
from typing import Callable, Dict, Optional, Tuple

# --- robust imports so this file works when run directly or as a package module ---
try:
    from .status_led import set_led, WS2812_SCRIPT_DEFAULT
except Exception:
    import os as _os, sys as _sys
    _pkg_root = _os.path.dirname(_os.path.dirname(_os.path.abspath(__file__)))
    if _pkg_root not in _sys.path:
        _sys.path.insert(0, _pkg_root)
    from system.hardware.ka2.status_led.status_led import set_led, WS2812_SCRIPT_DEFAULT  # type: ignore

try:
    from cereal import messaging
except Exception as e:
    raise RuntimeError("cereal.messaging not found. Run inside the openpilot environment.") from e


StateTuple = Tuple[str, str, Optional[str], str]  # (color_or_hex, mode, rate, brightness)


class AlertLEDService:
    """
    Subscribes to 'controlsState', reads alertType/active, and drives the status LED.

    Blink policy:
      - Blink runs ONCE per alertType (latched).
      - After blinking, LED switches to a SOLID state automatically:
          * 'previous' -> previous non-blink solid (remembered baseline)
          * 'same'     -> solid of the blink color

    Not-running policy:
      - If no updates from controlsState for > not_running_timeout_s OR sub is not alive:
          * LED = SOLID YELLOW (does NOT change the remembered baseline)
    """

    def __init__(
        self,
        *,
        ws_script: str = WS2812_SCRIPT_DEFAULT,
        brightness_active: str = "200",
        brightness_standby: str = "100",
        topic: str = "controlsState",
        base_poll_ms: int = 500,          # base block time for SubMaster.update
        overrides: Optional[Dict[str, Tuple[str, str, Optional[str]]]] = None,
        on_change: Optional[Callable[[bool, str, StateTuple], None]] = None,
        blink_duration_s: float = 1.0,
        blink_settle: str = "previous",   # 'previous' | 'same'
        not_running_timeout_s: float = 1.0,
        debug: bool = True,
    ):
        assert blink_settle in ("previous", "same"), "blink_settle must be 'previous' or 'same'"

        self.ws_script = ws_script
        self.brightness_active = brightness_active
        self.brightness_standby = brightness_standby
        self.topic = topic
        self.base_poll_ms = int(max(1, base_poll_ms))
        self.on_change = on_change
        self.overrides = {k.lower(): v for k, v in (overrides or {}).items()}
        self.blink_duration_s = float(blink_duration_s)
        self.blink_settle = blink_settle
        self.not_running_timeout_s = float(not_running_timeout_s)
        self.debug = debug

        self._stop = threading.Event()
        self._sm = messaging.SubMaster([self.topic])

        # Last applied state
        self._last: Optional[StateTuple] = None
        self._last_active: Optional[bool] = None

        # Remembered state (used when settling from blink)
        self._last_non_blink: StateTuple = ("YELLOW", "solid", None, self.brightness_standby)

        # Blink scheduler
        self._blink_latched_for: Optional[str] = None
        self._blink_until: float = 0.0
        self._pending_post_state: Optional[StateTuple] = None

        # Track last message time + last seen values
        self._last_msg_time: Optional[float] = None
        self._last_seen_active: bool = False
        self._last_seen_alert_type: str = ""

        # Start in "not running" yellow
        self._apply(("YELLOW", "solid", None, self.brightness_active), active=False, alert_type="not_running")

    def stop(self):
        self._stop.set()

    def run_forever(self):
        while not self._stop.is_set():
            now = time.monotonic()

            # Compute dynamic blocking timeout:
            # - base_poll_ms to check for not-running timeout
            # - but if a blink is scheduled to end sooner, wake just in time to settle
            wait_ms = self.base_poll_ms
            if self._blink_until > 0:
                remaining_ms = int((self._blink_until - now) * 1000)
                if remaining_ms <= 0:
                    wait_ms = 1
                else:
                    wait_ms = max(1, min(wait_ms, remaining_ms))

            # Block for up to wait_ms waiting for a message
            self._sm.update(wait_ms)

            now = time.monotonic()

            # Record heartbeat if updated
            if self._sm.updated[self.topic]:
                self._last_msg_time = now

                cs = self._sm[self.topic]
                self._last_seen_active = bool(getattr(cs, "active", False))
                self._last_seen_alert_type = (getattr(cs, "alertType", "") or "")

                desired = self._effective_state(self._last_seen_alert_type, self._last_seen_active)
                self._maybe_apply(desired, self._last_seen_active, self._last_seen_alert_type)
                # Continue to next loop; we may have also set a blink end time.
                continue

            # No new message: check timers and not-running condition

            # 1) Settle from blink if its window ended
            if self._blink_until > 0 and now >= self._blink_until and self._pending_post_state:
                solid = self._pending_post_state
                self._pending_post_state = None
                self._blink_until = 0.0
                self._last_non_blink = solid
                # Use last seen values for context (cheap and OK)
                self._maybe_apply(solid, self._last_seen_active, self._last_seen_alert_type)

            # 2) controlsState not running?
            no_heartbeat = (self._last_msg_time is None) or ((now - self._last_msg_time) > self.not_running_timeout_s)
            if (not self._sm.alive[self.topic]) or no_heartbeat:
                yellow = ("YELLOW", "solid", None, self.brightness_active)
                self._maybe_apply(yellow, active=False, alert_type="not_running")

    # ----- classification & blink policy -----

    def classify(self, alert_type: str, active: bool) -> StateTuple:
        """Base mapping: (color, mode, rate, brightness). Customize as needed."""
        tl = alert_type.lower()

        # Exact overrides
        if tl in self.overrides:
            color, mode, rate = self.overrides[tl]
            return (color, mode, rate, self.brightness_active if active else self.brightness_standby)

        # Heuristics (very light string checks)
        if active:
            if ("immediate" in tl):
                return ("RED", "blink", "fast", self.brightness_active)
            if ("override" in tl):
                return ("WHITE", "solid", None, self.brightness_active)
            if ("soft" in tl) or ("warn" in tl) or ("low" in tl) or ("overheat" in tl) or ("unavail" in tl) or ("pre" in tl) or ("temp" in tl):
                return ("ORANGE", "blink", "fast", self.brightness_active)
            return ("GREEN", "solid", None, self.brightness_active)

        if ("permanent" in tl):
            return ("RED", "solid", None, self.brightness_active)
        if ("noentry" in tl):
            return ("ORANGE", "solid", None, self.brightness_active)
        return ("WHITE", "solid", None, self.brightness_standby)

    def _effective_state(self, alert_type: str, active: bool) -> StateTuple:
        """
        Enforce: blink once → then solid.
        Remembers last non-blink solid and uses it when settling (if configured).
        """
        base = self.classify(alert_type, active)
        now = time.monotonic()
        tl = alert_type.lower()

        # Non-blink: remember and clear blink scheduling
        if base[1] != "blink":
            self._last_non_blink = base
            self._blink_until = 0.0
            self._pending_post_state = None
            self._blink_latched_for = None
            return base

        # Blink path
        if self._blink_latched_for != tl:
            # New alertType ⇒ start blink window
            self._blink_latched_for = tl
            self._blink_until = now + self.blink_duration_s

            # Decide post-blink solid target
            if self.blink_settle == "previous" and self._last_non_blink:
                post = self._last_non_blink
            else:
                post = (base[0], "solid", None, base[3])  # settle to solid of the blink color

            self._pending_post_state = post
            return base  # show blink

        # Already latched for this alertType
        if now < self._blink_until:
            return base  # keep blinking until window ends

        # Blink window over ⇒ settle to solid
        if self._pending_post_state:
            solid = self._pending_post_state
            self._pending_post_state = None
            self._blink_until = 0.0
            self._last_non_blink = solid
            return solid

        # Fallback: convert current blink to solid
        self._blink_until = 0.0
        return (base[0], "solid", None, base[3])

    # ----- apply & change detection -----

    def _maybe_apply(self, state: StateTuple, active: bool, alert_type: str):
        if state != self._last or active != self._last_active:
            self._apply(state, active, alert_type)
            self._last = state
            self._last_active = active

    def _apply(self, state: StateTuple, active: bool, alert_type: str):
        color, mode, rate, brightness = state
        # Only include duration when blinking; led script handles the rest.
        kwargs = {"duration": str(self.blink_duration_s)} if mode == "blink" else {}
        set_led(
            color, None,
            mode=mode, rate=rate, brightness=brightness,
            ws_script=self.ws_script, fire_and_forget=True, **kwargs
        )
        if self.debug and alert_type:
            # Lightweight optional trace
            print(f"[LED] active={active} alertType='{alert_type}' -> {mode} {color}"
                  + (f" rate={rate}" if rate else "")
                  + f" brightness={brightness}", flush=False)

def main():
  svc = AlertLEDService()
  svc.run_forever()

if __name__ == "__main__":
    svc = AlertLEDService()
    try:
        svc.run_forever()
    except KeyboardInterrupt:
        svc.stop()

