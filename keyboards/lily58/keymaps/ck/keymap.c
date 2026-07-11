#include QMK_KEYBOARD_H
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"
#include "analog.h"
#include "math.h"
#include "action.h"
#include "keyboard.h"

// =>                           ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Custom Keycodes ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
enum my_keycodes {
  CK_SCS = SAFE_RANGE, // Clipboard cropped snippet (screenshot)
  CK_WCS,              // Wizard cropped snippet (screenshot)
  CK_LNST,             // Go to line start
  CK_LNED,             // Go to line end
  CK_LYER,             // Base Layer toggle/switcher key
  CK_ENT3,             // onHold: Layer3 | onTap: ENTER
  CK_DEL3,              // onHold: Layer3 | onTap: DEL
  CK_ATB,             // Alt+Tab
};

// =>                  ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ OS Base Layers Key codes ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
#define HY_ESC  ALL_T(KC_ESC)   // onHold: Hyper | onTap: ESC
#define HRW_A   LGUI_T(KC_A)    // Homerow A/Win
#define HRW_S   LALT_T(KC_S)    // Homerow S/Alt
#define HRW_D   LCTL_T(KC_D)    // Homerow D/Ctrl
#define HRW_F   LSFT_T(KC_F)    // Homerow F/Shift
#define HRW_J   RSFT_T(KC_J)    // Homerow J/Shift
#define HRW_K   RCTL_T(KC_K)    // Homerow K/Ctrl
#define HRW_L   LALT_T(KC_L)    // Homerow L/Alt
#define HRW_QT  LGUI_T(KC_QUOT) // Homerow '/Win
#define HRM_A   LCTL_T(KC_A)    // Mac Homerow A/Ctrl (Mac layer switcheroo)
#define HRM_D   LGUI_T(KC_D)    // Mac Homerow D/Cmd (Mac layer switcheroo)
#define HRM_K   LGUI_T(KC_K)    // Mac Homerow K/Cmd (Mac layer switcheroo)
#define HRM_QT  RCTL_T(KC_QUOT) // Mac Homerow '/Ctrl (Mac layer switcheroo)
#define HRS_A   LGUI_T(KC_PERC) // Symbol Homerow % / Win
#define HRS_S   LALT_T(KC_AMPR) // Symbol Homerow & / Alt
#define HRS_D   LCTL_T(KC_PIPE) // Symbol Homerow | / Ctrl
#define HRS_F   LSFT_T(KC_LPRN) // Symbol Homerow ( / Shift
#define W_COPY  LCTL(KC_C)      // Copy (Windows)
#define M_COPY  LGUI(KC_C)      // Copy (Mac)
#define W_PASTE  LCTL(KC_V)     // Paste (Windows)
#define M_PASTE  LGUI(KC_V)     // Paste (Mac)
#define L4_SPC  LT(4,KC_SPC)    // onHold: NumLayer | onTap: SPACE
#define AT_TB   LALT(KC_TAB)    // Alt+Tab
#define SF_F10  LSFT(KC_F10)      // Shift + F10

// =>                             ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Keymap Matrix ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  <x  |
  * |------+------+------+------+------+------|  (+)  |    |  Vol  |------+------+------+------+------+------|
  * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   |LCtrl | LAlt |Space | /  DEL  /       \Enter \  |Space |Arrows| RWin |
  *                   |      |      |      |/       /         \      \ |      |(joy) |      |
  *                   `----------------------------'           '------''--------------------'
  */
  [_WINDOWS] = LAYOUT( // 0
    KC_GRV,   KC_1,   KC_2,   KC_3,     KC_4,     KC_5,                       KC_6,   KC_7,     KC_8,     KC_9,   KC_0,    KC_MINS, 
    KC_TAB,   KC_Q,   KC_W,   KC_E,     KC_R,     KC_T,                       KC_Y,   KC_U,     KC_I,     KC_O,   KC_P,    KC_EQL, 
    HY_ESC,   HRW_A,  HRW_S,  HRW_D,    HRW_F,    KC_G,                       KC_H,   HRW_J,    HRW_K,    HRW_L,  HRW_QT,  KC_BSPC, 
    KC_LSFT,  KC_Z,   KC_X,   KC_C,     KC_V,     KC_B,   CK_WCS,  CK_LYER,  KC_N,   KC_M,     KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, 
                              KC_LCTL,  KC_LALT,  L4_SPC, CK_DEL3,  CK_ENT3,  L4_SPC, XXXXXXX,  KC_RGUI
  ),

  [_MAC_OS] = LAYOUT( // 1
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, 
    _______, HRM_A,   _______, HRM_D,   _______, _______,                     _______, _______, HRM_K,   _______, HRM_QT,  _______, 
    _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, 
                               _______, KC_LGUI, _______, _______,  _______,  _______, XXXXXXX, KC_RALT
  ),  
  
  [_GAMING] = LAYOUT( // 2
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, 
    _______,  KC_A,    KC_S,    KC_D,    KC_F,   _______,                     _______, KC_J,    KC_K,    KC_L,    KC_QUOT, _______, 
    _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, 
                               _______, KC_LALT, _______, _______,  _______,  _______, XXXXXXX, KC_RGUI
  ),
  
  [_SYMBOL] = LAYOUT( // 3
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
    KC_BSLS, KC_EXLM, KC_AT,   KC_HASH, KC_LBRC, KC_RBRC,                     KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, MS_WHLU, KC_ESC, 
    KC_ESC,  KC_PERC, KC_AMPR, KC_PIPE, KC_LPRN, KC_RPRN,                     KC_VOLD, MS_BTN1, MS_BTN3, MS_BTN2, MS_WHLD, _______, 
    _______, KC_CIRC,  KC_DLR, KC_ASTR, KC_LCBR, KC_RCBR, CK_SCS,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, 
                               _______, _______, _______, KC_DEL,   KC_ENT,   _______ , XXXXXXX, _______
  ),
  [_NUM_FN] = LAYOUT( // 4
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, 
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_7,    KC_8,    KC_9,    KC_PPLS, XXXXXXX, 
    KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, _______, 
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PDOT, _______, 
                               _______, _______, KC_SPC , KC_DEL,   KC_ENT,   KC_0,    XXXXXXX, KC_PDOT
  )
};

// =>                                  ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Joystick ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗

#define JMT 7 // Stop joystick processing below this threshold (aids throttling)
#define JOY_TO_KEY 17 // Joystick registers as key press above this value (from center)
#define JOY_KEY_LOWER_THRESHOLD 50 - JOY_TO_KEY  // These translate to the actual 
#define JOY_KEY_HIGHER_THRESHOLD 50 + JOY_TO_KEY // values to compare with (0-50)

int16_t xMin = 180; // In theory, these should have 0 to 1023 range but
int16_t xMax = 870; // manual measurements using oled
int16_t yMin = 190; // indicate that these hardcoded values are much more accurate.
int16_t yMax = 880; // Anyway, they automatically update over time to improve tracking.

int16_t xPos = 512;     // Current Joystick X position
int16_t yPos = 512;     // Current Joystick Y position

int16_t old_xPos = 512; // Previous Joystick X position (aids throttling)
int16_t old_yPos = 512; // Previous Joystick Y position (aids throttling)

double angle = 0.0; // 0 to 359 degrees (Right is 0, increases clockwise)
double normX = 0; // Holds the normalized x axis value (0 to 100)
double normY = 0; // Holds the normalized y axis value (0 to 100)
double joyDistFromCenter = 0.0; // How far from center is the Joystick (0 to 50)

bool joystickMouse = false; // Determines if Joystick is a being used as Mouse
int8_t mouseUpdateDelimiter = 0; // For throttling
bool isJoyMoving = false; // Helps throttle the joystick processing

bool yDownHeld = false;   // These are used to 
bool yUpHeld = false;     // track when the joystick 
bool xLeftHeld = false;   // is being used as 
bool xRightHeld = false;  // the arrow keys

bool recordingMacro = false; // TODO: This should not be here

// Default setup
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  JOYSTICK_AXIS_IN(F4, 0, 512, 1023),
  JOYSTICK_AXIS_IN(F5, 0, 512, 1023)
};

// Matrix Scan (be careful; runs every single tick)
void matrix_scan_user(void) {
  if (!is_keyboard_master())
    return; // Master Keyboard Only
  
  xPos = analogReadPin(F4);   // Read raw pin data x axis
  yPos = analogReadPin(F5);   // Read raw pin data y axis

  if ( xPos < old_xPos - JMT      // Checks if the dead-zone processing threshold
    || xPos > old_xPos + JMT      // was surpassed. Basically helps throttle by 
    || yPos < old_yPos - JMT      // stopping the joystick processing
    || yPos > old_yPos + JMT ) {  // unless it's moved.
    isJoyMoving = true;
    old_xPos = xPos;  // Remember joystick
    old_yPos = yPos;  // position for latter
  }

  // Base Layer Toggler
  layerSwitcher_timerHandler();
}

// Stops any ongoing arrow movement
void clearArrowMovement(void) {
  unregister_code(KC_RGHT);
  unregister_code(KC_LEFT);
  unregister_code(KC_UP);
  unregister_code(KC_DOWN);
}

// This executes after all other homework has finished
void housekeeping_task_user(void) {
  if (!isJoyMoving || !is_keyboard_master())
    return; // Helps throttling as this also runs a lot.

  isJoyMoving = false; // Reset movement
  xMin = (xMin > xPos) ? xPos : xMin; // Update x axis min  ╗
  xMax = (xMax < xPos) ? xPos : xMax; // Update x axis max  ║ Improves tracking
  yMin = (yMin > yPos) ? yPos : yMin; // Update y axis min  ║ over time.
  yMax = (yMax < yPos) ? yPos : yMax; // Update y axis max  ╝
  normX = (double) (xPos - xMin) / (xMax - xMin) * 100;       // Normalize x axis (0 to 100)
  normY = (double) (yPos - yMin) / (yMax - yMin) * 100;       // Normalize y axis (0 to 100)
  // Calculates the joystick's distance from the center (0 to 50)
  joyDistFromCenter = sqrt(pow(normX - 50, 2) + pow(normY - 50, 2));
  
  // => Joystick Behaviour
  switch (get_highest_layer(layer_state)) {
    case _WINDOWS:  // When layer is Windows, 
    case _MAC_OS:   // MacOs or Gaming, the joystick 
    case _GAMING:   // functions as the arrow keys.
      // Up and Down
      if (!yDownHeld && normY >= JOY_KEY_HIGHER_THRESHOLD) {
        yDownHeld = true;
        register_code(KC_DOWN);
      } else if (yDownHeld && normY < JOY_KEY_HIGHER_THRESHOLD) {
        yDownHeld = false;
        unregister_code(KC_DOWN);
      } else if (!yUpHeld && normY <= JOY_KEY_LOWER_THRESHOLD) {
        yUpHeld = true;
        register_code(KC_UP);
      } else if (yUpHeld && normY > JOY_KEY_LOWER_THRESHOLD) {
        yUpHeld = false;
        unregister_code(KC_UP);
      }
      // Left and Right
      if (!xLeftHeld && normX >= JOY_KEY_HIGHER_THRESHOLD) {
        xLeftHeld = true;
        register_code(KC_RGHT);
      } else if (xLeftHeld && normX < JOY_KEY_HIGHER_THRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_RGHT);
      } else if (!xRightHeld && normX <= JOY_KEY_LOWER_THRESHOLD) {
        xRightHeld = true;
        register_code(KC_LEFT);
      } else if (xRightHeld && normX > JOY_KEY_LOWER_THRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_LEFT);
      }
      break;
    case _NUM_FN: // If layer is Num-pad, the joystick is a Mouse Scroller
      // Up and Down
      if (!yDownHeld && normY >= JOY_KEY_HIGHER_THRESHOLD) {
        yDownHeld = true;
        (LS_isBaseLayer(_MAC_OS)) ? register_code(MS_WHLU) : register_code(MS_WHLD);
      } else if (yDownHeld && normY < JOY_KEY_HIGHER_THRESHOLD) {
        yDownHeld = false;
        (LS_isBaseLayer(_MAC_OS)) ? unregister_code(MS_WHLU) : unregister_code(MS_WHLD);
      } else if (!yUpHeld && normY <= JOY_KEY_LOWER_THRESHOLD) {
        yUpHeld = true;
        (LS_isBaseLayer(_MAC_OS)) ? register_code(MS_WHLD) : register_code(MS_WHLU);
      } else if (yUpHeld && normY > JOY_KEY_LOWER_THRESHOLD) {
        yUpHeld = false;
        (LS_isBaseLayer(_MAC_OS)) ? unregister_code(MS_WHLD) : unregister_code(MS_WHLU);
      }
      // Left and Right
      if (!xLeftHeld && normX >= JOY_KEY_HIGHER_THRESHOLD) {
        xLeftHeld = true;
        (LS_isBaseLayer(_MAC_OS)) ? register_code(MS_WHLL) : register_code(MS_WHLR);
      } else if (xLeftHeld && normX < JOY_KEY_HIGHER_THRESHOLD) {
        xLeftHeld = false;
        (LS_isBaseLayer(_MAC_OS)) ? unregister_code(MS_WHLL) : unregister_code(MS_WHLR);
      } else if (!xRightHeld && normX <= JOY_KEY_LOWER_THRESHOLD) {
        xRightHeld = true;
        (LS_isBaseLayer(_MAC_OS)) ? register_code(MS_WHLR) : register_code(MS_WHLL);
      } else if (xRightHeld && normX > JOY_KEY_LOWER_THRESHOLD) {
        xRightHeld = false;
        (LS_isBaseLayer(_MAC_OS)) ? unregister_code(MS_WHLR) : unregister_code(MS_WHLL);
      }
      clearArrowMovement();
      break;
    case _SYMBOL: // Joystick will be a Mouse Pointer (Mouse Report does the movement)
      // Calculate angle, goes from -180 to 180 degrees
      angle = atan2(normY - 50, normX - 50) * 180 / M_PI;
      // Convert angle to 0-360 degrees, 0 is right, increases clockwise
      angle = fmod(angle + 360.0, 360.0);
      clearArrowMovement();
      break;
    default: // Unknown Layer, disable all movement
      angle = 0;
      yDownHeld = 0;
      yUpHeld = 0;
      xLeftHeld = 0;
      xRightHeld = 0;
      clearArrowMovement();
      break;
  }
}

// =>          ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Pointing Device (Custom: Joycon) ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
bool pointing_device_driver_init(void) { return true; }
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
  if (!is_keyboard_master())
    return mouse_report;

  mouseUpdateDelimiter++;
  if (joystickMouse && joyDistFromCenter >= 5 && mouseUpdateDelimiter >= 12) {
      mouseUpdateDelimiter = 0; 
      int8_t speed = 1;
      if (joyDistFromCenter >= 25)
        speed=3;
      if (joyDistFromCenter >= 44)
        speed=9;
      if((angle >= 0 && angle < 22)||(angle >= 337 && angle <= 360)){
        //east
        mouse_report.x = 3 * speed;
      } else if (angle >= 22 && angle < 67){
        // south-east
        mouse_report.x = 2 * speed;
        mouse_report.y = 2 * speed;
      } else if (angle >= 67 && angle < 112){
        // south
        mouse_report.y = 3 * speed;
      } else if (angle >= 112 && angle < 157){
        // south-west
        mouse_report.x = -2 * speed;
        mouse_report.y = 2 * speed;
      } else if (angle >= 157 && angle < 202){
        // west
        mouse_report.x = -3 * speed;
      } else if (angle >= 202 && angle < 247){
        // north-west
        mouse_report.x = -2 * speed;
        mouse_report.y = -2 * speed;
      } else if (angle >= 247 && angle < 292){
        // north
        mouse_report.y = -3 * speed;
      } else if (angle >= 292 && angle < 337){
        // north-east
        mouse_report.x = 2 * speed;
        mouse_report.y = -2 * speed;
      }
      // mouse_report.h = mouse_report.x;
      // mouse_report.v = mouse_report.y;
  } else if ( joyDistFromCenter < 5 ) {
    mouseUpdateDelimiter = 12; // fixes delay on movement bug
  } else {
    mouse_report.x = 0;
    mouse_report.y = 0;
  }

  return mouse_report; 
}
uint16_t pointing_device_driver_get_cpi(void) { return 500; }
void pointing_device_driver_set_cpi(uint16_t cpi) {}


// =>                                      ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ OLED ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
#ifdef OLED_ENABLE
// Display Icon Locations
static void render_icon(enum LayerName layer) {
  static const char PROGMEM windows_icon[] = {
    0x95, 0x9a, 0x9b, 0x9c, 0x99, 
    0xb5, 0xba, 0xbb, 0xbc, 0xb9, 
    0xd5, 0xda, 0xdb, 0xdc, 0xd9, 0x00
  };
  static const char PROGMEM mac_icon[] = {
    0x95, 0x96, 0x97, 0x98, 0x99, 
    0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0x00
  };
  static const char PROGMEM game_icon[] = {
    0x95, 0x3d, 0x3e, 0x3f, 0x99, 
    0xb5, 0x5d, 0x5e, 0x5f, 0xb9, 
    0xd5, 0x7d, 0x7e, 0x7f, 0xd9, 0x00
  };
  static const char PROGMEM symbol_icon[] = {
    0x95, 0x92, 0x93, 0x94, 0x99, 
    0xb5, 0xb2, 0xb3, 0xb4, 0xb9, 
    0xd5, 0xd2, 0xd3, 0xd4, 0xd9, 0x00
  };
  static const char PROGMEM numpad_icon[] = {
    0x95, 0x9d, 0x9e, 0x9f, 0x99, 
    0xb5, 0xbd, 0xbe, 0xbf, 0xb9, 
    0xd5, 0xdd, 0xde, 0xdf, 0xd9, 0x00
  };
  switch (layer) {
    case _WINDOWS:
      oled_write_P(windows_icon, false);
      break;
    case _MAC_OS:
      oled_write_P(mac_icon, false);
      break;
    case _GAMING:
      oled_write_P(game_icon, false);
      break;
    case _SYMBOL:
      oled_write_P(symbol_icon, false);
    break;
    case _NUM_FN:
      oled_write_P(numpad_icon, false);
    break;
    default:
    break;
  }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void oled_display_locks(void) {
  oled_set_cursor(0,10);
  led_t led_state = host_keyboard_led_state();
  oled_write(led_state.num_lock    ? "NUM:    on" : "NUM:   off", false);
  oled_write(led_state.caps_lock   ? "CAP:    on" : "CAP:   off", false);
  oled_write(led_state.scroll_lock ? "SCR:    on" : "SCR:   off", false);
}

bool oled_task_user(void) {
  oled_clear();
  oled_set_cursor(0,0);
  switch (get_highest_layer(layer_state)) {
    case _WINDOWS:      
      render_icon(_WINDOWS);
      oled_write(" WIN ", false);
      // if(isJoyMoving){
      // oled_write(get_u16_str(xPos, ' '), false);
      // oled_write(get_u16_str(yPos, ' '), false);
      // } 
      //oled_write(get_u16_str(my_function(), ' '), false);
      oled_display_locks();
      break;
    case _MAC_OS:
      render_icon(_MAC_OS);
      oled_write("MacOS", false);
      oled_display_locks();
      break;
    case _GAMING:
      render_icon(_GAMING);
      oled_write("GAMES", false);
      oled_display_locks();
      break;
    case _SYMBOL:
      render_icon(_SYMBOL);
      oled_write("#$*&@", false);
      if (is_keyboard_master()) {
        oled_set_cursor(0,10);
        oled_write("DfC: ", false);
        oled_write(get_u16_str(joyDistFromCenter, ' '), false);
        oled_write("ANG: ", false);
        oled_write(get_u16_str(angle, ' '), false);
        oled_write("Lim: ", false);
        oled_write(get_u16_str(mouseUpdateDelimiter, ' '), false);
      }
      break;
    }
  return false;
}
#endif




// =>            ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Combos (Quick Key Combination) ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
const uint16_t PROGMEM combo01[] = {KC_COMM, KC_DOT,  COMBO_END};  // ',' + '.' = ';'
const uint16_t PROGMEM combo02[] = {KC_SPC,  CK_DEL3,  COMBO_END};  // ' ' + Del = Enter
const uint16_t PROGMEM combo03[] = {KC_Z,    KC_X,    COMBO_END};  // 'Z' + 'X' = Home
const uint16_t PROGMEM combo04[] = {KC_DOT,  KC_SLSH, COMBO_END};  // '.' + '/' = End
const uint16_t PROGMEM combo05[] = {KC_N,    KC_M,    COMBO_END};  // 'N' + 'M' = End
const uint16_t PROGMEM combo06[] = {KC_V,    KC_B,    COMBO_END};  // 'V' + 'B' = Home
const uint16_t PROGMEM combo07[] = {KC_2,    KC_W,    COMBO_END};  // 2 + W = PgUp
const uint16_t PROGMEM combo08[] = {KC_9,    KC_O,    COMBO_END};  // 9 + O = PgDn
const uint16_t PROGMEM combo09[] = {KC_C,    HRW_D,   COMBO_END};  // D + C = Copy(Win)
const uint16_t PROGMEM combo10[] = {KC_C,    HRM_D,   COMBO_END};  // D + C = Copy(Mac)
const uint16_t PROGMEM combo11[] = {KC_V,    HRW_D,   COMBO_END};  // V + C = Paste(Win)
const uint16_t PROGMEM combo12[] = {KC_V,    HRM_D,   COMBO_END};  // V + C = Paste(Mac)
const uint16_t PROGMEM combo13[] = {KC_O,    HRW_L,   COMBO_END};  // L + O = Alt+Tab
const uint16_t PROGMEM combo14[] = {KC_9,    HRW_F,   COMBO_END};  // Shift + 9 = Shift + F10

combo_t key_combos[] = {
  COMBO(combo01, KC_SCLN),       // Comma + Dot = Semicolon
  COMBO(combo02, KC_ENT),        // Space + Delete = Enter
  COMBO(combo03, CK_LNST),       // 'Z' + 'X' = Home
  COMBO(combo04, CK_LNED),       // '.' + '/' = End
  COMBO(combo05, CK_LNED),       // 'N' + 'M' = End
  COMBO(combo06, CK_LNST),       // 'V' + 'B' = Home
  COMBO(combo07, KC_PGUP),       // 2 + W = PgUp
  COMBO(combo08, KC_PGDN),       // 9 + O = PgDn
  COMBO(combo09, W_COPY),        // D + C = Copy (Windows)
  COMBO(combo10, M_COPY),        // D + C = Copy (Mac OS)
  COMBO(combo11, W_PASTE),       // V + C = Paste (Windows)
  COMBO(combo12, M_PASTE),       // V + C = Paste (Mac)
  COMBO(combo13, AT_TB),         // L + O = Alt+Tab
  COMBO(combo14, SF_F10),       // Shift + 9 = Shift + F10 
};

// =>                              ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ OS Detection ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
bool OsAlreadyDetected = false;
bool process_detected_host_os_kb(os_variant_t detected_os) {
  if (!process_detected_host_os_user(detected_os))
    return false;
  
  if (OsAlreadyDetected)
    return false;

  switch (detected_os) {
    case OS_MACOS:
    case OS_IOS:
      layerSwitcher_setBaseLayers(_MAC_OS, _WINDOWS);
      break;
    default: // OS_WINDOWS OS_IOS OS_LINUX OS_UNSURE
      layerSwitcher_setBaseLayers(_WINDOWS, _GAMING);
  }
  OsAlreadyDetected = true;
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HRW_F:
    case HRW_J:
      return QUICK_TAP_TERM;
    default:
      return TAPPING_TERM;
  }
}

// =>                            ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Process Record ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
uint16_t ck_ent3_timer = 0;
uint16_t ck_del3_timer = 0;
uint16_t rsft_timer = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_RSFT: // Double-tap: Toggle Mouse Layer (Symbol)
      if (record->event.pressed) {
        if (timer_elapsed(rsft_timer) < TAPPING_TERM) {
          if (joystickMouse == true){
            layer_off(_SYMBOL);
            joystickMouse = false;
          }else{
            layer_on(_SYMBOL);
            joystickMouse = true;
          }
          rsft_timer = 0;
          return false;
        }
        rsft_timer = timer_read();
      }
      break;
    case CK_LYER: // Tap: Toggle Layer | Hold: Switch Layer
      layerSwitcher_keyHandler(record->event.pressed);
      break;
    case CK_ENT3: // Tap: Enter | Hold: Symbol Layer/Mouse Pointer
      if (record->event.pressed){
        ck_ent3_timer = timer_read();
        joystickMouse = true;
        layer_on(_SYMBOL);
      } else {
        joystickMouse = false;
        layer_off(_SYMBOL);
        if (timer_elapsed(ck_ent3_timer) < TAPPING_TERM) {
          tap_code(KC_ENT);
        }
      }
      return false;
    case CK_DEL3: // Tap: Delete | Hold: Symbol Layer/Mouse Pointer
      if (record->event.pressed){
        ck_del3_timer = timer_read();
        joystickMouse = true;
        layer_on(_SYMBOL);
      } else {
        joystickMouse = false;
        layer_off(_SYMBOL);
        if (timer_elapsed(ck_del3_timer) < QUICK_TAP_TERM) {
          tap_code(KC_DEL);
      }
    case CK_LNST: // Go to Line Start
      if (record->event.pressed) {
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(G(KC_LEFT)); // Mac OS
        } else {
          tap_code(KC_HOME); // Windows
        }
        return false;
      }
      break;
    case CK_LNED: // Go to Line End
      if (record->event.pressed) {
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(G(KC_RGHT)); // Mac OS
        } else {
          tap_code(KC_END); // Windows
        }
        return false;
      }
      break;
    case CK_WCS: // Wizard Cropped Snippet (Screenshot)
      if (record->event.pressed) {
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(C(G(S(KC_4)))); // Mac OS
        } else {
          tap_code16(KC_PSCR); // Windows
        }
        return false;
      }
      break;
    case CK_SCS: // Clipboard Cropped Snippet (Screenshot)
      if (record->event.pressed) {
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(G(S(KC_4))); // Mac OS
        } else {
          tap_code16(KC_PSCR); // Windows
        }
        return false;
      }
      break;
    }
    
    return false;
  }

  return true;
}
