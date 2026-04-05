#include QMK_KEYBOARD_H
#include "oled.h"
// #include "print_info.h"
#include "icons.h"
// #include "numbers.h"
#include "./lib/layers/layers.h"


#define SCREEN_SAVER_TIMER 10000 // In milliseconds

uint16_t oledTimer = 0;
bool oled_isActive = true;      // Display is on by default

// Big Number Data
#define BIG_NUM_TIMER_MAX 7500 // In milliseconds

uint16_t bigNumTimer = 0; // 0 = disabled
//int8_t bigNum = 0; // really required?
uint8_t bigNum_tens_digit = 0;
uint8_t bigNum_units_digit = 0;
int8_t bigNumRow = 5; // At what hight starts to display



// Oled initial setup
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}



// Used in matrix_scan_user (qmk/life_cycle.c)
void oled_timerHandler(void) {
  if (!is_keyboard_master())
    return;
  
  if(oledTimer == 0) // Screen saver timer, always running
    oledTimer = timer_read(); 

  if (timer_elapsed(oledTimer) > SCREEN_SAVER_TIMER) {
    oled_isActive = false;
  }

  if (bigNumTimer > 0 && timer_elapsed(oledTimer) > BIG_NUM_TIMER_MAX) {
    bigNumTimer = 0; // Big Number Displaying deactivated
  }
}

// API Queue big number display
void oled_bigNumber(uint8_t value, uint8_t row) {
  if (value < 0 || value > 99) // Only from 0 to 99 allowed
    return;
  
  bigNumTimer = timer_read(); // Request resets timer
  bigNum_tens_digit = value / 10;
  bigNum_units_digit = value % 10;
}

// Display big number while its timer is valid
void processBigNumber(void) {
  // if (bigNumTimer > 0) {
  //   oled_set_cursor(0,bigNumRow);
  //   oled_write_P(topNum[bigNum_tens_digit], false);
  //   oled_write(" ", false);
  //   oled_write_P(topNum[bigNum_units_digit], false);
  //   oled_write_P(lowNum[bigNum_tens_digit], false);
  //   oled_write(" ", false);
  //   oled_write_P(lowNum[bigNum_units_digit], false);
  // }
}


// Displays Windows Icon, Mac Icon, Gaming... etc.
void displayLayerIcon(void) {
  oled_set_cursor(0,0);
  switch (get_highest_layer(layer_state)) {
    case _WINDOWS:
      oled_write_P(windows_icon, false);
      oled_write(" WIN ", false);
      break;
    case _MAC_OS:
      oled_write_P(mac_icon, false);
      oled_write("MacOS", false);
      break;
    case _GAMING:
      oled_write_P(game_icon, false);
      oled_write("GAMES", false);
      break;
    case _SYMBOL:
      oled_write_P(symbol_icon, false);
      oled_write(" SYM ", false);
      break;
    case _NUMPAD:
      oled_write_P(numpad_icon, false);
      oled_write(" NUM ", false);
      break;
    case _FUNCTION:
      oled_write_P(function_icon, false);
      oled_write("FUNCT", false);
      break;
    case _CONFIG:
      oled_write_P(config_icon, false);
      oled_write("CONFG", false);
  }
}


// Displays Caps Lock, Numpad Lock & Scroll Lock
void displayLocks(void) {
  oled_set_cursor(0,10);
  switch (get_highest_layer(layer_state)) {
    case _WINDOWS:
    case _MAC_OS:
    case _GAMING:
      led_t led_state = host_keyboard_led_state();
      oled_write(led_state.caps_lock   ? "CAP:    on" : "CAP:   off", false);
      oled_write(led_state.num_lock    ? "NUM:    on" : "NUM:   off", false);
      oled_write(led_state.scroll_lock ? "SCR:    on" : "SCR:   off", false);
      break;
  }
}

void displayInfoQueue(void){
  oled_set_cursor(0,5);
  processBigNumber();
}

bool oled_task_user(void) {
  oled_clear();

  if (oled_isActive && is_keyboard_master()){ // Master side
    displayLayerIcon();
  } else if (oled_isActive && !is_keyboard_master()) { // Slave side
    displayLayerIcon();
    displayLocks();
  } else { // Screensaver (any side)

  } 

  //if (!is_keyboard_master())
    //return false;

  //displayInfoQueue();



  // Handle render requests
  // if (printInfo_renderHandler()) {
  //   //oled_write("prted", false);
  // }

  // if (!oled_isActive)
  //   return false; // Screen saver

  // if(!isOledTimerActive) {
  //   isOledTimerActive = true; 
  //   oledTimer = timer_read(); // Reset screen saver timer 
  // }

  

  
  //oled_write(get_u16_str(oled_counter, ' '), false);
  return false;
}


// API to wake up oled (from screen saver)
void oled_wakeUpScreen(){
  oledTimer = timer_read(); 
  oled_isActive = true;
}