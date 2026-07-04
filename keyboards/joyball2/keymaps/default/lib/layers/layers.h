#pragma once

/*
Layers are divided into BaseLayer, UpperLayers and optionally GameLayers.

BaseLayers are set automatically as default when keyboard detects the OS, 
for example, Windows, Linux or MacOS. They usually holds your main letter 
keys, space bar, backspace, and enter.

UpperLayers are more temporary in nature, like Numpad, Function, Nav or Symbols.

GameLayers are also BaseLayers, but never set as default and, for the 
purpose of this setup, will have their Combo disabled, as many games can
detect this with ani-cheat software and cause issues.

Setup below LayerName enum with your OS Layers, Gaming Layers and Upper Layers
in that order.
*/

// General layer definition (base/game layers must go first)
enum LayerName {
    _LINUX    = 0,
    _WINDOWS  = 1,
    _MAC_OS   = 2,
    _GAME_S   = 3,
    _GAME_R   = 4,
    _SYMBOL   = 5,
    _NUMPAD   = 6,
    _FUNCTION = 7,
    _CONFIG   = 8
};

// Define below indexes accordingly (inclusive)
#define FIRST_BASE_LAYER 0
#define LAST_BASE_LAYER 4