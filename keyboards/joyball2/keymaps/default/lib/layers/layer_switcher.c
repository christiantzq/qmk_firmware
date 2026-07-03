#include QMK_KEYBOARD_H
#include "layer_switcher.h"
#include "layers.h"
#include "./lib/rgb/under_glow.h"
#include "./lib/audio/songs.h"

/*
Base Layer Toggle/Cycle Feature

Enables a given key to toggle between two layers on tap and switch to a 
different set of layers when hold (via selector).

For example, quickly toggle between Windows-Gaming on tap
but switching to a different base layer when hold+selector (round robin)
the temp base layer is not set until committing, allowing for more 
practical encoder selection.

Toggle: Windows <-> Gaming
Hold+Next: Temporary selects MacOs
Commit: MacOs and Windows become the new active and standby layers
*/

enum LayerName activeBaseLayer = _WINDOWS; // default values used
enum LayerName standByBaseLayer = _GAMING; // for BaseLayer-Quick-Toggle

bool LS_isBaseLayer(enum LayerName layer){
  return (layer == activeBaseLayer ? true : false);
}

enum LayerName LS_baseLayer(void){
  return activeBaseLayer;
}

// Disables Combo when a Game layer is selected (required for some anti-cheat games)
void handleGamingLayer(void) {
  if (activeBaseLayer >= FIRST_GAME_LAYER && activeBaseLayer <= LAST_GAME_LAYER) {
    combo_disable();
  } else {
    combo_enable();
  }
}

void applyLayerChanges(void) {
  clear_mods(); // helps clear
  layer_move(activeBaseLayer);
  handleGamingLayer(); // Disable Combos in Game Mode
  rgb_updateBaseLayerHue(); // Set lighting
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