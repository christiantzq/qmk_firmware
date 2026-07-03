#pragma once
#include "layers.h"

/* - - - - - - - API List: - - - - - - - */ 

// Sets both base layers (helpful for initialization)
void layerSwitcher_setBaseLayers(enum LayerName active, enum LayerName standBy);

// returns current activeBaseLayer
enum LayerName LS_baseLayer(void); // RENAME

// Returns true if given layer is active
bool LS_isBaseLayer(enum LayerName layer); // RENAME

// Select next next layer (round robin)
void layerSwitcher_selectNext(void);

// Select previous next layer (round robin)
void layerSwitcher_selectPrev(void);

// Swaps active and standby layers
void layerSwitcher_quickSwap(void);