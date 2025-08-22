from opendbc.can.packer import CANPacker
from openpilot.selfdrive.car.interfaces import CarControllerBase
from openpilot.selfdrive.car.proton.protoncan import create_can_steer_command, send_buttons, create_acc_cmd
from openpilot.selfdrive.car.proton.values import DBC
from openpilot.common.numpy_fast import clip
from openpilot.common.realtime import DT_CTRL
from openpilot.common.features import Features
import time

def apply_proton_steer_torque_limits(apply_torque, apply_torque_last, driver_torque, LIMITS):

  # limits due to driver torque
  driver_offset = driver_torque * 30
  max_steer_allowed = clip(LIMITS.STEER_MAX + driver_offset, 0, LIMITS.STEER_MAX)
  min_steer_allowed = clip(-LIMITS.STEER_MAX + driver_offset, -LIMITS.STEER_MAX, 0)
  apply_torque = clip(apply_torque, min_steer_allowed, max_steer_allowed)

  # slow rate if steer torque increases in magnitude
  if apply_torque_last > 0:
    apply_torque = clip(apply_torque, max(apply_torque_last - LIMITS.STEER_DELTA_DOWN, -LIMITS.STEER_DELTA_UP),
                        apply_torque_last + LIMITS.STEER_DELTA_UP)
  else:
    apply_torque = clip(apply_torque, apply_torque_last - LIMITS.STEER_DELTA_UP,
                        min(apply_torque_last + LIMITS.STEER_DELTA_DOWN, LIMITS.STEER_DELTA_UP))

  return round(apply_torque)

STEER_REDUCED_TIME = 1.75 # The time where the steering becomes 100% again

def reduce_steer(steer, resume_diff):
  # Non-linear increment steering after resume
  rate = 0.003 # Higher rate means steeper curve. When rate is 0, the curve becomes linear.
  mul = min(1.0, (resume_diff / STEER_REDUCED_TIME) ** (1.0 - rate))
  return steer * mul

class CarControllerParams():
  def __init__(self, CP):

    self.STEER_MAX = CP.lateralParams.torqueV[0]
    # make sure Proton only has one max steer torque value
    assert(len(CP.lateralParams.torqueV) == 1)

    # for torque limit calculation
    self.STEER_DELTA_UP = 15
    self.STEER_DELTA_DOWN = 35

class CarController(CarControllerBase):
  def __init__(self, dbc_name, CP, VM):
    self.CP = CP
    self.frame = 0
    self.packer = CANPacker(DBC[CP.carFingerprint]['pt'])
    self.params = CarControllerParams(self.CP)

    self.last_steer = 0
    self.steer_rate_limited = False
    self.steering_direction = False

    self.last_steer_resume_frame = 0
    self.prev_lat_active = False

    # For LDW/LDP (Proton stock LKS/LKA)
    self.always_lks_tactile = Features().has("lks-tactile")
    self.last_steer_disable = 0

  def update(self, CC, CS, now_nanos):
    can_sends = []
    frame = self.frame

    enabled = CC.latActive
    actuators = CC.actuators
    lat_active = enabled
    #ldw = CC.hudControl.leftLaneDepart or CC.hudControl.rightLaneDepart

    # steer
    new_steer = round(actuators.steer * self.params.STEER_MAX)
    apply_steer = apply_proton_steer_torque_limits(new_steer, self.last_steer, 0, self.params)

    cs_out = CS.out

    if lat_active:
      # Check bp steer resume before LDP check
      if not self.prev_lat_active:
        self.last_steer_resume_frame = frame
      # Reduce steering after each bp resume
      if (resume_diff := (frame - self.last_steer_resume_frame) * DT_CTRL) < STEER_REDUCED_TIME:
        apply_steer = reduce_steer(apply_steer, resume_diff)
    else: # not lat_active
      if self.prev_lat_active:
        self.last_steer_disable = time.monotonic() # Record last bp steer disabled time

    # Record the last lat_active before LDP applied
    self.prev_lat_active = lat_active

    # Stock Lane Departure Prevention / Centering Control (LKS Auxiliary / Blue line)
    if not lat_active and (stock_steer_cmd := CS.stock_ldp_cmd) > 0 and \
       not ((cs_out.rightBlinker and CS.stock_ldp_right) or (cs_out.leftBlinker and CS.stock_ldp_left)):
      # After steer disable, keep steering at 0 for the first 0.55 seconds, then increase from 0% to 100% over 0.5 seconds.
      # To prevent sudden pull after bp disable (especially in ICC mode or LKA Centering mode)
      mul = clip((time.monotonic() - self.last_steer_disable - 0.55) / 0.5, 0, 1)
      apply_steer = round(stock_steer_cmd * (-1 if CS.steer_dir else 1) * mul) &~1 # Ensure LSB 0 for 11-bit cmd
      lat_active = True
      self.steer_rate_limited = False

    # CAN controlled lateral running at 50hz
    if frame % 2 == 0:
      ldw_steering = CS.stock_ldw_steering
      # Passing LKS mode values does not change car stored values, so also pass LDW value to ADAS steering.
      if self.always_lks_tactile:
        ldw_steering = ldw_steering or CS.has_audio_ldw
        lks_audio, lks_tactile = False, True
      else:
        lks_audio, lks_tactile = CS.lks_audio, CS.lks_tactile

      standstill_request = cs_out.standstill and CC.longActive and actuators.accel < -0.01
      can_sends.append(create_can_steer_command(self.packer, apply_steer, lat_active, \
                      CS.hand_on_wheel_warning, CS.hand_on_wheel_warning_2, \
                      CS.lks_aux, CS.lks_audio, CS.lks_tactile, CS.lks_assist_mode, \
                      CS.lka_enable, ldw_steering))
      can_sends.append(create_acc_cmd(self.packer, actuators.accel, enabled, cs_out.gasPressed, standstill_request))

      #can_sends.append(create_hud(self.packer, apply_steer, enabled, ldw, CC.hudControl.rightLaneVisible, CC.hudControl.leftLaneVisible))
      #can_sends.append(create_lead_detect(self.packer, CC.hudControl.leadVisible, enabled))


    self.last_steer = apply_steer
    new_actuators = actuators.copy()
    new_actuators.steer = apply_steer / self.params.STEER_MAX

    self.frame += 1
    return new_actuators, can_sends
