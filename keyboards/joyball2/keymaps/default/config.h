#pragma once

// Split Hardware Config
#define MASTER_LEFT
#define SERIAL_USART_TX_PIN GP0    // USART TX pin
#define SERIAL_USART_RX_PIN GP1    // USART RX pin
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 3000
#define SPLIT_USB_TIMEOUT_POLL 10
//#define USB_SUSPEND_WAKEUP_DELAY 5000
#define SPLIT_WATCHDOG_ENABLE      // Reboot slave if it loses connection
#define SPLIT_WATCHDOG_TIMEOUT 4000
#define SELECT_SOFT_SERIAL_SPEED 0 // 0 had the best response

// USB Config
#define USB_POLLING_INTERVAL_MS 1

// OS Detection
#define OS_DETECTION_SINGLE_REPORT
#define OS_DETECTION_KEYBOARD_RESET

// Oled Display setup
#undef OLED_FONT_H
#define OLED_FONT_H "keymaps/default/lib/display/glcdfont.c"

// For custom communication between sides
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A

// Send this data to slave side
#define SPLIT_LAYER_STATE_ENABLE  // Current Layer
#define SPLIT_MODS_ENABLE         // GUI/Ctrl/Alt/Shift
#define SPLIT_LED_STATE_ENABLE    // Caps/NumLock/ScrLock
#define SPLIT_HAPTIC_ENABLE       // Haptic Feedback

// Haptics for Eccentric Rotating Mass (ERM)
#define DRV2605L_FB_ERM_LRA 0
#define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#define DRV2605L_RATED_VOLTAGE 3 // Refer to your motor's datasheet for the correct value
#define DRV2605L_V_PEAK 5 // Refer to your motor's datasheet for the correct value

// Trackball Config (Slave Right)
#define SPLIT_POINTING_ENABLE     // Mouse Pointer
// #define MOUSE_EXTENDED_REPORT
// #define WHEEL_EXTENDED_REPORT
#define ROTATIONAL_TRANSFORM_ANGLE  90
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_RIGHT
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
#define PMW33XX_CS_PIN GP21
#define POINTING_DEVICE_TASK_THROTTLE_MS 4
#define PMW33XX_LIFTOFF_DISTANCE 0x02 //0x02
// #define POINTING_DEVICE_HIRES_SCROLL_ENABLE

// Joystick Config (Master Left)
#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXES_COUNT 2
#define JOYSTICK_AXIS_RESOLUTION 10

// Combo setup
#define COMBO_ONLY_FROM_LAYER 0 // Combos forced to Base Layer
#define COMBO_MUST_TAP_PER_COMBO // Allows Homerows to be combo-ed

// Tap/Hold: Sets [hold] action when another key is tapped
#define PERMISSIVE_HOLD

// Shifts for Caps
//#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 6000

// Sea Picro Under-glow config 
#undef WS2812_DI_PIN
#define WS2812_DI_PIN 11 // GP11
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14
#define RGBLED_SPLIT {7, 7}
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_SNAKE

// Audio Config (check mcuconf.h/halconf.h for PWM setup)
#define AUDIO_PIN GP10
#define AUDIO_PWM_DRIVER PWMD5
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define AUDIO_INIT_DELAY

// Encoders
#define ENCODERS_PAD_A { GP27 }
#define ENCODERS_PAD_B { GP26 }
#define ENCODER_RESOLUTIONS { 2 }