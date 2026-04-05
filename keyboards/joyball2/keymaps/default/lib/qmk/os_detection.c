#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "./lib/layers/layer_switcher.h"
#include "./lib/layers/layers.h"
// #include "./lib/eeprom/eeprom.h"
// #include "./lib/joystick/joystick.h"

bool OsAlreadyDetected = false;

bool process_detected_host_os_kb(os_variant_t detected_os) {
  if (!process_detected_host_os_user(detected_os))
    return false;
  
  if (OsAlreadyDetected)
    return false;

  switch (detected_os) {
    case OS_MACOS:
    case OS_IOS: // Mac OS
      layerSwitcher_setBaseLayers(_MAC_OS, _WINDOWS);
      break;
    default: // Windows
      layerSwitcher_setBaseLayers(_WINDOWS, _GAMING);
  }
  OsAlreadyDetected = true;
  return true;
}