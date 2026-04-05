#pragma once

// Setup this in matrix_scan_user (lib/qmk/life_cycle.c)
void printInfo_timerHandler(void);


// Setup this in oled_process_render
bool printInfo_renderHandler(void); // returns true if printed something


// API
void oled_printInfo(char* info, uint8_t row, bool flash);
void oled_printBigNum(int8_t num, uint8_t row, bool flash);