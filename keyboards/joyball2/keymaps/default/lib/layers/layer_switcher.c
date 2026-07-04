#include QMK_KEYBOARD_H
#include "layer_switcher.h"
#include "layers.h"
#include "./lib/audio/songs.h"
#include "./lib/mouse/pointer.h"
#include "./lib/joystick/joystick.h"

/*
Base Layer Toggle/Cycle Feature

Enables a given key to toggle between two layers on tap and switch to a 
different set of layers when hold (via selector).

For example, quickly toggle between Windows-Gaming on tap
but switching to a different base layer when hold+selector (round robin)

Toggle: Windows <-> Gaming
Hold+Next: Temporary selects MacOs
*/

enum LayerName activeBaseLayer; // default values used
enum LayerName standByBaseLayer; // for BaseLayer-Quick-Toggle

// =>                     ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  Layer Customization  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
void layerCustomization(void) {
  // RGB
  // HSV (Hue, Saturation and Value)
  // https://docs.qmk.fm/features/rgblight
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);

  switch (activeBaseLayer) {
    case _LINUX:
      combo_enable();
      rgblight_sethsv_noeeprom(180, 255, 150); // Violet
      mouse_setCpi(500);
      joystick_setMode(_JOY_ARROWS);
      break;
    case _WINDOWS:
      combo_enable();
      rgblight_sethsv_noeeprom(140, 255, 150); // Azure
      mouse_setCpi(500);
      joystick_setMode(_JOY_ARROWS);
      break;
    case _MAC_OS:
      combo_enable();
      rgblight_sethsv_noeeprom(0, 0, 150); // White
      mouse_setCpi(800);
      joystick_setMode(_JOY_ARROWS);
      break;
    case _GAME_S:
      combo_disable();
      rgblight_sethsv_noeeprom(11, 255, 150); // Red-Orange
      mouse_setCpi(500);
      joystick_setMode(_JOY_WASD);
      break;
    case _GAME_R:
      combo_disable();
      rgblight_sethsv_noeeprom(21, 255, 150); // Orange
      mouse_setCpi(500);
      joystick_setMode(_JOY_ARROWS);
      break;
    default: 
      // NA
  }
}

bool LS_isBaseLayer(enum LayerName layer){
  return (layer == activeBaseLayer ? true : false);
}

enum LayerName LS_baseLayer(void){
  return activeBaseLayer;
}

void applyLayerChanges(void) {
  clear_mods(); // helps clear
  layer_move(activeBaseLayer);
  layerCustomization();
}

// Sets Layers & apply changes
void layerSwitcher_setBaseLayers(enum LayerName active, enum LayerName standBy) {
  activeBaseLayer = active;
  standByBaseLayer = standBy;
  applyLayerChanges();
}

// Swaps active and standby layers
void layerSwitcher_quickSwap(void) {
  layerSwitcher_setBaseLayers(standByBaseLayer, activeBaseLayer);
  audio_playSound(_SN_LAYER_SWAP);
}

// Manual Layer Switch Forward
void layerSwitcher_selectNext(void) {
  // Round robin forward
  if (activeBaseLayer == LAST_BASE_LAYER) {
    activeBaseLayer = FIRST_BASE_LAYER;
  } else {
    activeBaseLayer = activeBaseLayer + 1;
  }
  applyLayerChanges();
  audio_playSound(_SN_LAYER_SWITCH);
}

// Manual Layer Switch Backward
void layerSwitcher_selectPrev(void) {
  // Round robin backwards
  if (activeBaseLayer == FIRST_BASE_LAYER) {
    activeBaseLayer = LAST_BASE_LAYER;
  } else {
    activeBaseLayer = activeBaseLayer - 1;
  }
  applyLayerChanges();
  audio_playSound(_SN_LAYER_SWITCH);
}

