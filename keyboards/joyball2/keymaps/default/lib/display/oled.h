#pragma once

// Used by Sync (slave comms)
bool oled_isActive;

// Setup this in matrix_scan_user (qmk/life_cycle.c)
void oled_timerHandler(void);

// API to wake up oled (from screen saver)
void oled_wakeUpScreen(void);
void oled_bigNumber(uint8_t value, uint8_t row);