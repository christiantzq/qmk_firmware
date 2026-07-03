#include QMK_KEYBOARD_H
#include "analog.h"
#include "joystick.h"

int16_t xPos;     // Current Joystick X position
int16_t yPos;     // Current Joystick Y position
#define JOY_THRESHOLD 128
bool movingUp = false;
bool movingDown = false;
bool movingLeft = false;
bool movingRight = false;


// Joystick Setup
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  JOYSTICK_AXIS_IN(GP28, 0, 512, 1023), // x
  JOYSTICK_AXIS_IN(GP29, 0, 512, 1023)  // y
};

// This needs to be called constantly (Matrix Scan)
void joystick_readPins(void) {
  if (!is_keyboard_master())
    return; // Master Keyboard Only

  xPos = analogReadPin(GP28);   // Read raw pin data x axis
  yPos = analogReadPin(GP29);   // Read raw pin data y axis  
}

void joystick_postProcessing(void) {
  if (!is_keyboard_master())
    return; // Master Keyboard Only

  // Arrow Key Behaviour
  if (yPos < (512-JOY_THRESHOLD) && !movingUp) {
    movingUp = true;
    //register_code(KC_UP);
    register_code(KC_W);
  } else if (yPos >= (512-JOY_THRESHOLD) && movingUp) {
    movingUp = false;
    //unregister_code(KC_UP);
    unregister_code(KC_W);
  }

  if (yPos > (512+JOY_THRESHOLD) && !movingDown) {
    movingDown = true;
    //register_code(KC_DOWN);
    register_code(KC_S);
  } else if (yPos <= (512+JOY_THRESHOLD) && movingDown) {
    movingDown = false;
    // unregister_code(KC_DOWN);
    unregister_code(KC_S);
  }
  
  if (xPos < (512-JOY_THRESHOLD) && !movingLeft) {
    movingLeft = true;
    // register_code(KC_LEFT);
    register_code(KC_A);
  } else if (xPos >= (512-JOY_THRESHOLD) && movingLeft) {
    movingLeft = false;
    // unregister_code(KC_LEFT);
    unregister_code(KC_A);
  }

  if (xPos > (512+JOY_THRESHOLD) && !movingRight) {
    movingRight = true;
    // register_code(KC_RGHT);
    register_code(KC_D);
  } else if (xPos <= (512+JOY_THRESHOLD) && movingRight) {
    movingRight = false;
    unregister_code(KC_D);
  }

}