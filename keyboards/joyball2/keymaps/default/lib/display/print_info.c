#include QMK_KEYBOARD_H
#include "print_info.h"
#include "numbers.h"

/*
  This API allows you to display text temporarily to
  your master OLED screen on a given location.
*/

#define INFO_DISPLAY_TIME 7500 // Miliseconds to display de info
#define FLASHING_INTERVAL 500

bool isPrintInfoActive = false;
bool isPrintBigNumActive = false;
bool isFlashingActive = false;
uint16_t infoTimer = 0;
uint16_t bigNumTimer_ex = 0;
uint16_t flashingTimer = 0;
int8_t textRow = 0;
int8_t bigNumRow_ex = 0;
char* text;
int8_t bigNum = 0;
bool flashStatus = false;
uint8_t tens_digit = 0;
uint8_t units_digit = 0;

// Called in matrix_scan_user (lib/qmk/life_cycle.c)
void printInfo_timerHandler(void) {
  if (isPrintInfoActive) {
    if (timer_elapsed(infoTimer) > INFO_DISPLAY_TIME) {
      isPrintInfoActive = false;
      isFlashingActive = false;
      flashStatus = false;
    }
  }
  if (isPrintBigNumActive) {
    if (timer_elapsed(bigNumTimer_ex) > INFO_DISPLAY_TIME) {
      isPrintBigNumActive = false;
      isFlashingActive = false;
      flashStatus = false;
    }
  }
  if (isFlashingActive) {
    if (timer_elapsed(flashingTimer) > FLASHING_INTERVAL) {
      flashingTimer = timer_read();
      flashStatus = !flashStatus;
    }
  }
}

bool renderText(void) {
  if (is_keyboard_master() && isPrintInfoActive) {
    oled_set_cursor(0, textRow);
    oled_write(text, flashStatus);
    return true;
  }
  return false;
}

bool renderBigNum(void){
  if (is_keyboard_master() && isPrintBigNumActive) {
    if (bigNum < 0 || bigNum > 99) {
      oled_set_cursor(0,bigNumRow_ex);
      oled_write("?", false);
      return true;
    }
    
    tens_digit = bigNum / 10;
    units_digit = bigNum % 10;

    oled_set_cursor(0,bigNumRow_ex);
    oled_write_P(topNum[tens_digit], flashStatus);
    oled_write(" ", false);
    oled_write_P(topNum[units_digit], flashStatus);
    oled_write_P(lowNum[tens_digit], flashStatus);
    oled_write(" ", false);
    oled_write_P(lowNum[units_digit], flashStatus);
    return true;
  }
  return false;
}

// Called in oled_task_user
bool printInfo_renderHandler(void) {
  if (renderBigNum() || renderText()) {
    return true;
  }
  return false;
}

// API
void oled_printInfo(char* info, uint8_t row, bool flash) {
  infoTimer = timer_read();
  isPrintInfoActive = true;
  text = info;
  textRow = row;
  isFlashingActive = flash;
  flashStatus = flash;
  flashingTimer = timer_read();
}

// API
void oled_printBigNum(int8_t num, uint8_t row, bool flash){
  bigNumTimer_ex = timer_read();
  isPrintBigNumActive = true;
  bigNum = num;
  bigNumRow_ex = row;
  isFlashingActive = flash;
  flashStatus = flash;
  flashingTimer = timer_read();
}