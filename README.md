# ESP32 USB Gamepad (Virtual Xbox 360 Controller)

A wired gamepad built around an ESP32. A Python script on the PC turns the ESP32's serial data into a virtual Xbox 360 controller.

## Why this design
The classic ESP32 has no native USB HID, and my PC has no Bluetooth, so the ESP32 can't appear as a gamepad directly. Instead:
1. The ESP32 reads sticks, pots and buttons and streams them over USB serial (460800 baud).
2. A Python script reads the stream and creates a virtual Xbox 360 controller using vgamepad (ViGEmBus driver).

## Status
- Working: both joysticks, including L3/R3 clicks. Tested on an online gamepad tester and in Assetto Corsa.
- Planned: A/B/X/Y, L1/R1, 4-way D-pad (firmware and pins are in place; waiting for switches with longer legs) and potentiometer triggers (LT/RT).

## Components
- NodeMCU ESP32S
- 2 x HW-504 joystick modules
- Tactile switches
- Potentiometers (for LT/RT)
- Breadboard and jumper wires
- USB cable

## Wiring
Joysticks: VCC to 3V3 (not 5V), GND to GND.

| Input | GPIO |
|---|---|
| Left stick X / Y | 36 / 39 |
| Right stick X / Y | 34 / 35 |
| L3 / R3 (stick clicks) | 26 / 27 |
| L2 pot / R2 pot | 33 / 32 |
| A / B / X / Y | 13 / 14 / 16 / 17 |
| L1 / R1 | 18 / 19 |
| D-pad Up / Down / Left / Right | 23 / 25 / 4 / 5 |

Buttons: one leg to the GPIO, the diagonally opposite leg to GND (internal pull-ups are used).

## Setup
1. Flash [gamepad_firmware.ino](gamepad_firmware.ino) with Arduino IDE (board: ESP32 Dev Module).
2. Install Python, then run `python -m pip install pyserial` followed by `python -m pip install vgamepad`. (restart the computer once).
3. Edit `PORT` in [gamepad.py](gamepad.py) to your COM port, close the Arduino Serial Monitor, and run `python gamepad.py`.
4. Roll both sticks fully a few times so the script learns their range.

## Notes
- the python script must constantly keep running in the background. If it is closed, the virtual gamepad disconnects.
- Stick directions can be flipped with the `INVERT` list in `gamepad.py`.
- The Python script was written with AI assistance.

## Demo
[google drive](https://drive.google.com/drive/folders/1YRcsxh0ck-ftof3_ygBeJYhW_rbsMEM_)
