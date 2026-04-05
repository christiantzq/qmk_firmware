#pragma once
#include QMK_KEYBOARD_H

//bool joystick_isHorizScroll; // Scrolling Horizontally?

// Setup in matrix_scan_user (qmk/life_cycle.c)
void joystick_readPins(void);

// Setup in housekeeping_task_user (qmk/life_cycle.c)
void joystick_postProcessing(void);

// Setup in pointing_device_task_user
//void joystick_processScrolling(report_mouse_t *mouse_report);

// API Reset Joystick Center
//void joystick_ResetMidValues(void);
//void joystick_CycleMode(void);