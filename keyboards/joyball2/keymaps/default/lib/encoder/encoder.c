#include QMK_KEYBOARD_H
#include "encoder.h"
#include "./lib/display/oled.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) // Scroll (Left Master)
    if (clockwise) {
        tap_code(MS_WHLD);
    } else {
        tap_code(MS_WHLU);
    }
  else { // Volume (Right Slave)
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
  } 
  oled_wakeUpScreen();

  return false;
}
