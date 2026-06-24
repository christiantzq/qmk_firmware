# Generic RP2040 compatible Pin Layout (check elite-c-pins.png)
PIN_COMPATIBLE = elite_c

# Enable Flashboot with Key 0,0 (Tilde/Minus keys)
BOOTMAGIC_ENABLE = yes

# Generic RP2040 compatible Bootloader
BOOTLOADER = rp2040
CONVERT_TO = rp2040_ce

# Tries to detect OS
OS_DETECTION_ENABLE = yes

# Activate Joystick
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# Activate Mouse Pointer
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
# Mouse buttons
MOUSEKEY_ENABLE = yes

# Oled Screens
OLED_ENABLE = yes

# Uppercase word with both shifts
CAPS_WORD_ENABLE = yes

# Simultaneous keypress functions
COMBO_ENABLE = yes

# Audio control and System control
EXTRAKEY_ENABLE = yes

# Link Time Optimization enabled
LTO_ENABLE = yes

SRC += analog.c
SRC += ./lib/logo_reader.c
SRC += ./lib/layers/layer_switcher.c