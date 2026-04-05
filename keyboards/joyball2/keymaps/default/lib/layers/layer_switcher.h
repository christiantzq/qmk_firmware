#pragma once
#include "layers.h"


// Setup Keycode in process_record_user (keymap.c)
void layerSwitcher_keyHandler(bool isKeyPressed);

// Setup in matrix_scan_user (qmk/life_cycle.c)
void layerSwitcher_timerHandler(void);

// API
void layerSwitcher_setBaseLayers(enum LayerName active, enum LayerName standBy);
enum LayerName LS_baseLayer(void); // returns current activeBaseLayer
bool LS_isBaseLayer(enum LayerName layer);