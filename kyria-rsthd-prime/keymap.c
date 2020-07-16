/* Copyright 2020 @frogm0uth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap.h"

user_config_t user_config;

// Initialize based on EEPROM user data 
void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set OS
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
  os_set_raw(user_config.os_selection);
#endif
  
    // DEBUG - Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

// #defines for shorter codes for keymap
#define CU_DTUN CU_DOT_UNDERSCORE
#define CU_CMMI CU_COMMA_MINUS

#define CU_HBCK CU_HYPER_BACK
#define CU_HFWD CU_HYPER_FORWARD

#ifdef COMPOSE_KEY
  #define CU_DEAD CU_COMPOSE  // Compose key
#elif defined(LEADER_ENABLE)
  #define CU_DEAD KC_LEAD     // Leader key
#else
  #define CU_DEAD KC_NO       // Nothing
#endif

/**
 ** Keymap
 **/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * Layer 0: RSTHD

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |   J  |   C  |   Y  |   F  |   K  |                              |   Z  |   L  | '  " |   U  |   Q  |Leader|
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |   R  |   S  |   T  |   H  |   D  |                              |   M  |   N  |   A  |   I  |   O  |      |
  | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |   V  |   G  |   P  |   B  |      |      |  |      |      |   X  |   W  | .  _ | ,  - |      |      |
  |  Cmd | Shift|      |      |      |      |   E  |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      | EDIT |  |CURSOR|      |      |      |(EncR)|
                       |      |  Alt |NUMPAD|      |      |  |      |      |SYNTAX|  Alt |      |
                       `----------------------------------'  `----------------------------------'
 */
    [RSTHD] = LAYOUT(
      KC_ESC,  KC_J,    KC_C,   KC_Y,   KC_F,   KC_K,                                           KC_Z,    KC_L,    KC_QUOT, KC_U,    KC_Q,   CU_DEAD,
      KC_LCTL, KC_R,    KC_S,   KC_T,   KC_H,   KC_D,                                           KC_M,    KC_N,    KC_A,    KC_I,    KC_O,   KC_RCTL,
      KC_LGUI, CU_LSFT, KC_V,   KC_G,   KC_P,   KC_B, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_X,    KC_W,    CU_DTUN, CU_CMMI, CU_RSFT, KC_RGUI,
                           CU_SLOCK, KC_LALT, CU_NUMPAD, KC_E, CU_EDIT, /* */ CU_CURSOR, KC_SPACE, CU_SYNTAX, KC_RALT, CU_SLEEP
    ),
    
/* 
 * Layer 1: PRIME

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |   J  |   C  |   W  |   D  |   Y  |                              |   Z  |   L  |   U  | '  " |   Q  |Leader|
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |   R  |   S  |   T  |   H  |   P  |                              |   V  |   N  |   I  |   O  |   A  |      |
  | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |   B  |   G  |   F  |   K  |      |      |  |      |      |   X  |   M  | ,  - | .  _ |      |      |
  |  Cmd | Shift|      |      |      |      |   E  |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      | EDIT |  |CURSOR|      |      |      |(EncR)|
                       |      |  Alt |NUMPAD|      |      |  |      |      |SYNTAX|  Alt |      |
                       `----------------------------------'  `----------------------------------'
 */
    [PRIME] = LAYOUT(
      KC_ESC,  KC_J,   KC_C,   KC_W,   KC_D,   KC_Y,                                             KC_Z,    KC_L,    KC_U,    KC_QUOT, KC_Q,   CU_DEAD,
      KC_LCTL, KC_R,   KC_S,   KC_T,   KC_H,   KC_P,                                             KC_V,    KC_N,    KC_I,    KC_O,    KC_A,   KC_RCTL,
      KC_LGUI, CU_LSFT,KC_B,   KC_G,   KC_F,   KC_K, XXXXXXX, XXXXXXX, /* */ KC_COMM,   XXXXXXX, KC_X,    KC_M,    CU_CMMI, CU_DTUN, CU_RSFT, KC_RGUI,
                         CU_SLOCK, KC_LALT, CU_NUMPAD, KC_E,  CU_EDIT, /* */ CU_CURSOR, KC_SPACE, CU_SYNTAX, KC_RALT, CU_SLEEP
    ),

/*
 * Layer 2: NUMPAD (R)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc | FUNC |  ../ |   =  |      | AppP |                              | AppN | 4  $ | 5  % | 6  ^ |      | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |   /  |   *  |   .  |   0  |  Up  |                              |AppWin| 1  ! | 2  @ | 3  # | `  ~ |
  | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |  Tab |   -  |   +  | Left |      |      |  |      |      | Right| 7  & | 8  * | 9  ( |      |      |
  |  Cmd | Shift|      |      |      |      |      |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      | EDIT |  |CURSOR|      |      |      |(EncR)|
                       |      |  Alt | (**) |      |      |  |      |      |SYNTAX|  Alt |      |
                       `----------------------------------'  `----------------------------------'
 */
    [NUMPAD] = LAYOUT(
      _______, CU_FUNC, CU_DIRU, KC_EQL,  XXXXXXX, CU_APPP,                                           CU_APPN,  KC_4, KC_5, KC_6, XXXXXXX, CU_BASE,
      _______, KC_SLSH, KC_ASTR, KC_DOT,  KC_0,    KC_UP,                                             CU_WAPP,  KC_1, KC_2, KC_3, KC_GRV,  _______,
      _______, _______, KC_TAB,  KC_MINS, KC_PLUS,  KC_LEFT, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_RIGHT, KC_7, KC_8, KC_9, _______, _______,
                                CU_SCRZ0, _______, _______, XXXXXXX, _______, /* */ _______, _______, _______,  _______,  CU_APPZ0
    ),

/*
 * Layer 3: SYNTAX (L)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |      |   [  |   |  |   ]  |      |                              |      |      |   #  |      |ADJUST| BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |   /  |   {  |   ;  |   }  |      |                              |      |   )  |   :  |   (  |   \  |      |
  | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |   <  |   ?  |   >  |      |      |      |  |      |      |      |      |   !  |  Tab |      |      |
  |  Cmd | Shift|      |      |      |      | Enter|  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
  `--------------------+------+------+------|      |      |  |      |      |------+------+---------------------------'
                       |(EncL)|      | Space|      | EDIT |  |CURSOR|      |      |      |(EncR)|
                       |      |  Alt |      |      |      |  |      |      | (**) |  Alt |      |
                       `----------------------------------'  `----------------------------------'
 */
    [SYNTAX] = LAYOUT(
      _______, XXXXXXX, KC_LBRC, KC_PIPE, KC_RBRC, KC_NO,                                            KC_NO, XXXXXXX, KC_HASH, XXXXXXX, CU_ADJUST, CU_BASE,
      _______, KC_SLSH, KC_LCBR, KC_SCLN, KC_RCBR, KC_NO,                                            KC_NO, KC_RPRN, KC_COLN, KC_LPRN, KC_BSLS, _______,
      _______, _______, KC_LABK, KC_QUES, KC_RABK, KC_NO,  XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_NO, XXXXXXX, KC_EXLM, KC_TAB, _______, _______,
                              XXXXXXX, _______, KC_SPACE, KC_ENTER, _______, /* */ _______, _______, _______, _______, XXXXXXX
    ),

/*
 * Layer 4: EDIT (R)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |  All |  Cut | Copy | Paste| WinL |                              | WinR | WordL|  Up  | WordR|      | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |      |      |      |      | AppL |                              | AppR | Left | Down | Right| PgUp |      |
  |      |DelMod| Acc1 | Acc2 |Repeat|      |                              |      |      |      |      |      |      |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |      |      |      | TabL |      |      |  |      |      | TabR | HBck | Down | HFwd | PgDn |      |
  |      | Shift| Ctrl |  Alt |  Cmd |      |      |      |  | Enter| BkSp |      |      |      |      |      |      |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      | (**) |  |      |      |  Del |      |(EncR)|
                       |      |      |      |      |      |  |      |      |      |  Alt |      |
                       `----------------------------------'  `----------------------------------'
 */
  [EDIT] = LAYOUT(
      _______, CU_ALL,  CU_CUT,  CU_COPY, CU_PAST, CU_WINL,                                           CU_WINR, CE_WD_L, CE_MV_U, CE_WD_R, XXXXXXX, CU_BASE,
      XXXXXXX, CE_DMOD, CE_ACC1, CE_ACC2, CE_REPT, CU_APPL,                                           CU_APPR, CE_MV_L, CE_MV_D, CE_MV_R, CE_PG_U, XXXXXXX,
      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CU_TABL, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_TABR, CU_HBCK, CE_MV_D, CU_HFWD, CE_PG_D, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /* */ KC_ENTER, KC_BSPC, KC_DEL, _______, XXXXXXX
    ),

/*
 * Layer 5: CURSOR (L)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |      |      | MS_U |      | ScrL |                              | ScrR | Paste| Copy |  Cut |  All | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |      | MS_L | MS_D | MS_R |Expose|                              |FulScr|      |      |      |      |      |
  |      | Wheel|      |      |      |      |                              |      |Repeat| Acc2 | Acc1 | Slow |      |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      | HBck | MS_D | HFwd | SSRgn|      |      |  |      |      |DskTop|      |      |      |      |      | 
  |      |      |      |      |      |      | Btn_L| Btn_R|  |      |      |      |  Cmd |  Alt | Ctrl | Shift|      |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      | Btn_M|      |      |  | (**) |      | SSWin| SSScr|(EncR)|
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
*/
#ifndef CURSOR_RIGHTHANDED
    [CURSOR] = LAYOUT(
      _______, XXXXXXX, XXXXXXX, CM_MS_U, XXXXXXX, CU_SCRL,                                             CU_SCRR,  CU_PAST, CU_COPY, CU_CUT,  CU_ALL,  CU_BASE,
      XXXXXXX, CM_WHEE, CM_MS_L, CM_MS_D, CM_MS_R, CU_WALL,                                             CU_FSCR,  CM_REPT, CM_ACC2, CM_ACC1, CM_SLOW, XXXXXXX,
      XXXXXXX, XXXXXXX, CU_HBCK, CM_MS_D, CU_HFWD, CU_SSRGN, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX,  CU_DTOP,  KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, XXXXXXX,
                                 CM_BTN1, XXXXXXX, CM_BTN3,  CM_BTN1, CM_BTN2, /* */ _______, XXXXXXX,  CU_SSWIN, CU_SSSCR, XXXXXXX
    ),
#endif
/*
 * Layer 5: CURSOR ALT (L) "Right-handed version"

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |  All |  Cut | Copy | Paste| ScrL |                              | ScrR |      | MS_U |      |      | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |      |      |      |      |Expose|                              |FulScr| MS_L | MS_D | MS_R |      |      |
  |      | Slow | Acc1 | Acc2 |Repeat|      |                              |      |      |      |      | Wheel|      |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |      |      |      | SSRgn|      |      |  |      |      |DskTop| HBck | MS_D | HFwd |      |      |
  |      | Shift| Ctrl |  Alt |  Cmd |      | Btn_L| Btn_R|  |      |      |      |      |      |      |      |      |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      | Btn_M|      |      |  | (**) |      | SSWin| SSScr|(EncR)|
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
*/
#ifdef CURSOR_RIGHTHANDED
    [CURSOR] = LAYOUT(
      _______, CU_ALL,  CU_CUT,  CU_COPY, CU_PAST, CU_SCRL,                                            CU_SCRR,  XXXXXXX, CM_MS_U, XXXXXXX, XXXXXXX, CU_BASE,
      XXXXXXX, CM_SLOW, CM_ACC1, CM_ACC2, CM_REPT, CU_WALL,                                            CU_FSCR,  CM_MS_L, CM_MS_D, CM_MS_R, CM_WHEE, XXXXXXX,
      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CU_SSRGN, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_DTOP,  CU_HBCK, CM_MS_D, CU_HFWD, XXXXXXX, XXXXXXX,
                                 CM_BTN1, XXXXXXX, CM_BTN3,  CM_BTN1, CM_BTN2, /* */ _______, XXXXXXX, CU_SSWIN, CU_SSSCR, XXXXXXX
    ),
#endif
/*
 * Layer 6: FUNC (R)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc | (**) |      |      |      |      |                              |      |  F4  |  F5  |  F6  |      | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |      |      |      |      |      |                              |      |  F1  |  F2  |  F3  |      |      |
  |      | Shift| Ctrl |  Alt |  Cmd |      |                              |      |      |      |      |      |      |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |      |      |      |      |      |      |  |      |      |      |  F7  |  F8  |  F9  |      |      |
  |      |      |      |      |      |      |      |      |  |      |  F10 |      |      |      |      |      |      |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      |      |  |      |      | F11  |  F12 |(EncR)|
                       |      |      | (**) |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
 */
    [FUNC] = LAYOUT(
      _______, CU_FUNC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           XXXXXXX, KC_F4, KC_F5, KC_F6, XXXXXXX, CU_BASE,
      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                                           XXXXXXX, KC_F1, KC_F2, KC_F3, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, XXXXXXX, KC_F7, KC_F8, KC_F9, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, CU_FUNC, XXXXXXX, XXXXXXX, /* */ XXXXXXX, KC_F10, KC_F11, KC_F12, XXXXXXX
    ),
    
/*
 * Layer 7: ADJUST (L)

  ,-----------------------------------------.                              ,-----------------------------------------.
  |  Esc |      |      | Mute |      |      |                              |      | !WIN | !MAC |      | (**) | BASE |
  |------+------+------+------+------+------|                              |------+------+------+------+------+------|
  |      |      |      | VolUp| BrtUp|      |                              |      |!RSTHD|!PRIME|      |      |      |
  | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
  |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
  |      |      |      | VolDn| BrtDn|      |      |      |  |      |      |      |      |      |      |      |      |
  |  Cmd | Shift|      |      |      |      |      |      |  | !WIPE|      |      |      |      |      | Shift|  Cmd |
  `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                       |(EncL)|      |      |      |      |  |      |      |      |      |(EncR)|
                       |      |      |      |      |      |  |      |      | (**) |      |      |
                       `----------------------------------'  `----------------------------------'
 */
    [ADJUST] = LAYOUT(
      _______, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,                                           XXXXXXX, CU_WIN,   CU_MAC,   XXXXXXX, CU_ADJUST, CU_BASE,
      _______, XXXXXXX, XXXXXXX, KC_VOLU, KC_BRIU, XXXXXXX,                                           XXXXXXX, CU_RSTHD, CU_PRIME, XXXXXXX, XXXXXXX, _______,
      _______, _______, XXXXXXX, KC_VOLD, KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, _______, _______,
                                 KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* */ CU_WIPE, XXXXXXX, CU_ADJUST, XXXXXXX,  CU_SAVE
    ),
};



/**
 ** App switcher. Alt-Tab in Windows, Cmd-Tab on macOS.
 **/
#ifndef APP_SWITCHER_TERM
#define APP_SWITCHER_TERM 1000
#endif

static bool app_switcher_active = false;
static uint16_t app_switcher_timer = 0;


void app_switcher_tick (void) { // Call from matrix_scan_user()
  if (app_switcher_active) {
    if (timer_elapsed(app_switcher_timer) > APP_SWITCHER_TERM) {
      unregister_code(SC(SC_APPSWITCH_START));
      app_switcher_active = false;
    }
  }
}

// Record keypress. Call from process_record_user.
void app_switcher_record(uint16_t keycode, bool pressed) {
  if (pressed) {
    if (!app_switcher_active) {
      app_switcher_active = true;
      register_code(SC(SC_APPSWITCH_START));
    }
    app_switcher_timer = timer_read();
    register_code16(keycode==CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
  } else {
    unregister_code16(keycode==CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
  }
}



/**
 ** Custom shift key
 **/
void custom_shift(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
  uint8_t mods = get_mods();
  if (record->event.pressed){
    if (mods & MOD_MASK_SHIFT) { // shifted case
      if (mods & MOD_BIT(KC_LSHIFT)) {
	unregister_code16(KC_LSHIFT);
      } else {
	unregister_code16(KC_RSHIFT);
      }
      register_code16(shiftedkey);
      set_mods(mods);
    } else {
      register_code16(key);
    }
  } else {
    unregister_code16(key);
    unregister_code16(shiftedkey);
  }
}


/*
 * User-level handling of custom keycodes
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //int i, n; // loop counters
  uint8_t mods = get_mods();
  uint16_t tempcode = KC_NO;

  // First check to see if we intercept for a compose sequence
#ifdef COMPOSE_KEY
  if (compose_key_intercept(keycode, record)) {
    return false;
  }
#endif
  
  switch (keycode) {

    // Toggle compose mode on or off
#ifdef COMPOSE_KEY
  case CU_COMPOSE:
    process_record_compose(keycode, record);
    break;
#endif
    
    // Custom mouse
#ifdef CUSTOM_MOUSE
    CUSTOM_MOUSE_PROCESS_RECORD(keycode, record);
#endif

    // Custom editing
#ifdef CUSTOM_EDIT
    CUSTOM_EDIT_PROCESS_RECORD(keycode, record);
#endif

    /** 
     ** Layer switching using the layer-tap-toggle function
     **/
#ifdef LAYER_TAP_TOGGLE
  case CU_LLCK:
    return ltt_lock(record); // Lock the current (highest) layer
    break;
    
  case CU_BASE:
    return ltt_base();   // Clear all layers and go back to the default layer
    break;

  case CU_NUMPAD:
    return layer_tap_toggle(KC_NO, NUMPAD, record);    
    break;
    
  case CU_SYNTAX:
    return layer_tap_toggle(KC_NO, SYNTAX, record);
    break;
    
  case CU_CURSOR:
    return layer_tap_toggle(KC_ENTER, CURSOR, record);
    break;
    
  case CU_EDIT:
    return layer_tap_toggle(KC_TAB, EDIT, record);
    break;
    
  case CU_FUNC:
    return layer_tap_toggle(KC_NO, FUNC, record);
    break;
    
  case CU_ADJUST:
    return layer_tap_toggle(KC_NO, ADJUST, record);
    break;
#endif
    
    
    /** 
     ** Macro/convenience codes
     **/
  case CU_DIRU:  // directory up
    if (record->event.pressed) {
      tap_code(KC_DOT);
      tap_code(KC_DOT);
      tap_code(KC_SLSH);
    }
    break;
    
    /** 
     ** Custom keycodes for different code on shift
     **/

  case CU_LSFT:      // Both shift keys turn on caps lock
    if (record->event.pressed) {
      if (mods & MOD_BIT(KC_RSHIFT)) {
	register_code(KC_CAPS);
      } else {
	register_code16(KC_LSFT);
      }
    } else {
      if (mods & MOD_BIT(KC_RSHIFT)) {
	unregister_code(KC_CAPS);
      } else {
	unregister_code16(KC_LSFT);
      }
    }      
    break;
  case CU_RSFT:
    if (record->event.pressed) {
      if (mods & MOD_BIT(KC_LSHIFT)) {
	register_code(KC_CAPS);
      } else {
	register_code16(KC_RSFT);
      }
    } else {
      if (mods & MOD_BIT(KC_LSHIFT)) {
	unregister_code(KC_CAPS);
      } else {
	unregister_code16(KC_RSFT);
      }
    }
    break;
    
  case CU_DOT_UNDERSCORE:
    custom_shift(KC_DOT, KC_UNDERSCORE, record);
    break;

  case CU_COMMA_MINUS:
    custom_shift(KC_COMMA, KC_MINUS, record);
    break;

    
    // "Hyper" back and forward -
    //   Normal: undo and redo
    //   Cmd:    browser back and forward
    //   Alt:    next and previous search result
    // FIXME: error if modifier is released first?
    //
  case CU_HYPER_BACK:
  case CU_HYPER_FORWARD:
    if (mods & MOD_MASK_GUI){
      tempcode = keycode == CU_HYPER_BACK ? SC(SC_BROWSER_BACK) : SC(SC_BROWSER_FWD);
    } else if (mods & MOD_MASK_ALT){
      tempcode = keycode == CU_HYPER_BACK ? SC(SC_PREV_SEARCH) : SC(SC_NEXT_SEARCH);
    } else {
      tempcode = keycode == CU_HYPER_BACK ? SC(SC_UNDO_ACTION) : SC(SC_REDO_ACTION);
    }
    if (record->event.pressed){
      clear_mods();
      register_code16(tempcode);
      set_mods(mods);
    } else {
      unregister_code16(tempcode);
    }
    break;
    
    // Take screenshot of the window under the cursor
    // FIXME: needs to have a Windows version
  case CU_SSWIN:
    if (record->event.pressed){
      tap_code16(SC(SC_SHOT_REGION));
      tap_code(KC_SPC);
#ifdef CUSTOM_MOUSE
      _delay_ms(100);
      custom_mouse_button_press(CM_BTN1, true);
      _delay_ms(100);
      custom_mouse_button_press(CM_BTN1, false);
#endif
    }
    break;

    // Take screenshot of a region. This does the initial mouse press, so drag then press the mouse button.
    // FIXME: needs to have a Windows version
  case CU_SSRGN:
    if (record->event.pressed){
      tap_code16(SC(SC_SHOT_REGION));
#ifdef CUSTOM_MOUSE
      _delay_ms(100);
      custom_mouse_button_press(CM_BTN1, true);
#endif
    }
    break;

    /** 
     ** Custom keycodes for window operations
     **/

    // Switch between applications
  case CU_APPR:
  case CU_APPL:
    app_switcher_record(keycode, record->event.pressed);
    break;

    // Switch between tabs. With some apps, this doesn't work, so press Cmd/Gui as well and it might work then
  case CU_TABR:
  case CU_TABL:
    if (record->event.pressed) {
      if (mods & MOD_MASK_GUI) {
	register_code16(keycode == CU_TABR ? SC(SC_TAB_RIGHT_ALT) : SC(SC_TAB_LEFT_ALT));
	} else {
	register_code16(keycode == CU_TABR ? SC(SC_TAB_RIGHT) : SC(SC_TAB_LEFT));
      }
    } else {
      	unregister_code16(keycode == CU_TABR ? SC(SC_TAB_RIGHT_ALT) : SC(SC_TAB_LEFT_ALT));
	unregister_code16(keycode == CU_TABR ? SC(SC_TAB_RIGHT) : SC(SC_TAB_LEFT));
    }
    break;

    // Wipe the EEPROM. Handy if you get stuck when you have multiple default layers.....
    // After doing this, power-cycle the keyboard. There will be no visible indication...
  case CU_WIPE:
    eeconfig_init();
    break;

    // Save RGB state to EEPROM
#ifdef RGBLIGHT_ENABLE
  case CU_SAVE:
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
    break;
#endif

    // Switch the default layer
  case CU_RSTHD:
    set_single_persistent_default_layer(RSTHD);
    layer_clear();
    break;

  case CU_PRIME:
    set_single_persistent_default_layer(PRIME);
    layer_clear();
    break;
    
    // OS selection
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
  case CU_SELECT_MACOS:
  case CU_SELECT_WINDOWS:
    if (record->event.pressed) {
      os_set_from_keycode(keycode);
      user_config.os_selection = os_get_raw();
      eeconfig_update_user(user_config.raw);
    }
    break;
#endif

  }

  // Default processing for OS shortcuts
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
  process_record_shortcut(keycode, record);
#endif
  
  // All done OK, we hope
  return true;
}



void matrix_scan_user(void) {
  // Update ltt_timer
#ifdef LAYER_TAP_TOGGLE
  ltt_update_timer();
#endif
  
  // Mouse repeat
#ifdef CUSTOM_MOUSE
  custom_mouse_tick();
#endif
  
  // Editing repeat
#ifdef CUSTOM_EDIT
  custom_edit_tick();
#endif
  
  // Compose key status timer
#ifdef COMPOSE_STATUS_ENABLE
  compose_status_tick();
#endif
  
  // App-switcher timeout
  app_switcher_tick();

#ifdef LEADER_ENABLE
  // Process leader keys
  matrix_scan_leader();
#endif
}
