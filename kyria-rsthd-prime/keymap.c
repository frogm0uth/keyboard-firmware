/* Copyright 2020-2023 @frogm0uth
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
 * Keymap
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA v41

 ,-----------------------------------------.                        ,-----------------------------------------.
 |  Esc |   B  |   C  |   W  |   F  |   Z  |                        |Search|   M  |   U  | .  ! | -  _ |   Q  |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   V  |                        | ;  : |   N  |   I  |   O  |   A  | Enter|
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |  Tab |      |   P  |   G  |   D  |                                      |   L  |   Y  | ,  ? |      |BkSp/D|
 | META | Shift|      |      |      |                                      |      |      |      | Shift| META |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 | Mute |      | Enter| Space|Repeat|  | '  " |   E  |  Tab |
 .                 |      |      | EDIT |      |      |  |      |      | SYMS |
 .                 `------'      `--------------------'  `--------------------'
*/
    [ALPHA] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_ESC,   KC_B,     KC_C,  KC_W,  KC_F,  KC_Z,
        KC_X,     KC_R,     KC_S,  KC_T,  KC_H,  KC_V,
        CL_META,  KC_LSFT,  KC_P,  KC_G,  KC_D,

        /* Right hand */
                  SC_SEARCH, KC_M,  KC_U,  CU_DOT,  KC_MINS, KC_Q,
                  KC_SCLN,   KC_N,  KC_I,  KC_O,    KC_A,    KC_ENT,
                             KC_L,  KC_Y,  CU_COMM, KC_RSFT, CL_META_R,

        /* Thumbs */
        CL_EDIT, KC_SPC, CU_REPT,   KC_QUOT, KC_E, CL_SYMS,

        /* Encoder button */
        KC_MUTE
    ),


/* SYMS

 ,-----------------------------------------.                        ,-----------------------------------------.
 |   ^  |   +  | (  [ |   *  | )  ] |  ../ |                        | AppR | Paste| Copy |  Cut |  All |   #  |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   9  | 4  @ | 3  { | 2  % | 1  } |  Tab |                        |   =  | 0  ` | 5 Tab|   6  |   7  |   8  |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |   ~  |   -  | <  & |   /  | >  | |                                      |      |      |      |      |   $  |
 |      |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift|      |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      | Enter| Space|   .  |  |      |      |      |
 .                 |      |      |      |      |      |  |      |      | (**) |
 .                 `------'      `--------------------'  `--------------------'
*/

    [SYMS] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_CIRC,  KC_PLUS,       CU_LPRN,  KC_ASTR,       CU_RPRN,  CU_DIRUP,
        CU_9,     CU_4,          CU_3,     CU_2,          CU_1,     KC_TAB,
        KC_TILD,  CU_MINS_MINS,  CU_LT,    CU_SLSH_SLSH,  CU_GT,

        /* Right hand */
                  CU_APPSWITCH_RIGHT,  SC_PASTE,  SC_COPY,  SC_CUT,   SC_SELECT_ALL,  KC_HASH,
                  CU_EQL_EQL,          CU_0,      CU_5,     CU_6,     CU_7,           CU_8,
                                       KC_RGUI,   KC_RALT,  KC_RCTL,  CU_SHIFT,       KC_DLR,

        /* Thumbs */
        CU_ENT_ENT, CU_SPC_SPC, CU_DOT_DOT,   ___X___, ___X___, _______,

        /* Encoder button */
        ___X___
    ),


/* EDIT

 ,-----------------------------------------.                        ,-----------------------------------------.
 |  Esc |  All |  Cut | Copy | Paste| AppR |                        |Expose| Home |  Up  |  End | PgUp | ScrR |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |FulScr|      |      |      |      |AppWin|                        | TabR | Left | Down | Right| PgDn | WinR |
 |      |Delete| More |  x4  | Fast |      |                        |      |      |      |      |      |      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 | SNAP |      |      |      |      |                                      | Undo | Space| Redo |  Tab | AppR |
 |      | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      |      |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |      |      |      |  | Enter| BkSp |  Del |
 .                 |      |      | (**) |      |      |  |      |      |      |
 .                 `------'      `--------------------'  `--------------------'
*/

    [EDIT] = KEY_LAYOUT_stack(
        /* Left hand */
        _______,        SC_SELECT_ALL,  SC_CUT,   SC_COPY,  SC_PASTE,  CU_APPSWITCH_RIGHT,
        SC_FULLSCREEN,  CE_DELETE,      CE_MORE,  CE_X4,    CE_FAST,   SC_EXPOSE_APP,
        CL_SNAP,        CU_SHIFT,       KC_LCTL,  KC_LALT,  KC_LGUI,

        /* Right hand */
                     CU_EXPOSE_ALL,   CE_HOME,  CE_UP,    CE_END,    CE_PAGE_UP,    CU_SCREEN_RL,
                     CU_TAB_RIGHT,    CE_LEFT,  CE_DOWN,  CE_RIGHT,  CE_PAGE_DOWN,  CU_NEXT_WINDOW,
                                      SC_UNDO,  KC_SPC,   SC_REDO,   KC_TAB,        CU_APPSWITCH_RIGHT,

        /* Thumbs */
        _______, ___X___, ___X___,   CU_ENT_ENT, KC_BSPC, KC_DEL,

        /* Encoder button */
        ___X___
    ),


/* META

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |  Bin | Close|Dsktop| Find | BriU |                        | VolU |PrvTrk| Play |NxtTrk| Mute |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | eXit |Reload| Save |newTab|      | BriD |                        | VolD |  New |      | Open |saveAs| Quit |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      | Print| Prev | Next |                                      | Back |  Fwd |AppSet|      |      |
 | (**) | Shift|      |      |      |                                      |      |      |      | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |      |      |      |  |SysSet|      |      |
 .                 |      |      | SNAP |      |      |  |      |      | FUNC |
 .                 `------'      `--------------------'  `--------------------'
 */

    [META] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___, SC_BIN,      SC_CLOSE_TAB, SC_REVEAL_DESKTOP, SC_FIND,     SC_BRIGHTNESS_UP,
        SC_QUIT, SC_RELOAD,   SC_SAVE,      SC_NEW_TAB,     ___X___,        SC_BRIGHTNESS_DOWN,
        _______, CU_SHIFT,    SC_PRINT,     SC_PREV_SEARCH, SC_NEXT_SEARCH,

        /* Right hand */
                 KC_VOLU,  KC_MPRV,         KC_MPLY,        KC_MNXT,         KC_MUTE,     ___X___,
                 KC_VOLD,  SC_NEW,          ___X___,        SC_OPEN,         SC_SAVE_AS,  SC_QUIT,
                           SC_BROWSER_BACK, SC_BROWSER_FWD, SC_APP_SETTINGS, CU_SHIFT,    _______,

        /* Thumbs */
        CL_SNAP, ___X___, ___X___, SC_SYS_SETTINGS, ___X___, CL_FUNC,

        /* Encoder button */
        ___X___
    ),


/* FUNC

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |  F8  |  F7  |  F6  |  F5  |LghtUp|                        |      | !Mac | !Win |!Linux|      |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |      |  F4  |  F3  |  F2  |  F1  |LghtDn|                        |      | SSRgn| SSWin| SSScr| SSApp|!WRITE|
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |  F12 |  F11 |  F10 |  F9  |                                      |      |      |      |      |      |
 | (**) |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |  Z0  |      |      | Btn1 | Btn2 |  | !WIPE|      |      |
 .                 |      |      |      |      |      |  |      |      | (**) |
 .                 `------'      `--------------------'  `--------------------'
 */

    [FUNC] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___,  KC_F8,     KC_F7,    KC_F6,    KC_F5,  CU_LGHTUP,
        ___X___,  KC_F4,     KC_F3,    KC_F2,    KC_F1,  CU_LGHTDN,
        _______,  KC_F12,    KC_F11,   KC_F10,   KC_F9,

        /* Right hand */
                 ___X___,   CU_MACOS,        CU_WINDOWS,      CU_LINUX,          ___X___,        ___X___,
                 ___X___,   CU_SCRSHOT_RGN,  CU_SCRSHOT_WIN,  SC_SCRSHOT_SCREEN, SC_SCRSHOT_APP, CU_WRITE,
                            KC_RGUI,         KC_RALT,         KC_RCTL,           CU_SHIFT,       _______,

        /* Thumbs */
        _______, CM_BTN1, CM_BTN2,   CU_WIPE, ___X___, _______,

        /* Encoder button */
        SC_APP_ZOOM_RESET
    ),


/* SNAP

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |      |      |      |      |      |                        | SPrev| SL23 | SMax | SR23 | ZmIn | SnapT|
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |!WRITE| SSApp| SSScr| SSWin| SSRgn|      |                        | SVert| SL12 | SM23 | SR12 | ZmOut| SnapB|
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      | SL14 | SM12 | SR14 |  Zm0 |      |
 | (**) | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      | (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |      |      | !WIPE|  |      | Btn1 | Btn2 |
 .                 |      |      | (**) |      |      |  |      |      |      |
 .                 `------'      `--------------------'  `--------------------'
 */

    [SNAP] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___,  ___X___,           ___X___,              ___X___,        ___X___,        ___X___,
        CU_WRITE, SC_SCRSHOT_APP,    SC_SCRSHOT_SCREEN,    CU_SCRSHOT_WIN, CU_SCRSHOT_RGN, ___X___,
        _______,  CU_SHIFT,          KC_LCTL,              KC_LALT,        KC_LGUI,

         /* Right hand */
                 SC_SNAP_PREVIOUS,  SC_SNAP_LEFTTWOTHIRDS, SC_SNAP_MAXIMIZE,     SC_SNAP_RIGHTTWOTHIRDS, SC_APP_ZOOM_IN,    SC_SNAP_TOP,
                 SC_SNAP_VERTICAL,  SC_SNAP_LEFT,          SC_SNAP_MIDTWOTHIRDS, SC_SNAP_RIGHT,          SC_APP_ZOOM_OUT,   SC_SNAP_BOTTOM,
                                    SC_SNAP_LEFTQUARTER,   SC_SNAP_MIDDLE,       SC_SNAP_RIGHTQUARTER,   SC_APP_ZOOM_RESET, _______,

        /* Thumbs */
        _______, ___X___, CU_WIPE,   ___X___, CM_BTN1, CM_BTN2,

        /* Encoder button */
        ___X___
    ),

};
// clang-format on



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_user_common(keycode, record);
}


