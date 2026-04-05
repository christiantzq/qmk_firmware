#include QMK_KEYBOARD_H
#include "pomodoro.h"
#include "./lib/display/oled.h"
// #include "./lib/display/print_info.h"
#include "./lib/audio/songs.h"

/*
Pomodoro Feature

Provides a complete, interactive Pomodoro timer for your keyboard, with 
visual feedback on the OLED and audio alerts.
*/


int8_t remainingMinutes = 0; // max 99 
int8_t remainingSeconds = 0;
bool isPomodoroActive = false;
bool isSettingTimer = false;
uint16_t timer = 0;
bool isManuallyCanceled = false;
bool isTimerPaused = false;
bool isTimeLengthChanged = false;
// char s1[21]; // Ouput String max 20 chars (5x4 matrix + EoL)


// Used in oled_process_render
void updateOledData(bool flashing) {
  oled_bigNumber(remainingMinutes, 5);
  // if (remainingSeconds % 2 == 0) {
  //   // snprintf(s1, sizeof(s1), "  :%02d> > >", remainingSeconds);
  //   //get_u16_str(remainingMinutes, ' ')
  //   snprintf(s1, sizeof(s1), "%02d:%02d> > >", remainingMinutes, remainingSeconds);
  // } else {
  //   // snprintf(s1, sizeof(s1), "  :%02d > > ", remainingSeconds);
  //   snprintf(s1, sizeof(s1), "%02d:%02d > > ", remainingMinutes, remainingSeconds);
  // }
  // // oled_printInfo(s1, 7, flashing);
  // oled_printInfo(s1, 5, flashing);
}


// Used in encoder_update_user
bool pomodoro_isSettingTime(void) {
  return isSettingTimer;
}

void pomodoro_add5Minutes(void) {
  if (isSettingTimer) {
    isTimeLengthChanged = true;
    remainingMinutes+=5;
    if (remainingMinutes > 99) { // 99 is max due to Oled width limit
      remainingMinutes = 99;
      remainingSeconds = 59;
      audio_playCapsOn(); // Signal the upper limit cap.
    }
    isPomodoroActive = true;
    updateOledData(false);
  }
}

void pomodoro_sub5Minutes(void) {
  if (isSettingTimer) {
    isTimeLengthChanged = true;
    remainingMinutes-=5;
    if (remainingMinutes <= 0) { // Canceling Pomodoro
      remainingMinutes = 0;
      remainingSeconds = 0;
      isPomodoroActive = false;
      isManuallyCanceled = true;
      //oled_printBigNum(0, 5, false);
      oled_printInfo("  :--X X X", 7, false);
      audio_playCapsOn(); // Signal the lower (thus cancelling) limit cap.
      return;
    }
    updateOledData(false);
  }
}

// Whenever the key is Hold, timer is paused and remaining time can be modified.
void updateTimeSettingState(bool isKeyPressed){
  if(isKeyPressed){
    isTimeLengthChanged = false;
    isSettingTimer = true;
  } else {
    isSettingTimer = false;
  }
}


// Used in process_record_user (keymap.c)
bool pomodoro_processKeyEvent(bool isKeyPressed) {
  updateTimeSettingState(isKeyPressed);

  if (isKeyPressed){
    // Nothing
  } else { // key has been released
    if (!isPomodoroActive 
        && remainingMinutes == 0 
        && remainingSeconds == 0
        && !isManuallyCanceled) {
      // Start a standard pomodoro
      isPomodoroActive = true;
      remainingMinutes = 25;
      timer = timer_read();
    } else if (isTimerPaused) {
      isTimerPaused = false;
    } else if (isPomodoroActive
      && !isTimeLengthChanged
      && (remainingMinutes > 0 || remainingSeconds > 0) ) {
        isTimerPaused = true;
    }
  }

  isManuallyCanceled = false;
  return false;
}


// Used in matrix_scan_user (qmk/life_cycle.c)
void pomodoro_timerHandler(void) {
  if (isPomodoroActive && !isSettingTimer && !isTimerPaused) {
    if (timer_elapsed(timer) >= 1000) {
      timer = timer_read();
      remainingSeconds--;
      if (remainingSeconds == 0 && remainingMinutes == 0) { // Timer is off!!
        isPomodoroActive = false;
        remainingSeconds = 0;
        oled_printInfo("PO  OMO  VDO  ERO  R", 8, true);
        audio_playZeldaSecret();
      } else { // Continue the count-down
        if (remainingSeconds < 0) {
          remainingSeconds = 59;
          remainingMinutes--;
        }
        updateOledData(false);
      }
    }
  }
}