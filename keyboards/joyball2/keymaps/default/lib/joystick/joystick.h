#pragma once

// Setup

enum JoystickMode {
    _JOY_WASD   = 0,
    _JOY_ARROWS = 1,
    _JOY_PURE   = 2
};

#define JOY_LAST_MODE 2

// Setup in matrix_scan_user (qmk/life_cycle.c)
void joystick_readPins(void);

// Setup in housekeeping_task_user (qmk/life_cycle.c)
void joystick_postProcessing(void);


// API
void joystick_setMode(enum JoystickMode);
enum JoystickMode joystick_getMode(void);
void joystick_cycleMode(void);