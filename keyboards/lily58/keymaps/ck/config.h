#pragma once

// Select hand configuration
#define MASTER_RIGHT
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 3000
#define SPLIT_USB_TIMEOUT_POLL 10
//#define USB_SUSPEND_WAKEUP_DELAY 5000
#define SPLIT_WATCHDOG_ENABLE      // Reboot slave if it loses connection
#define SPLIT_WATCHDOG_TIMEOUT 4000
#define SELECT_SOFT_SERIAL_SPEED 0 // 0 had the best response

// Send this data to slave side
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

// Key to press for boot (flash)
#define BOOTMAGIC_ROW 5
#define BOOTMAGIC_COLUMN 0

// Tap/Hold: Tap and hold for auto-repeat
#define QUICK_TAP_TERM 120

// Tap/Hold: Sets [tap] action when < Term
#define TAPPING_TERM 200

// Joystick setup
#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXES_COUNT 2

// Oled Display setup
#undef OLED_FONT_H 
#define OLED_FONT_H "keymaps/ck/glcdfont.c"

// Tap/Hold: Sets [hold] action when another key is tapped
#define PERMISSIVE_HOLD

// OS Detection (Fix for Mac OS ARM?)
#define OS_DETECTION_SINGLE_REPORT
#define OS_DETECTION_KEYBOARD_RESET

// Both shifts enable CAPS for a single word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 6000