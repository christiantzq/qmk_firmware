#include QMK_KEYBOARD_H
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"

// HSV (Hue, Saturation and Value)
// https://docs.qmk.fm/features/rgblight

void rgb_updateBaseLayerHue(void){
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
  rgblight_sethsv_noeeprom(0, 0, 0); // Black?

  switch (LS_baseLayer()) {
    case _LINUX:
      rgblight_sethsv_noeeprom(180, 255, 150); // Violet
      break;
    case _MAC_OS:
      rgblight_sethsv_noeeprom(0, 0, 150); // White
      break;
    case _WINDOWS:
      rgblight_sethsv_noeeprom(140, 255, 150); // Azure
      break;
    case _GAME_S: // Shooter
      rgblight_sethsv_noeeprom(11, 255, 150); // Red/Orange
      break;
    case _GAME_R: // RPG
      rgblight_sethsv_noeeprom(21, 255, 150); // Orange
      break;
    default:
      break;
  }
}