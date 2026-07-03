#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "./lib/layers/layer_switcher.h"
#include "./lib/layers/layers.h"
#include "./lib/mouse/pointer.h"

bool OsAlreadyDetected = false;

bool process_detected_host_os_kb(os_variant_t detected_os) {
  if (!process_detected_host_os_user(detected_os))
    return false;
  
  if (OsAlreadyDetected)
    return false;

  switch (detected_os) {
    case OS_LINUX: // Bazzite
      layerSwitcher_setBaseLayers(_LINUX, _GAME_S);
      break;
    case OS_WINDOWS: // Windows
      layerSwitcher_setBaseLayers(_WINDOWS, _GAME_S);
      break;
    case OS_MACOS:
    case OS_IOS: // Mac OS
      layerSwitcher_setBaseLayers(_MAC_OS, _GAME_S);
      break;
    case OS_UNSURE:
      layerSwitcher_setBaseLayers(_LINUX, _GAME_S);
  }
  OsAlreadyDetected = true;
  return true;
}
