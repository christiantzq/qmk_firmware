#pragma once

// Setup in keyboard_post_init_user (qmk/life_cycle.c)
void eeprom_loadUserConfig(void);

// API
uint16_t eeprom_loadCpi(void);
void eeprom_saveCpi(uint16_t cpi);
