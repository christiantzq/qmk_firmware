#include QMK_KEYBOARD_H
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"

// EEPROM can only have a single DWORD for storage, up to 32 bits.
// the same are defined for tight packaging (divided) here:
typedef union {
  uint32_t raw;
  struct {
    uint8_t      cpi_win :8; // Reads as uint8 but only stores 5 bits (0-31),
    uint8_t      cpi_mac :8; // so, these save up to 3100 CPI each.
  };
} user_config_t;

user_config_t user_config;

// Loads the CPI from EEPROM config
uint16_t eeprom_loadCpi(void) {
  if(LS_isBaseLayer(_MAC_OS))
    return user_config.cpi_mac * 100; // CPI values are multiplied
  return user_config.cpi_win * 100;   // by 100 in code to store as 5 bits
}

// Saves the CPI to EEPROM config
// we receive full int value, so we need to convert
void eeprom_saveCpi(uint16_t cpi){
  if (cpi > 3100)
    cpi = 3100; // Max allowed due to 5 bit limitation

  if(LS_isBaseLayer(_MAC_OS)){
    user_config.cpi_mac = cpi / 100;
  } else {
    user_config.cpi_win = cpi / 100;
  }
  eeconfig_update_user(user_config.raw);
}

void eeprom_loadUserConfig(void){
  user_config.raw = eeconfig_read_user();
}

// Resets EEPROM
void eeconfig_init_user(void) {  
  user_config.raw = 0; 
  user_config.cpi_mac = 10; // CPI values are multiplied by
  user_config.cpi_win = 7;  // a 100 in code to save space
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM
}