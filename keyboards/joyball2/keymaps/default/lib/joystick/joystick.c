#include QMK_KEYBOARD_H
#include "analog.h"
#include "joystick.h"

int16_t xPos;     // Current Joystick X position
int16_t yPos;     // Current Joystick Y position
enum JoystickMode selectedMode = 0;

bool movingUp = false;
bool movingDown = false;
bool movingLeft = false;
bool movingRight = false;

// =>                          ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  Joystick Setup  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
#define JOY_THRESHOLD 128 // For Key mapping
#define JOY_MID_POINT 512

joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  JOYSTICK_AXIS_IN(GP28, 0, 511, 1023), // x axis
  JOYSTICK_AXIS_IN(GP29, 0, 511, 1023)  // y axis
};

// This needs to be called constantly (Matrix Scan)
void joystick_readPins(void) {
  if (!is_keyboard_master())
  return; // Master Keyboard Only

  xPos = analogReadPin(GP28);   // Read raw pin data x axis
  yPos = analogReadPin(GP29);   // Read raw pin data y axis  
}

// Sets the Joystick mode
void joystick_setMode(enum JoystickMode mode) {
  selectedMode = mode;
}

// Gets the Joystick mode
enum JoystickMode joystick_getMode(void) {
  return selectedMode;
}

// Mode round robin forward
void joystick_cycleMode(void) {
  if (selectedMode == JOY_LAST_MODE) {
    selectedMode = 0;
    return;
  }
  selectedMode++;
}

// =>                               ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  WASD Mode  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
void wasdMode(void) {
  if (yPos < (JOY_MID_POINT-JOY_THRESHOLD) && !movingUp) {
    movingUp = true;
    register_code(KC_W);
  } else if (yPos >= (JOY_MID_POINT-JOY_THRESHOLD) && movingUp) {
    movingUp = false;
    unregister_code(KC_W);
  }

  if (yPos > (JOY_MID_POINT+JOY_THRESHOLD) && !movingDown) {
    movingDown = true;
    register_code(KC_S);
  } else if (yPos <= (JOY_MID_POINT+JOY_THRESHOLD) && movingDown) {
    movingDown = false;
    unregister_code(KC_S);
  }
  
  if (xPos < (JOY_MID_POINT-JOY_THRESHOLD) && !movingLeft) {
    movingLeft = true;
    register_code(KC_A);
  } else if (xPos >= (JOY_MID_POINT-JOY_THRESHOLD) && movingLeft) {
    movingLeft = false;
    unregister_code(KC_A);
  }

  if (xPos > (JOY_MID_POINT+JOY_THRESHOLD) && !movingRight) {
    movingRight = true;
    register_code(KC_D);
  } else if (xPos <= (JOY_MID_POINT+JOY_THRESHOLD) && movingRight) {
    movingRight = false;
    unregister_code(KC_D);
  }
}

// =>                             ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  Arrows Mode  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
void arrowsMode(void) {
  if (yPos < (JOY_MID_POINT-JOY_THRESHOLD) && !movingUp) {
    movingUp = true;
    register_code(KC_UP);
  } else if (yPos >= (JOY_MID_POINT-JOY_THRESHOLD) && movingUp) {
    movingUp = false;
    unregister_code(KC_UP);
  }

  if (yPos > (JOY_MID_POINT+JOY_THRESHOLD) && !movingDown) {
    movingDown = true;
    register_code(KC_DOWN);
  } else if (yPos <= (JOY_MID_POINT+JOY_THRESHOLD) && movingDown) {
    movingDown = false;
    unregister_code(KC_DOWN);
  }
  
  if (xPos < (JOY_MID_POINT-JOY_THRESHOLD) && !movingLeft) {
    movingLeft = true;
    register_code(KC_LEFT);
  } else if (xPos >= (JOY_MID_POINT-JOY_THRESHOLD) && movingLeft) {
    movingLeft = false;
    unregister_code(KC_LEFT);
  }

  if (xPos > (JOY_MID_POINT+JOY_THRESHOLD) && !movingRight) {
    movingRight = true;
    register_code(KC_RGHT);
  } else if (xPos <= (JOY_MID_POINT+JOY_THRESHOLD) && movingRight) {
    movingRight = false;
    unregister_code(KC_RGHT);
  }
}

void joystick_postProcessing(void) {
  if (!is_keyboard_master())
    return; // Master Keyboard Only

  switch (selectedMode) {
    case _JOY_WASD:
      wasdMode();
      break;
    case _JOY_ARROWS:
      arrowsMode();
      break;
    default:
      break;
  }
}