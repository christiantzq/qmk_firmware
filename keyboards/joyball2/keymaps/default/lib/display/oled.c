#include QMK_KEYBOARD_H
#include "oled.h"
#include "icons.h"
#include "./lib/layers/layers.h"
#include "./lib/mouse/pointer.h"

#define SCREEN_SAVER_TIMER 10000 // In milliseconds

uint16_t oledTimer = 0;
bool oled_isActive = true;      // Display is on by default

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
}

// Displays Caps Lock, Numpad Lock & Scroll Lock
void displayLocks(bool isMacOs) {
  if (is_keyboard_master()) // Slave only
    return;

  oled_set_cursor(0,10);
  led_t led_state = host_keyboard_led_state();
  oled_write(led_state.caps_lock   ? "CAP:    on" : "CAP:   off", false);
  if (!isMacOs) // Numpad Lock does not work on MacOS
    oled_write(led_state.num_lock    ? "NUM:    on" : "NUM:   off", false);
  oled_write(led_state.scroll_lock ? "SCR:    on" : "SCR:   off", false);
}

// =>                               ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  OLED Loop  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
bool oled_task_user(void) {
  oled_clear(); 

  if (!oled_isActive)
    return false; // Screen saver

  // Main display loop
  oled_set_cursor(0,0);
  switch (get_highest_layer(layer_state)) {
    case _LINUX:
      oled_write_P(linux_icon, false);
      oled_write(" BZT ", false);
      displayLocks(false);
      break;
    case _WINDOWS:
      oled_write_P(windows_icon, false);
      oled_write(" WIN ", false);
      displayLocks(false);
      break;
    case _MAC_OS:
      oled_write_P(mac_icon, false);
      oled_write("MacOS", false);
      displayLocks(true);
      break;
    case _GAME_S:
      oled_write_P(game_icon, false);
      oled_write("WASD ", false);
      displayLocks(false);
      break;
    case _GAME_R:
      oled_write_P(game_icon, false);
      oled_write(" RPG ", false);
      displayLocks(false);
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
      if (is_keyboard_master()) {
        oled_write("     CPI: ", false);
        oled_write(get_u16_str(mouse_getCpi(), ' '), false);
      }
  }

  return false;
}

// API to wake up oled (from screen saver)
void oled_wakeUpScreen(){
  oledTimer = timer_read(); 
  oled_isActive = true;
}