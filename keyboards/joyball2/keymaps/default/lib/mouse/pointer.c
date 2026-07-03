#include QMK_KEYBOARD_H
// #include "./lib/joystick/joystick.h"
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"
// #include "./lib/display/print_info.h"

uint16_t mouseCpi = 800;
// char info_output[21]; // Ouput String max 20 chars (5x4 matrix + EoL)

// #define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))

uint16_t mouse_getCpi(void) {
  return mouseCpi;
}

// If this is bypassed CPI will not be updated in config settings
void mouse_setCpi(uint16_t cpi) {
  mouseCpi = cpi;
  pointing_device_set_cpi(cpi);
}

// Increases current CPI by 100
// Max for PWD3360 is 12,000 but we're capped at 3,100
void mouse_increaseCpi(void) {
  mouseCpi += 100;
  if (mouseCpi > 3100) {
    mouseCpi = 3100;
  }
  pointing_device_set_cpi(mouseCpi);

  // Print to Oled
  // snprintf(info_output, sizeof(info_output), "CPI:   %03d", mouseCpi);
  // oled_printInfo(info_output, 7, false); 
}

// Decrements current CPI by 100
// Min for PWD3360 is 100
void mouse_decreaseCpi(void) {
  mouseCpi -= 100;
  if (mouseCpi < 100){
    mouseCpi = 100;
  }
  pointing_device_set_cpi(mouseCpi);

  // Print to Oled
  // snprintf(info_output, sizeof(info_output), "CPI:   %03d", mouseCpi);
  // oled_printInfo(info_output, 7, false); 
}

// Refresh CPI when changing layers
void mouse_refreshCpi(void) {
  switch (LS_baseLayer()) {
    case _LINUX: // Bazzite
      mouse_setCpi(500);
      break;
    case _WINDOWS: // Windows
      mouse_setCpi(500);
      break;
    case _MAC_OS: // MacOS
      mouse_setCpi(800);
      break;
    case _GAME_S: // Shooter
      mouse_setCpi(500);
      break;
    case _GAME_R: // RPG
      mouse_setCpi(500);
      break;
    default:
      break;
  }
}