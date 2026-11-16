import sys, time, serial
import vgamepad as vg

PORT = "COM7"
BAUD = 460800
DEAD = 0.08

# Stick resting values from your readings: LX, LY, RX, RY
CENTER = [1826, 1874, 1873, 1836]
INVERT = [False, False, False, False]   # set True if a direction is backwards

# Pots are switched off until they are wired
R2_ENABLED = False
L2_ENABLED = False
R2_REST, R2_FULL = 1200, 2400
L2_REST, L2_FULL = 1200, 2400

# Stick range is learned while running: it starts narrow
# and widens as you push each stick fully in every direction
lo = [c - 300 for c in CENTER]
hi = [c + 300 for c in CENTER]

B = vg.XUSB_BUTTON
BUTTONS = [B.XUSB_GAMEPAD_A, B.XUSB_GAMEPAD_B,
           B.XUSB_GAMEPAD_X, B.XUSB_GAMEPAD_Y,
           B.XUSB_GAMEPAD_LEFT_SHOULDER, B.XUSB_GAMEPAD_RIGHT_SHOULDER,
           B.XUSB_GAMEPAD_LEFT_THUMB, B.XUSB_GAMEPAD_RIGHT_THUMB,
           B.XUSB_GAMEPAD_DPAD_UP, B.XUSB_GAMEPAD_DPAD_DOWN,
           B.XUSB_GAMEPAD_DPAD_LEFT, B.XUSB_GAMEPAD_DPAD_RIGHT]

def stick(i, raw):
    lo[i] = min(lo[i], raw)
    hi[i] = max(hi[i], raw)
    if raw >= CENTER[i]:
        v = (raw - CENTER[i]) / (hi[i] - CENTER[i])
    else:
        v = (raw - CENTER[i]) / (CENTER[i] - lo[i])
    if abs(v) < DEAD:
        return 0.0
    v = (abs(v) - DEAD) / (1 - DEAD) * (1 if v > 0 else -1)
    return -v if INVERT[i] else v

def trigger(raw, rest, full):
    t = max(0.0, min(1.0, (raw - rest) / (full - rest)))
    return 0 if t < 0.03 else int(t * 255)

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)
ser.reset_input_buffer()

pad = vg.VX360Gamepad()
print("Running. Roll both sticks fully a few times. Ctrl+C to stop.")
try:
    while True:
        while ser.in_waiting > 120:
            ser.readline()
        line = ser.readline().decode(errors="ignore").strip()
        try:
            lx, ly, rx, ry, l2, r2, mask = map(int, line.split(","))
        except ValueError:
            continue
        pad.left_joystick_float(stick(0, lx), stick(1, ly))
        pad.right_joystick_float(stick(2, rx), stick(3, ry))
        pad.right_trigger(value=trigger(r2, R2_REST, R2_FULL) if R2_ENABLED else 0)
        pad.left_trigger(value=trigger(l2, L2_REST, L2_FULL) if L2_ENABLED else 0)
        for i, b in enumerate(BUTTONS):
            if mask & (1 << i):
                pad.press_button(button=b)
            else:
                pad.release_button(button=b)
        pad.update()
except KeyboardInterrupt:
    pass
finally:
    pad.reset()
    pad.update()
