#include QMK_KEYBOARD_H
#include "./lib/layers/layers.h"
#include "./lib/layers/layer_switcher.h"
#include "./lib/display/oled.h"
// #include "./lib/display/print_info.h"
// #include "./lib/eeprom/eeprom.h"
// #include "./lib/joystick/joystick.h"
// #include "./lib/espeng/esp_key.h"
#include "./lib/mouse/pointer.h"
#include "./lib/sync/oled_status.h"
#include "./lib/audio/songs.h"
#include "./lib/rgb/under_glow.h"
// #include "./lib/pomodoro/pomodoro.h"

// =>                           ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Custom Keycodes ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
enum my_keycodes {
  CK_SCS = SAFE_RANGE, // Simple cropped snippet
  CK_WCS,              // Wizard cropped snippet
  CK_LNST,             // Go to line start
  CK_LNED,             // Go to line end
  CK_JOYM,             // Cycle Joystick Mode
  CK_ATAB,             // Alt + Tab
  CK_ATIL,             // Alt + Tilde
  CK_CTAB,             // Control + Tab
  CK_ESP,              // Spanish Character Leader Key (Single Shot)
  CK_CPIU,             // Raise the Mouse CPI
  CK_CPID,             // Lower the Mouse CPI
  CK_PARE,             // Fast Parenthesis
  CK_SBRK,             // Fast Square Brackets
  CK_CBRK,             // Fast Curly Brackets
  CK_LNUP,             // Move a dozen lines up
  CK_LNDN,             // Move a dozen lines down
  CK_LYER,             // Base Layer toggle/switcher key
  CK_COPY,             // Copy (for Combo)
  PLAY_Z1,             // Play Zelda Song 1
  PLAY_Z2,             // Play Zelda Song 2
  // CK_POMO,             // Pomodoro Key
  CK_RJOY,             // Reset Joystick Middle
  CK_USCR,             // Go to the Beginning of File
  CK_DSCR              // Go to the EOF
};


// =>                          ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Wrapped Keycodes ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
#define HY_ESC  ALL_T(KC_ESC)        // onHold: Hyper | onTap: ESC
#define HRW_A   LGUI_T(KC_A)         // Win Homerow A/Win
#define HRW_S   LALT_T(KC_S)         // Win Homerow S/Alt
#define HRW_D   LCTL_T(KC_D)         // Win Homerow D/Ctrl
#define HRW_F   LSFT_T(KC_F)         // Win Homerow F/Shift
#define HRW_J   LSFT_T(KC_J)         // Win Homerow J/Shift
#define HRW_K   LCTL_T(KC_K)         // Win Homerow K/Ctrl
#define HRW_L   LALT_T(KC_L)         // Win Homerow L/Alt
#define HRW_QT  LGUI_T(KC_QUOT)      // Win Homerow Quot/Win
#define HRM_A   LCTL_T(KC_A)         // Mac Homerow A/Ctrl
#define HRM_D   LGUI_T(KC_D)         // Mac Homerow D/Cmd
#define HRM_K   LGUI_T(KC_K)         // Mac Homerow K/Cmd
#define HRM_QT  LCTL_T(KC_QUOT)      // Mac Homerow Quot/Ctrl
#define RS_ENT  RSFT_T(KC_ENT)       // onHold: Shift         | onTap: Enter 
#define L_SYMB  LT(_SYMBOL,KC_DEL)   // onHold: SymbolsLayer  | onTap: Delete
#define L_FUNC  LT(_FUNCTION,MS_BTN2)// onHold: FunctionLayer | onTap: Mouse Btn 3
#define NP_SPC  LT(_NUMPAD,KC_SPC)   // onHold: NumpadLayer   | onTap: Space
#define L_CONF  MO(_CONFIG)          // onHold: ConfigLayer

// =>                      ≈ ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓  Keymap Layouts  ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ ≈ =╗
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//                                        ▒▒ ▒▒ ▒▒ ▒▒          ▒▒ ▒▒ ▒▒ ▒▒
//                                  ▒▒ ▒▒ ▓▓ ▓▓ ▓▓ ▓▓          ▓▓ ▓▓ ▓▓ ▓▓ ▒▒ ▒▒
//                                  ▓▓ ▓▓ ▒▒ ▒▒ ▒▒ ▒▒          ▒▒ ▒▒ ▒▒ ▒▒ ▓▓ ▓▓
//                                  ▒▒ ▒▒  ░ ░                        ░ ░  ▒▒ ▒▒
//                                  ░░ ░░ ░░      ░░            ░░      ░░ ░░ ░░
//                                    ▒-▒-▒-▒  ▒▒ ▒▒            ▒▒ ▒▒  ▒-▒-▒-▒

[_WINDOWS] = LAYOUT(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  HY_ESC,  HRW_A,   HRW_S,   HRW_D,   HRW_F,   KC_G,          KC_H,    HRW_J,   HRW_K,   HRW_L,   HRW_QT,  KC_BSPC,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RS_ENT,
  KC_LCTL, KC_LGUI, KC_LALT, MS_BTN2, MS_BTN1, NP_SPC,        NP_SPC,  MS_BTN1, MS_BTN2, CK_LYER, XXXXXXX, L_CONF,
  CK_ATIL, CK_ATAB, XXXXXXX, CK_CTAB, L_FUNC,  L_SYMB,        L_SYMB,  L_FUNC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_UP
),
[_MAC_OS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, KC_A,    _______, HRM_D,   _______, _______,       _______, _______, HRM_K,   _______, KC_QUOT, _______,
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______
),
[_GAMING] = LAYOUT(
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, KC_A,    KC_S,    KC_D,    KC_F,    _______,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,  KC_SPC,       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,  NP_SPC,       _______, _______, _______, _______, _______, _______
),
[_SYMBOL] = LAYOUT(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
  KC_ESC,  KC_PIPE, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_WCS,        CK_SCS,  XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  CK_USCR, XXXXXXX, CK_DSCR, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, _______, CK_LNDN, _______, CK_LNUP
),
[_NUMPAD] = LAYOUT(
  KC_MINS, XXXXXXX, KC_9,    KC_8,    KC_7,    KC_NUM,        KC_NUM,  KC_7,    KC_8,    KC_9,    XXXXXXX, KC_MINS,
  KC_ESC,  KC_PDOT, KC_6,    KC_5,    KC_4,    XXXXXXX,       XXXXXXX, KC_4,    KC_5,    KC_6,    KC_PDOT, _______,
  _______, KC_PDOT, KC_3,    KC_2,    KC_1,    KC_0,          KC_0,    KC_1,    KC_2,    KC_3,    KC_PDOT, XXXXXXX,
  _______, _______, _______, XXXXXXX, XXXXXXX, KC_0,          KC_0,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_PPLS, KC_PSLS, KC_PMNS, KC_PAST, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, KC_PAST, KC_PMNS, KC_PSLS, KC_PPLS
),
[_FUNCTION] = LAYOUT(
  XXXXXXX, KC_F12,  KC_F11,  KC_F10,  KC_F9,   XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_ESC,  KC_F8,   KC_F7,   KC_F6,   KC_F5,   XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, _______, _______, _______, _______
),
[_CONFIG] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PLAY_Z1,       CK_JOYM, CK_CPIU, CK_CPID, XXXXXXX, XXXXXXX, XXXXXXX,
  EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PLAY_Z2,       HF_TOGG, HF_FDBK, HF_RST,  HF_NEXT, HF_PREV, HF_RST,
  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)
};

// =>            ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Combos (Quick Key Combination) ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
const uint16_t PROGMEM cb00[] = {HRW_F,   HRW_D,   COMBO_END};  // D + F
const uint16_t PROGMEM cb01[] = {HRW_J,   HRW_K,   COMBO_END};  // J + K
const uint16_t PROGMEM cb02[] = {KC_COMM, KC_DOT,  COMBO_END};  // Comma + Dot
const uint16_t PROGMEM cb03[] = {KC_E,    KC_I,    COMBO_END};  // E + I
const uint16_t PROGMEM cb04[] = {HRW_D,   HRW_K,   COMBO_END};  // D + K
const uint16_t PROGMEM cb05[] = {KC_C,    KC_COMM, COMBO_END};  // C + Comma
const uint16_t PROGMEM cb06[] = {KC_Z,    KC_X,    COMBO_END};  // Z + X
const uint16_t PROGMEM cb07[] = {KC_DOT,  KC_SLSH, COMBO_END};  // Dot + Slash
const uint16_t PROGMEM cb08[] = {HRW_D,   KC_C,    COMBO_END};  // D + C
const uint16_t PROGMEM cb09[] = {HRW_F,   HRW_J,   COMBO_END};  // F + J
// const uint16_t PROGMEM cb10[] = {KC_E,    KC_R,    COMBO_END};  // E + R
// const uint16_t PROGMEM cb11[] = {KC_U,    KC_I,    COMBO_END};  // U + I
// const uint16_t PROGMEM cb12[] = {KC_E,    KC_W,    COMBO_END};  // E + W
// const uint16_t PROGMEM cb13[] = {KC_C,    KC_X,    COMBO_END};  // C + X

combo_t key_combos[] = {
  COMBO(cb00, KC_ENT),   // D + F = Enter (on Tap)
  COMBO(cb01, KC_ENT),   // J + K = Enter (on Tap)
  COMBO(cb02, KC_SCLN),  // Comma + Dot = Semicolon
  COMBO(cb03, CK_PARE),  // () Parenthesis
  COMBO(cb04, CK_SBRK),  // [] Square Brackets
  COMBO(cb05, CK_CBRK),  // {} Curly Brackets
  COMBO(cb06, CK_LNST),  // 'Z' + 'X' = Home
  COMBO(cb07, CK_LNED),  // '.' + '/' = End
  COMBO(cb08, CK_COPY),  // D + C = Copy
  COMBO(cb09, CW_TOGG),  // Toggle Caps Word
  // COMBO(cb10, KC_DEL),   // Delete
  // COMBO(cb11, KC_DEL),   // Delete
  // COMBO(cb12, CK_USCR),  // Go to the Beginning of File
  // COMBO(cb13, CK_DSCR),  // Go to the End of File
};

// Identify and return true if that combo should be triggered only on tap
bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
  if (combo_index < 2) // Index 0 and 1 Tap to Enter, Hold to Homerow Mods
    return true;
  return false;
}

// =>                          ≈ ≈ ≈ ≈ ≈ ░░░▒▒▒▓▓▓ Process Keycodes ▓▓▓▒▒▒░░░ ≈ ≈ ≈ ≈ =╗
uint8_t mod_state; // Easy access to current active mods
// bool is_ctrl_alt_arrow_active = false;
// bool is_line_start_end_active = false;
bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;
bool is_alt_tilde_active = false;
bool have_config_changes = false; // Tracks changes to save EEPROM writes

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  oled_wakeUpScreen();

  switch (keycode) {
    case CK_USCR: // Go to the Beggining of the File
      if (record->event.pressed){
        if (LS_isBaseLayer(_MAC_OS)){
          tap_code16(G(KC_UP)); // Mac OS
        } else {
          tap_code16(C(KC_HOME)); // Windows
        }
        return false;
      }
    break;
    case CK_DSCR: // Go to EOF
      if (record->event.pressed){
        if (LS_isBaseLayer(_MAC_OS)){
          tap_code16(G(KC_DOWN)); // Mac OS
        } else {
          tap_code16(C(KC_END)); // Windows
        }
        return false;
      }
    break;
    // case CK_RJOY: // Re-center Joystick
    //   if (record->event.pressed){
    //     //joystick_ResetMidValues();
    //   }
    // break;
    // case LT(_NUMPAD,KC_SPC): // Alternative Scrolling on Hold
    // if (record->event.pressed){
    //     //mouse_isScrolling = true; // Enable trackball scrolling
    //     //joystick_isHorizScroll = true; // Enable Joystick Horizontal Scrolling
    //   }
    //   else {
    //     //mouse_isScrolling = false; // Disable trackball scrolling
    //     //joystick_isHorizScroll = false; // Disable Joystick Horizontal Scrolling
    //   }
    //   break;
    // case CK_POMO: // Pomodoro Timer Key Events Handler
    //   return pomodoro_processKeyEvent(record->event.pressed);
    //   break;
    case PLAY_Z1: // Play zelda song 1
      if (record->event.pressed) {
        audio_playZeldaChest();
      }
      break;
    case PLAY_Z2: // Play zelda song 2
      if (record->event.pressed) {
        audio_playZeldaSecret();
      }
      break;
    case CK_LNUP: // Quickly move 12 lines up
      if (record->event.pressed) {
        for (int i = 0; i < 12; i++) {
          tap_code_delay(KC_UP, 10);
        }
        return false;
      }
      break;
    case CK_LNDN: // Quickly move 12 lines down
      if (record->event.pressed) {
        for (int i = 0; i < 12; i++) {
          tap_code_delay(KC_DOWN, 10);
        }
        return false;
      }
      break;
    case CK_PARE: // Quick Parenthesis
      if (record->event.pressed) {
        tap_code16(KC_LPRN);
        tap_code16(KC_RPRN);
        tap_code16(KC_LEFT);
        return false;
      }
      break;
    case CK_SBRK: // Quick Square Bracket
      if (record->event.pressed) {
        tap_code16(KC_LBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_LEFT);
        return false;
      }
      break;
    case CK_CBRK: // Quick Curly Brackets
      if (record->event.pressed) {
        tap_code16(KC_LCBR);
        tap_code16(KC_RCBR);
        tap_code16(KC_LEFT);
        return false;
      }
      break;
    case CK_CPIU: // Increase the Mouse's CPI
      if (record->event.pressed) {
        mouse_increaseCpi(); // oled_CpiValue updates oled
        have_config_changes = true;
        return false;
      }
      break;
    case CK_CPID: // Decrease the Mouse's CPI
      if (record->event.pressed) {
        mouse_decreaseCpi(); // oled_CpiValue updates oled
        have_config_changes = true;
        return false;
      }
      break;
    case L_CONF: // Save CONFIG to EEPROM
      if (record->event.pressed) {
        pointing_device_get_cpi();
      } else {
        if (have_config_changes) { // Only writes to EEPROM on changes
        //  eeprom_saveCpi(pointing_device_get_cpi());
          have_config_changes = false; 
        }
      }
      break;
    // case LGUI_T(KC_A):  // ESP / ENG character
    // case KC_E:          // handling. Check these
    // case KC_I:          // keys for possible
    // case KC_O:          // spanish character
    // case KC_U:          // insertion like
    // case KC_N:          // ñ á é í ó ú
    //   if (record->event.pressed) {
    //     if (LS_baseLayer() != _MAC_OS) { // Windows only
    //       //return espKey_handlePossibleEspChar(keycode);
    //     }
    //   }
    //   break;
    // case CK_ESP: // Toggle ESP/ENG Lang Layout (Windows only)
    //   if (record->event.pressed){
    //     if (LS_baseLayer() != _MAC_OS) {
    //       //return espKey_toggle();
    //     }
    //   }
    //   break;
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
    case CK_SCS: // Simple Cropped Snippet (Screenshot)
      if (record->event.pressed) {
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(G(S(KC_4))); // Mac OS
        } else {
          tap_code16(KC_PSCR); // Windows
        }
        return false;
      }
      break;
    case CK_ATAB: // Alt + Tab (Inter App Navigation)
      if (record->event.pressed
          && !is_alt_tab_active
          && !is_alt_tilde_active
          && !is_ctrl_tab_active) {
        is_alt_tab_active = true;
        if (LS_isBaseLayer(_MAC_OS)) {
          register_code(KC_LGUI); // Mac OS
          tap_code16(KC_TAB);
        } else {
          register_code(KC_LALT); // Windows
          tap_code16(KC_TAB);
        }
        return false;
      } else {
        is_alt_tab_active = false;
        if (LS_isBaseLayer(_MAC_OS)) {
          unregister_code(KC_LGUI);
        } else {
          unregister_code(KC_LALT);
        }
        return false;
      }
      break;
    case CK_ATIL: // Alt + Tilde (Same App Navigation)
      if (record->event.pressed
          && !is_alt_tab_active
          && !is_alt_tilde_active
          && !is_ctrl_tab_active) {
        is_alt_tilde_active = true;
        if (LS_isBaseLayer(_MAC_OS)) {
          register_code(KC_LGUI); // Mac OS
          tap_code16(KC_GRV);
        } else {
          register_code(KC_LALT); // Windows
          tap_code16(KC_GRV);
        }
        return false;
      } else {
        is_alt_tilde_active = false;
        if (LS_isBaseLayer(_MAC_OS)) {
          unregister_code(KC_LGUI);
        } else {
          unregister_code(KC_LALT);
        }
        return false;
      }
      break;
    case CK_CTAB: // Control + Tab (tab movement)
      if (record->event.pressed
          && !is_alt_tab_active
          && !is_alt_tilde_active
          && !is_ctrl_tab_active) {
        is_ctrl_tab_active = true;
        register_code(KC_LCTL); // Both Mac OS & Windows
        tap_code16(KC_TAB);
        return false;
      } else {
        is_ctrl_tab_active = false;
        unregister_code(KC_LCTL);
        return false;
      }
      break;
    case CK_JOYM: // Cycle through Joystick Mode (round robin)
      if (record->event.pressed) {
        //joystick_CycleMode();
        return false;      
      }
      break;
    case CK_LYER: // Tap: Toggle Layer | Hold: Switch Layer
      layerSwitcher_keyHandler(record->event.pressed);
      break;
    case CK_COPY: // Copy
      if (record->event.pressed){
        if (LS_isBaseLayer(_MAC_OS)) {
          tap_code16(G(KC_C)); // Copy in Mac OS
        } else {
          tap_code16(C(KC_C)); // Copy in Windows
        }
      }
    break;
  }

  return true;
}