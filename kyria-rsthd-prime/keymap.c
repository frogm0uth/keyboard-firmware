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

/**
 * User space in EEPROM. Variable and function to read at initialization.
 */
user_config_t user_config;
void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    // Set OS
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    os_set_raw(user_config.os_selection);
#endif
}

/**
 *  #defines for shorter keycodes to put in keymap matrix
 */
#define CU_DTUN CU_DOT_UNDERSCORE
#define CU_CMMI CU_COMMA_MINUS
#define CU_EXQU CU_EXCLAIM_QUESTION
#define CU_SPEN CU_SPACE_ENTER

#define CU_HBCK CU_HYPER_BACK
#define CU_HFWD CU_HYPER_FORWARD

#define CU_AENT ALT_T(KC_ENTER)

#ifdef COMPOSE_KEY
#    define CU_DEAD CU_COMPOSE    // Compose key
#elif defined(LEADER_ENABLE)
#    define CU_DEAD KC_LEAD       // Leader key
#else
#    define CU_DEAD KC_NO         // Nothing
#endif

/**
 * Keymap
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
/* RSTHD

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   J  |   C  |   Y  |   F  |   K  |                              |   Z  |   L  | ,  - |   U  |   Q  |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   R  |   S  |   T  |   H  |   D  |                              |   M  |   N  |   A  |   I  |   O  |      |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |   V  |   G  |   P  |   B  |      |      |  |      | Enter|   X  |   W  | .  _ | ;  : |      |      |
 |  Cmd | Shift|      |      |      |      |   E  |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse| '  " |      |      |  |      |      | '  " |Compse|(EncR)|
 |                    |      |      | FUNC |      |SYNTAX|  |  Alt |      |CURSOR|      |      |
 |                    |      |      |NUMPAD|      |      |  |      |      | EDIT |      |      |
 |                    `----------------------------------'  `----------------------------------'
 |                                  +Cmd=Lock                             +Cmd=Lock
 |                                  +Alt=TAP                              
 |             	                    +Ctrl=FUNC                            +Ctrl=CURSOR
*/
    [RSTHD] = LAYOUT(
        KC_ESC,  KC_J,    KC_C,   KC_Y,    KC_F,    KC_K,                                              KC_Z,    KC_L,    CU_CMMI, KC_U,    KC_Q,    XXXXXXX,
        KC_LCTL, KC_R,    KC_S,   KC_T,    KC_H,    KC_D,                                              KC_M,    KC_N,    KC_A,    KC_I,    KC_O,    KC_RCTL,
        KC_LGUI, CU_LSFT, KC_V,   KC_G,    KC_P,    KC_B,    XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_X,    KC_W,    CU_DTUN, KC_SCLN, CU_RSFT, KC_RGUI,
        /* */                     CU_SLCK, CU_DEAD, CL_NUMP, KC_E,    CL_SYNT, /* */ CU_AENT, CU_SPEN, CL_EDIT, CU_DEAD, CU_SSLP
        ),

/* PRIME

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   V  |   C  |   W  |   D  |   K  |                              |   J  |   M  |   U  | .  _ |   Q  |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   R  |   S  |   T  |   H  |   P  |                              |   X  |   N  |   I  |   O  |   A  |      |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |   B  |   G  |   F  |   Z  |      |      |  |      | Enter| !  ? |   L  |   Y  | ,  - |      |      |
 |  Cmd | Shift|      |      |      |      |   E  |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse| '  " |      |      |  |      |      | '  " |Compse|(EncR)|
 |                    |      |      | FUNC |      |SYNTAX|  |  Alt |      |CURSOR|      |      |
 |                    |      |      |NUMPAD|      |      |  |      |      | EDIT |      |      |
 |                    `----------------------------------'  `----------------------------------'
 |                                  +Cmd=Lock                             +Cmd=Lock
 |                                  +Alt=TAP                              
 |             	                    +Ctrl=FUNC                            +Ctrl=CURSOR
*/
    [PRIME] = LAYOUT(
        KC_ESC,  KC_V,    KC_C,   KC_W,    KC_D,    KC_K,                                              KC_J,    KC_M,    KC_U,   CU_DTUN, KC_Q,    XXXXXXX,
        KC_LCTL, KC_R,    KC_S,   KC_T,    KC_H,    KC_P,                                              KC_X,    KC_N,    KC_I,   KC_O,    KC_A,    KC_RCTL,
        KC_LGUI, CU_LSFT, KC_B,   KC_G,    KC_F,    KC_Z,    XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_EXQU, KC_L,    KC_Y,   CU_CMMI, CU_RSFT, KC_RGUI,
        /* */                     CU_SLCK, CU_DEAD, CL_NUMP, KC_E,    CL_SYNT, /* */ CU_AENT, CU_SPEN, CL_EDIT, CU_DEAD, CU_SSLP
        ),

/* NUMPAD

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |  All |  Cut | Copy | Paste| ScrL |                              | ScrR | 4  $ | 5  % | 6  ^ |  ../ | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   *  |   -  |   .  |   0  |FulScr|                              |Expose| 1  ! | 2  @ | 3  # |   /  |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |   +  |  Tab |   =  |DskTop|      |      |  |      | Enter|DskTop| 7  & | 8  * | 9  ( |      |      |
 |  Cmd | Shift|      |      |      |      | AppR |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse|      |      |SYNTAX|  |      |      | '  " |Compse|(EncR)|
 |                    |      |      | (--) |      |      |  |  Alt |      |CURSOR|      |      |
 |                    |      |      | (**) |      |      |  |      |      | EDIT |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [NUMPAD] = LAYOUT(
        _______, CU_ALL,  CU_CUT,  CU_COPY, CU_PAST, CU_SCRL,                                           CU_SCRR, KC_4,    KC_5,    KC_6, CU_DIRU, CL_BASE,
        _______, KC_PLUS, KC_MINS, KC_DOT,  KC_0,    CU_FSCR,                                           CU_WALL, KC_1,    KC_2,    KC_3, KC_SLSH, _______,
        _______, _______, KC_PLUS, KC_TAB,  KC_EQL,  CU_DTOP, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_DTOP, KC_7,    KC_8,    KC_9, _______, _______,
        /* */                      CU_SCRZ, _______, _______, CU_APPR, _______, /* */ _______, _______, _______, _______, CU_APPZ
        ),

/* SYNTAX

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   =  |   #  |   !  |   $  | AppP |                              | AppN |   >  |   ?  |   <  |   -  | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   \  |   (  |   :  |   )  |  Up  |                              |AppWin|   }  |   ;  |   {  |   /  |      |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      | `  ~ |  Tab | '  " | Left |      |      |  |      |      | Right|   ]  |   |  |   [  |      |      |
 |  Cmd | Shift|      |      |      |      | BkSp |      |  | Enter| Space|      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+---------------------------'
 |                    |(EncL)|Compse|      |      | (**) |  |      |      |      |Compse|(EncR)|
 |                    |      |      |      |      |      |  |      |      |      |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [SYNTAX] = LAYOUT(
        _______, KC_EQL,  KC_HASH, KC_EXLM, KC_DLR,  CU_APPP,                                           CU_APPN, KC_RABK, KC_QUES, KC_LABK, KC_MINS, CL_BASE,
        _______, KC_BSLS, KC_LPRN, KC_COLN, KC_RPRN, KC_UP,                                             CU_WAPP, KC_RCBR, KC_SCLN, KC_LCBR, KC_SLSH, _______,
        _______, _______, KC_GRV,  KC_TAB,  KC_QUOT, KC_LEFT, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_RGHT, KC_RBRC, KC_PIPE, KC_LBRC, _______, _______,
        /* */                      XXXXXXX, _______, XXXXXXX, KC_BSPC, _______, /* */ KC_ENT,  KC_SPC,  XXXXXXX, _______, XXXXXXX
        ),

/* EDIT

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc | PgUp | WordL|  Up  | WordR| WinR |                              | WinL | Paste| Copy |  Cut |  All | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      | PgDn | Left | Down | Right| AppR |                              | AppL |      |      |      |      |      |
 | Ctrl |      |      |      |      |      |                              |      |Repeat| Acc2 | Acc1 |DelMod| Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      | HBck | Down | HFwd | TabR |      |      |  |      |      | TabL |      |      |      |      |      |
 |  Cmd | Shift|      |      |      |      | BkSp |  Tab |  |      | AppR |      |  Cmd |  Alt | Ctrl | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse|  Del |      |      |  |      |      |      |Compse|(EncR)|
 |                    |      |      |      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [EDIT] = LAYOUT(
        _______, CE_PG_U, CE_WD_L, CE_MV_U, CE_WD_R, CU_WINR,                                           CU_WINL, CU_PAST, CU_COPY, CU_CUT,  CU_ALL,  CL_BASE,
        _______, CE_PG_D, CE_MV_L, CE_MV_D, CE_MV_R, CU_APPR,                                           CU_APPL, CE_REPT, CE_ACC2, CE_ACC1, CE_DMOD, _______,
        _______, _______, CU_HBCK, CE_MV_D, CU_HFWD, CU_TABR, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_TABL, KC_RGUI, KC_RALT, KC_RCTL, _______, _______,
        /* */                      XXXXXXX, _______, KC_DEL,  KC_BSPC, KC_TAB,  /* */ XXXXXXX, CU_APPR, _______, _______, XXXXXXX
        ),

/* CURSOR

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc | SSScr| SSWin| MS_U | SSRgn| WinR |                              | WinL | Paste| Copy |  Cut |  All | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |      | MS_L | MS_D | MS_R | AppR |                              | AppL |      |      |      |      |      |
 | Ctrl | Wheel|      |      |      |      |                              |      |Repeat| Acc2 | Acc1 | Slow | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      | HBck | MS_D | HFwd | TabR |      |      |  |      |      | TabL |      |      |      |      |      | 
 |  Cmd | Shift|      |      |      |      | BtnL | BtnR |  |      |      |      |  Cmd |  Alt | Ctrl | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse| BtnM |      |      |  |      |      |      |Compse|(EncR)|
 |                    |      |      |      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [CURSOR] = LAYOUT(
        _______, CU_SSCR, CU_SWIN, CM_MS_U, CU_SRGN, CU_WINR,                                            CU_WINL, CU_PAST, CU_COPY, CU_CUT,  CU_ALL,  CL_BASE,
        _______, CM_WHEE, CM_MS_L,  CM_MS_D, CM_MS_R, CU_APPR,                                           CU_APPL, CM_REPT, CM_ACC2, CM_ACC1, CM_SLOW, _______,
        _______, _______, CU_HBCK,  CM_MS_D, CU_HFWD, CU_TABR, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_TABL, KC_RGUI, KC_RALT, KC_RCTL, _______, _______,
        /* */                       CM_BTN1, _______, CM_BTN3, CM_BTN1, CM_BTN2, /* */ XXXXXXX, XXXXXXX, _______, _______, XXXXXXX
        ),

/* FUNC

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |      |      | !MAC | !WIN |      |                              |      |  F4  |  F5  |  F6  |      | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |      |      |!PRIME|!RSTHD|      |                              |      |  F1  |  F2  |  F3  |      |      |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |  |      |      |      |  F7  |  F8  |  F9  |      |      |
 |  Cmd | Shift| Ctrl |  Alt |  Cmd |      |      | !WIPE|  |  F10 |  F11 |      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse|      |      |      |  |      |      | F12  |Compse|(EncR)|
 |                    |      |      | (**) |      |      |  |      |      |      |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [FUNC] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, CU_MAC,  CU_WIN,  XXXXXXX,                                           XXXXXXX, KC_F4,   KC_F5,   KC_F6,   XXXXXXX, CL_BASE,
        _______, XXXXXXX, XXXXXXX, CU_PRIM, CU_RSTH, XXXXXXX,                                           XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, _______,
        _______, _______, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   _______, _______,
        /* */                      CU_SAVE, _______, _______, XXXXXXX, CU_WIPE, /* */ KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE
        ),
};
// clang-format on

/**
 * App switcher i.e. Alt-Tab on Windows, Cmd-Tab on macOS.
 *
 * FIXME: move to separate file
 * FIXME: tie release to layer activation key when using from keyboard
 */
#ifndef APP_SWITCHER_TERM
#    define APP_SWITCHER_TERM 1000
#endif

static bool     app_switcher_active = false;
static uint16_t app_switcher_timer  = 0;

void app_switcher_tick(void) {    // Call from matrix_scan_user()
    if (app_switcher_active) {
        if (timer_elapsed(app_switcher_timer) > APP_SWITCHER_TERM) {
            unregister_code(SC(SC_APPSWITCH_START));
            app_switcher_active = false;
        }
    }
}

void app_switcher_record(uint16_t keycode, bool pressed) {    // Call from process_record_user.
    if (pressed) {
        if (!app_switcher_active) {
            app_switcher_active = true;
            register_code(SC(SC_APPSWITCH_START));
        }
        app_switcher_timer = timer_read();
        register_code16(keycode == CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
    } else {
        unregister_code16(keycode == CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
    }
}

/**
 * Process keys with a custom shift value.
 */
void custom_shift(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
    uint8_t mods = get_mods();
    if (record->event.pressed) {
        if (mods & MOD_MASK_SHIFT) {    // shifted case
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

/**
 * User-level processing of custom keycodes.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t  mods     = get_mods();
    uint16_t tempcode = KC_NO;

    // Check for interrupt to layer-tap-toggle
    ltt_interrupt(keycode, record);

    // Check to see if we intercept for a compose sequence
#ifdef COMPOSE_KEY
    if (compose_key_intercept(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        
            // Directory up
        case CU_DIRU:
            if (record->event.pressed) {
                tap_code(KC_DOT);
                tap_code(KC_DOT);
                tap_code(KC_SLASH);
            }
            break;

            /* Custom keycodes related to Shift. Both shift keys are custom keycodes;
             * both are pressed to toggle caps-lock. In addition, there are a number of
             * keys that have different character than normal if Shift is pressed.
             */
        case CU_LSFT:
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

        case CU_EXCLAIM_QUESTION:
            custom_shift(KC_EXCLAIM, KC_QUESTION, record);
            break;

        case CU_SPACE_ENTER:
            custom_shift(KC_SPACE, KC_ENTER, record);
            break;

            /* "Hyper" back and forward -
             *
             *   No mods: undo and redo
             *   Cmd:     browser back and forward
             *   Alt:     next and previous search result
             *
             * FIXME: check if there will be an error if the modifier is released first
             */
        case CU_HYPER_BACK:
        case CU_HYPER_FORWARD:
            if (mods & MOD_MASK_GUI) {
                tempcode = keycode == CU_HYPER_BACK ? SC(SC_BROWSER_BACK) : SC(SC_BROWSER_FWD);
            } else if (mods & MOD_MASK_ALT) {
                tempcode = keycode == CU_HYPER_BACK ? SC(SC_PREV_SEARCH) : SC(SC_NEXT_SEARCH);
            } else {
                tempcode = keycode == CU_HYPER_BACK ? SC(SC_UNDO_ACTION) : SC(SC_REDO_ACTION);
            }
            if (record->event.pressed) {
                clear_mods();
                register_code16(tempcode);
                set_mods(mods);
            } else {
                unregister_code16(tempcode);
            }
            break;

            /* Take a screenshot of the window under the cursor.
             *
             * FIXME: currently works on macOS only, need a Windows version
             */
        case CU_SWIN:
            if (record->event.pressed) {
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

            /* Take screenshot of a region. This does the initial mouse press,
             * so after pressing the key, drag with the mouse keys then press
             * mouse button 1 to complete the screenshot.
             *
             * FIXME: currently works on macOS only, need a Windows version
             */
        case CU_SRGN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SHOT_REGION));
#ifdef CUSTOM_MOUSE
                _delay_ms(100);
                custom_mouse_button_press(CM_BTN1, true);
#endif
            }
            break;

            /* Switch between applications (aka Alt-Tab on Windows or Cmd-Tab on macOS).
             *
             * FIXME: needs to be tied to the layer key that these keycodes are
             * on, so that a. there is no delay on releasing and b. auto-repeat
             * works. (The current implementation was designed for encoder use
             * only.)
             */
        case CU_APPR:
        case CU_APPL:
            app_switcher_record(keycode, record->event.pressed);
            break;

            /* Switch between tabs. With some apps on macOS, this doesn't work,
             * so press Cmd/Gui as well and it might work then.
             */
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

            /* Wipe the EEPROM. Handy if you get stuck when you have multiple
             * default layers.....  After doing this, power-cycle the
             * keyboard. There will be no visible indication...
             */
        case CU_WIPE:
            if (record->event.pressed) {
                eeconfig_init();
            }
            break;

            /* Save RGB state to EEPROM.
             */
#ifdef RGBLIGHT_ENABLE
        case CU_SAVE:
            if (record->event.pressed) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
            }
            break;
#endif

            /* Switch the default layer and write to EEPROM.
             */
        case CU_PRIM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(PRIME);
                layer_clear();
                return false;
            }
            break;

        case CU_RSTH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(RSTHD);
                layer_clear();
                return false;
            }
            break;

            /* Layer switching using the layer-tap-toggle function
             */
#ifdef LAYER_TAP_TOGGLE
        case CL_BASE:
            return ltt_base();    // Clear all layers and go back to the default layer
            break;

        case CL_NUMP:
            return layer_tap_toggle2(KC_QUOT, NUMPAD, FUNC, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle2(KC_QUOT, EDIT, CURSOR, record);
            break;

        case CL_SYNT:
            return layer_tap_toggle(KC_TAB, SYNTAX, record);
            break;
#endif

            // Toggle compose mode on or off
#ifdef COMPOSE_KEY
        case CU_COMPOSE:
            process_record_compose(keycode, record);
            break;
#endif

            // Custom mouse keycodes
#ifdef CUSTOM_MOUSE
            CUSTOM_MOUSE_PROCESS_RECORD(keycode, record);
#endif

            // Custom editing keycodes
#ifdef CUSTOM_EDIT
            CUSTOM_EDIT_PROCESS_RECORD(keycode, record);
#endif

            /* Select the OS used for shortcuts and write to EEPROM. Currently
             * only Mac and Win supported, Linux to be added later.
             */
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

            /* Process OS shortcut keycodes. This is compiled in only if
             * dynamically defined shortcuts are enabled.
             */
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
        default:
            process_record_shortcut(keycode, record);
            break;
#endif

    }    // switch

#ifdef DELETEME
        /* Do default processing for all OS shortcut keycodes
         */
#    if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    process_record_shortcut(keycode, record);
#    endif
#endif

    return true;
}

/**
 * User-level matrix scan hook.
 */
void matrix_scan_user(void) {
    // App-switcher timeout
    app_switcher_tick();

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

#ifdef LEADER_ENABLE
    // Process leader keys
    matrix_scan_leader();
#endif
}
