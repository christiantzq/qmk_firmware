#include QMK_KEYBOARD_H
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"

void rgb_updateBaseLayerHue(void){
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
  rgblight_sethsv_noeeprom(140, 255, 150); // Azure
  switch (LS_baseLayer()) {
    case _MAC_OS:
      rgblight_sethsv_noeeprom(0, 0, 150); // White
      break;
    case _WINDOWS:
      rgblight_sethsv_noeeprom(140, 255, 150); // Azure
      break;
    case _GAMING:
      rgblight_sethsv_noeeprom(21, 255, 128); // Orange
      break;
    default:
      break;
  }
}