# [cK] JoyBall2 Split Keyboard

## Compile
```bash
qmk compile -kb joyball2 -km default
```

## First Time Setup

- From Ubuntu:
```bash
python3 --version
sudo apt install python3-pip
sudo apt install python3.12-venv
python3 -m venv .venv
source .venv/bin/activate
pip install qmk
```

- From Bazzite:
    - Instal BoxBuddy (flatpak)
    - Install Ubuntu 22.04
    - Run: `curl -fsSL https://install.qmk.fm | sh`
```bash
qmk setup
qmk new-keyboard -kb joyball2
codium /home/chris/qmk_firmware/keyboards/joyball2
```
 - All default except:
    - Development Board: `y`, `kb2040`


## Features
- Ergonomic Split Keyboard 
    - Full Duplex Serial Communication (TRRS 4 pin required)
- Cheap/Generic ProMicro RP2040 (16Mb)
- 5x6 Matrix per side (4 + 8 + 48 Programmable Switches)
    - Per side D-pad (3D printed case, 8 buttons total)
    - Per side Dedicated Mouse Buttons (3D Printed, 4 buttons total)
    - Mechanical Hot-Swappable Switches (Kailh Choc V1, 48 total)
- Trackball (Slave Right, 3D Printed holder)
    - PixArt 3060 (High End Gaming Mouse sensor)
    - Easy to roll system (1 BTU, 4 static bearings)
- Analog Joystick (Master Left, 3D Printed holder)
    - TMR Joystick (anti-drift)
- Per side OLED Screen.
- Minimalistic RGB side-lights (3D Printed Cover and Diffuser)
- Per side Horizontal Knob (3D Printed)
- Speaker (Master Left)
- Per side Haptic Feedback
- Tenting Kit (30 degree, 3D Printed)


### Other
- Haptics: https://docs.qmk.fm/features/haptic_feedback