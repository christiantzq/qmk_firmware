# Config for using RP2040 Serial
SERIAL_DRIVER = vendor

# Tries to detect OS
OS_DETECTION_ENABLE = yes

# Enable Joystick (Master Left)
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# Enable Encoders (& Audio/System keys)
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes

# Enable Mouse Buttons
MOUSEKEY_ENABLE = yes

# Oled Screen
OLED_ENABLE = yes

# Enable Audio (Chibi-OS)
AUDIO_DRIVER = pwm_hardware
AUDIO_ENABLE = yes

# Haptics
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l

# Uppercase word with both shifts
CAPS_WORD_ENABLE = yes

# Simultaneous keypress functions
COMBO_ENABLE = yes

# Enable Trackball (Slave Right)
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

# Enable WS2812 RGB under-light.
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = vendor

# Libraries
SRC += ./lib/display/oled.c
SRC += ./lib/joystick/joystick.c
SRC += ./lib/encoder/encoder.c
SRC += ./lib/mouse/pointer.c
SRC += ./lib/layers/layer_switcher.c
# SRC += ./lib/eeprom/eeprom.c
SRC += ./lib/sync/oled_status.c
SRC += ./lib/rgb/under_glow.c
SRC += ./lib/qmk/life_cycle.c
SRC += ./lib/qmk/os_detection.c
SRC += ./lib/audio/songs.c