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
 * Keymap
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
/* RSTHD

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   J  |   C  |   Y  |   F  |   K  |                              |   Z  |   L  | .  - |   U  |   Q  |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   R  |   S  |   T  |   H  |   D  |                              |   M  |   N  |   A  |   I  |   O  |      |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |   V  |   G  |   P  |   B  |      |      |  |      |      |   X  |   W  | ,  _ | ;  : |      |      |
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
#ifdef UNUSED
    [RSTHD] = LAYOUT(
        KC_ESC,  KC_J,    KC_C,   KC_Y,    KC_F,    KC_K,                                              KC_Z,    KC_L,    KC_DOT,  KC_U,    KC_Q,    XXXXXXX,
        KC_LCTL, KC_R,    KC_S,   KC_T,    KC_H,    KC_D,                                              KC_M,    KC_N,    KC_A,    KC_I,    KC_O,    KC_RCTL,
        KC_LGUI, CU_LSFT, KC_V,   KC_G,    KC_P,    KC_B,    XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_X,    KC_W,    KC_COMM, KC_SCLN, CU_RSFT, KC_RGUI,
        /* */                     CU_SLCK, CU_DEAD, CL_NUMP, KC_E,    CL_SYNT, /* */ CU_AENT, KC_SPC,  CL_EDIT, CU_DEAD, CU_SSLP
        ),
#endif
    
/* PRIME


 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   V  |   C  |   W  |   D  |   K  |                              |   J  |   M  |   U  | .  / | -  _ |Compse|
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   F  |                              | ;  : |   N  |   I  |   O  |   A  |  Q   |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab |      |   B  |   G  |   P  |   Z  |      |      |  |      |      | !  ? |   L  |   Y  | ,  " |      |  Tab |
 |SYNTAX| Shift|      |      |      |      |   E  |  ED  |  | Enter| Space|      |      |      |      | Shift|SYNTAX|
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|      | '  " |      |      |  |      |      | '  " |      |(EncR)|
 |                    |      |      | FUNC |      |      |  |      |      | CURS |      |      |
 |                    |      |  Alt | NUMS |      |      |  |      |      | EDIT |  Cmd |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [PRIME] = LAYOUT(
        KC_ESC,  KC_V,    KC_C,   KC_W,    KC_D,    KC_K,                                              KC_J,    KC_M,    KC_U,   CU_DTSL, KC_MINS, CU_DEAD,
        CU_CX,   HK_R,    HK_S,   HK_T,    HK_H,    KC_F,                                              KC_SCLN, HK_N,    HK_I,   HK_O,    HK_A,    CU_CQ,
        CL_SYNT, CU_LSFT, KC_B,   KC_G,    KC_P,    KC_Z,    XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_EXQU, KC_L,    KC_Y,   CU_CMDQ, CU_RSFT, CL_SYNT,
        /* */                     CU_SLCK, KC_LALT, CL_NUMP, KC_E,    CU_ED,   /* */ KC_ENTER, KC_SPC, CL_EDIT, KC_RGUI, CU_SSLP
        ),

/* NUMPAD

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |  All |  Cut | Copy | Paste| ScrL |                              | ScrR | 4  $ | 5  % | 6  ^ |      | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   *  |   -  |   .  |   0  |FulScr|                              |Expose| 1  ! | 2  @ | 3  # |   /  |
 | Ctrl |      |      |      |      |      |                              |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |   +  |  Tab |   =  |DskTop|      |      |  |      |      |DskTop| 7  & | 8  * | 9  ( |      |      |
 |  Cmd | Shift|      |      |      |      | AppR |  Tab |  | Enter| Space|      |      |      |      | Shift|  Cmd |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse|      |      |SYNTAX|  |      |      | '  " |Compse|(EncR)|
 |                    |      |      | (--) |      |      |  |  Alt |      |CURSOR|      |      |
 |                    |      |      | (**) |      |      |  |      |      | EDIT |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [NUMPAD] = LAYOUT(
        _______, CU_ALL,  CU_CUT,  CU_COPY, CU_PAST, CU_SCRL,                                           CU_SCRR, KC_4,    KC_5,    KC_6, XXXXXXX, CL_BASE,
        _______, KC_ASTR, KC_MINS, KC_DOT,  KC_0,    CU_FSCR,                                           CU_XPSE, KC_1,    KC_2,    KC_3, KC_SLSH, _______,
        _______, _______, KC_PLUS, KC_TAB,  KC_EQL,  CU_DTOP, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_DTOP, KC_7,    KC_8,    KC_9, _______, _______,
        /* */                      CU_SCRZ, _______, _______, CU_APPR, _______, /* */ _______, _______, _______, _______, CU_APPZ
        ),

/* SYNTAX

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   =  |   #  |   !  |   $  | AppP |                              | AppN |   >  |   ?  |   <  |   -  | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |   \  |   (  |   :  |   )  |  Up  |                              | AppX |   }  |   ;  |   {  |   /  |      |
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
        _______, KC_BSLS, KC_LPRN, KC_COLN, KC_RPRN, KC_UP,                                             CU_APPX, KC_RCBR, KC_SCLN, KC_LCBR, KC_SLSH, _______,
        _______, _______, KC_GRV,  KC_TAB,  KC_QUOT, KC_LEFT, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, KC_RGHT, KC_RBRC, KC_PIPE, KC_LBRC, _______, _______,
        /* */                      XXXXXXX, _______, XXXXXXX, KC_BSPC, _______, /* */ KC_ENT,  _______, XXXXXXX, _______, XXXXXXX
        ),

/* EDIT

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc | PgUp | WordL|  Up  | WordR| WinR |                              | WinL | Paste| Copy |  Cut |  All | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      | PgDn | Left | Down | Right| AppR |                              | AppL |      |      |      |      |      |
 |      |      |      |      |      |      |                              |      |Repeat| Acc2 | Acc1 |DelMod|      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      | HBck | Down | HFwd | TabR |      |      |  |      |      | TabL |      |      |      |      |      |
 |      | Shift|      |      |      |      | BkSp |  Tab |  |      | AppR |      |  Cmd |  Alt | Ctrl | Shift|      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse|  Del |      |      |  |      |      |      |Compse|(EncR)|
 |                    |      |      |      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [EDIT] = LAYOUT(
        _______, CE_PG_U, CE_WD_L, CE_MV_U, CE_WD_R, CU_WINR,                                           CU_WINL, CU_PAST, CU_COPY, CU_CUT,  CU_ALL,  CL_BASE,
        KC_TAB,  CE_PG_D, CE_MV_L, CE_MV_D, CE_MV_R, CU_APPR,                                           CU_APPL, CE_REPT, CE_ACC2, CE_ACC1, CE_DMOD, XXXXXXX,
        XXXXXXX, _______, CU_HBCK, CE_MV_D, CU_HFWD, CU_TABR, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_TABL, KC_RGUI, KC_RALT, KC_RCTL, _______, XXXXXXX,
        /* */                      XXXXXXX, _______, KC_DEL,  KC_BSPC,  KC_ENTER,  /* */ XXXXXXX, CU_APPR, _______, _______, XXXXXXX
        ),

/* CURSOR

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc | SSScr| SSWin| MS_U | SSRgn| WinR |                              | WinL | Paste| Copy |  Cut |  All | BASE |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |DskTop|      | MS_L | MS_D | MS_R | AppR |                              | AppL |      |      |      |      |DskTop|
 |      | Wheel|      |      |      |      |                              |      |Repeat| Acc2 | Acc1 | Slow |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |Expose|      | HBck | MS_D | HFwd | TabR |      |      |  |      |      | TabL |      |      |      |      |Expose| 
 |      | Shift|      |      |      |      | BtnL | BtnR |  |      |      |      |  Cmd |  Alt | Ctrl | Shift|      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |(EncL)|Compse| BtnM |      |      |  |      |      |      |Compse|(EncR)|
 |                    |      |      |      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [CURSOR] = LAYOUT(
        _______, CU_SSCR, CU_SWIN, CM_MS_U, CU_SRGN, CU_WINR,                                            CU_WINL, CU_PAST, CU_COPY, CU_CUT,  CU_ALL,  CL_BASE,
        CU_DTOP, CM_WHEE, CM_MS_L,  CM_MS_D, CM_MS_R, CU_APPR,                                           CU_APPL, CM_REPT, CM_ACC2, CM_ACC1, CM_SLOW, CU_DTOP,
        CU_XPSE, _______, CU_HBCK,  CM_MS_D, CU_HFWD, CU_TABR, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, CU_TABL, KC_RGUI, KC_RALT, KC_RCTL, _______, CU_XPSE,
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
        _______, XXXXXXX, XXXXXXX, /*CU_PRIM*/XXXXXXX, /*CU_RSTH*/XXXXXXX, XXXXXXX,                                           XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, _______,
        _______, _______, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, /* */ XXXXXXX, XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   _______, _______,
        /* */                      CU_SAVE, _______, _______, XXXXXXX, CU_WIPE, /* */ KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE
        ),
};
// clang-format on

/**
 * Process keys with a custom shift value.
 */
void process_custom_shift(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
    uint8_t mods = get_mods();
    if (record->event.pressed) {
        if (mods & MOD_MASK_SHIFT && shiftedkey != S(shiftedkey)) {
            del_mods(MOD_MASK_SHIFT);
        }
        register_code16(mods & MOD_MASK_SHIFT ? shiftedkey : key);
        set_mods(mods);
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

#ifdef LAYER_TAP_TOGGLE
    // Check for interrupt to layer-tap-toggle
    ltt_interrupt(keycode, record);
#endif
    
    // Check to see if we intercept for a compose sequence
#ifdef COMPOSE_KEY
    if (compose_key_intercept(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        
            // Directory up
#ifdef UNUSED
        case CU_DIRU:
            if (record->event.pressed) {
                tap_code(KC_DOT);
                tap_code(KC_DOT);
                tap_code(KC_SLASH);
            }
            break;
#endif
           // E-D key
        case CU_ED:
            if (record->event.pressed) {
                if (mods & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_TAB);
                    set_mods(mods);
                } else {
                    tap_code(KC_E);
                    tap_code(KC_D);
                }
                //return false;
            } else {
                unregister_code(KC_TAB);
            }
            break;
#ifdef UNUSED
           // E-R key
        case CU_ER:
            if (record->event.pressed) {
                tap_code(KC_E);
                tap_code(KC_R);
            }
            break;
        case CU_QU:
            if (record->event.pressed) {
                if (mods && !(mods & MOD_MASK_SHIFT)) {
                    register_code(KC_Q);
                } else if (mods & MOD_MASK_SHIFT) {
                    tap_code(KC_Q);
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_U);
                    set_mods(mods);
                } else {
                    tap_code(KC_Q);
                    tap_code(KC_U);
                }
            } else {
                unregister_code(KC_Q);
            }
            break;
 #endif
            
            /* Both shift keys are custom keycodes; both are pressed to toggle
             * caps-lock.
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

            /* Process keys that have a different character than normal if Shift
             * is pressed.
             */
#ifdef UNUSED
        case CU_COMMA_MINUS:
            process_custom_shift(KC_COMMA, KC_MINUS, record);
            return false;
            break;

        case CU_COMMA_UNDERSCORE:
            process_custom_shift(KC_COMMA, KC_UNDERSCORE, record);
            break;

        case CU_DOT_MINUS:
            process_custom_shift(KC_DOT, KC_MINUS, record);
            break;

        case CU_DOT_UNDERSCORE:
            process_custom_shift(KC_DOT, KC_UNDERSCORE, record);
            break;

#endif
        case CU_DOT_SLASH:
            process_custom_shift(KC_DOT, KC_SLASH, record);
            break;

        case CU_COMMA_DOUBLEQUOTE:
            process_custom_shift(KC_COMMA, S(KC_QUOT), record);
            break;

        case CU_EXCLAIM_QUESTION:
            process_custom_shift(KC_EXCLAIM, KC_QUESTION, record);
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
            app_switcher_record(keycode, record);
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

#ifdef UNUSED
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
#endif

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

#ifdef UNUSED
        case CL_SYNTZ:
            return layer_tap_toggle(KC_Z, SYNTAX, record);
            break;
#endif
#endif

            // Toggle compose mode on or off
#ifdef COMPOSE_KEY
        case CU_COMPOSE:
            process_record_compose(keycode, record);
            break;
#endif

            // Process custom mouse keycodes
#ifdef CUSTOM_MOUSE
            CUSTOM_MOUSE_PROCESS_RECORD(keycode, record);
#endif

            // Process custom editing keycodes
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

/**
 * User-level layer change hook.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    /* Release the appswitcher on every layer change.
     */
    app_switcher_release();
    return state;
}

