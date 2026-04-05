#include QMK_KEYBOARD_H
#include "layer_switcher.h"
#include "layers.h"
#include "./lib/rgb/under_glow.h"

/*
Base Layer Toggle/Cycle Feature

Enables a given key to toggle between two layers on tap and switch to a 
different set of layers when hold.

For example, quickly toggle between Windows-Gaming on tap
but Switching to MacOS-Windows when hold longer than given term
 */

#define LAYER_CYCLE_TERM 500

bool isBaseLayerKeyTimerRunning = false;
uint16_t baseLayerKeyTimer = 0;
enum LayerName activeBaseLayer = _WINDOWS; // default values used
enum LayerName standByBaseLayer = _GAMING; // for BaseLayer-Quick-Toggle


bool LS_isBaseLayer(enum LayerName layer){
  return (layer == activeBaseLayer ? true : false); 
}

enum LayerName LS_baseLayer(void){
  return activeBaseLayer;
}

// Handles sounds and colors right after switching layers 
void layerSwitcher_setBaseLayers(enum LayerName active, enum LayerName standBy) {
  clear_mods(); // Useful to clear
  activeBaseLayer = active;
  standByBaseLayer = standBy;
  layer_move(activeBaseLayer);
  // Disable Combos in Game Mode
  if (activeBaseLayer == _GAMING) {
    combo_disable();
  } else {
    combo_enable();
  }
  // Setup lights, sounds, etc
  rgb_updateBaseLayerHue();
}

// Triggered when Base Layer Cycle Key has just being pressed
// this starts the timer to know if we need to toggle between
// the active and standBy layers or cycle to another layer
void beginBaseLayerCycleHandling(void) {
  baseLayerKeyTimer = timer_read();  // Saves current time for timing it latter
  isBaseLayerKeyTimerRunning = true;
}

// Performs the toggle if the term for hold has not being reached.
void finishBaseLayerCycleHandling(void) {
  if (isBaseLayerKeyTimerRunning) {
    // Layer Switch
    layerSwitcher_setBaseLayers(standByBaseLayer, activeBaseLayer);
  }
  isBaseLayerKeyTimerRunning = false;
}

// Setup Keycode in process_record_user (keymap.c)
void layerSwitcher_keyHandler(bool isKeyPressed){
  if (isKeyPressed) {
    clear_mods();
    beginBaseLayerCycleHandling();
  } else {
    finishBaseLayerCycleHandling();
  }
}

// After enabling it, this monitors the timer, if the Term was
// reached, proceed to cycle to the next layers.
// As this includes a timer check, it needs to be called 
// from the Matrix Scan's QMK function.
void layerSwitcher_timerHandler(void) {
  if (isBaseLayerKeyTimerRunning) {
    if (timer_elapsed(baseLayerKeyTimer) > LAYER_CYCLE_TERM) {
      isBaseLayerKeyTimerRunning = false;
      if (activeBaseLayer == _GAMING || standByBaseLayer == _GAMING){
        layerSwitcher_setBaseLayers(_MAC_OS, _WINDOWS);
      } else if (activeBaseLayer == _MAC_OS || standByBaseLayer == _MAC_OS) {
        layerSwitcher_setBaseLayers(_WINDOWS, _GAMING);
      }
    }
  }
}
