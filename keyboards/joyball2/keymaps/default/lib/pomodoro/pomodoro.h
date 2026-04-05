#pragma once


// Setup a Keycode in process_record_user
bool pomodoro_processKeyEvent(bool isKeyPressed);

// Setup in matrix_scan_user (qmk/life_cycle.c)
void pomodoro_timerHandler(void);

// API
bool pomodoro_isSettingTime(void);
void pomodoro_add5Minutes(void);
void pomodoro_sub5Minutes(void);