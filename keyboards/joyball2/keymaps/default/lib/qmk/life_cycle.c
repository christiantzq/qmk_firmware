#include QMK_KEYBOARD_H
#include "transactions.h"
// #include "./lib/eeprom/eeprom.h"
#include "./lib/display/oled.h"
// #include "./lib/display/print_info.h"
// #include "./lib/espeng/esp_key.h"
#include "./lib/layers/layer_switcher.h"
#include "./lib/joystick/joystick.h"
#include "./lib/encoder/encoder.h"
#include "./lib/sync/oled_status.h"
#include "./lib/rgb/under_glow.h"
// #include "./lib/pomodoro/pomodoro.h"


// =>                             ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Keyboard Init ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
// Runs once at boot-up
void keyboard_post_init_user(void) {
  // Under-light RGB Setup
  rgblight_enable_noeeprom(); 
  rgb_updateBaseLayerHue();

  // Read the user config from EEPROM
  // eeprom_loadUserConfig(); 
  
  // Slave-side custom sync setup
  transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);

  pointing_device_set_cpi(800);
}

// =>                               ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Matrix Scan ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
// Runs very early, every single tick
void matrix_scan_user(void) {
  // Spanish Characters
  //espKey_timerHandler();

  // Base Layer Toggler
  layerSwitcher_timerHandler();

  // Pomodoro Count Down
  // pomodoro_timerHandler();

  // Joystick
  joystick_readPins();
}

// =>                         ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Housekeeping Task ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
// Runs very late, every single tick
void housekeeping_task_user(void) {
  // Joystick Stuff
  joystick_postProcessing();

  // Encoder timer
  //encoder_timerHandler();

  // Oled Temp Text Info Display
  //printInfo_timerHandler();
  
  // Oled Screen Saver
  oled_timerHandler();

  // Oled Sync
  syncOledStateWithSlave();
}