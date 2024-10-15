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

/* ALPHA v42

 ,-----------------------------------------.                        ,-----------------------------------------.
 |  Esc |   B  |   C  |   W  |   F  |   Z  |                        |Search|   M  |   U  | .  ! | -  _ |   Q  |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   V  |                        | ;  : |   N  |   I  |   O  |   A  | '  " |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |  Tab |      |   P  |   G  |   D  |                                      |   L  |   Y  | ,  ? |      | Enter|
 | META | Shift|      |      |      |                                      |      |      |      | Shift| META |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 | Mute |      | Enter| Space|Repeat|  | Space|   E  |  Tab |BkSp/D|
 .                 |      |      | EDIT |      |      |  |      |      | SYMS |      |
 .                 `------'      `--------------------'  `---------------------------'
*/
    [ALPHA] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_ESC,   KC_B,     KC_C,  KC_W,  KC_F,  KC_Z,
        KC_X,     KC_R,     KC_S,  KC_T,  KC_H,  KC_V,
        CL_META,  KC_LSFT,  KC_P,  KC_G,  KC_D,

        /* Right hand */
                  SC_SEARCH, KC_M,  KC_U,  CU_DOT,  KC_MINS, KC_Q,
                  KC_SCLN,   KC_N,  KC_I,  KC_O,    KC_A,    KC_QUOT,
                             KC_L,  KC_Y,  CU_COMM, KC_RSFT, CL_META_R,

        /* Thumbs */
        CL_EDIT, KC_SPC, CU_REPT,   KC_SPACE, KC_E, CL_SYMS, CU_BSPC_DEL,

        /* Encoder button */
        KC_MUTE
    ),


/* SYMS

 ,-----------------------------------------.                        ,-----------------------------------------.
 | ^  ~ |   +  | (  [ |   *  | )  ] |  ../ |                        | AppR | Paste| Copy |  Cut |  All |   #  |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   $  | 7  @ | 6  { | 5  % | 0  } |   9  |                        |   8  | 1  ` | 2 Tab|   3  |   4  |   =  |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |  Tab |   -  | <  & |   /  | >  | |                                      |      |      |      |      |      |
 |      |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift| SNAP |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 |      |      | Enter| Space|   .  |  |      |      |      |      |
 .                 |      |      |      |      |      |  |      |      | (**) |      |
 .                 `------'      `--------------------'  `---------------------------'
*/

    [SYMS] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_CIRC,      KC_PLUS,       CU_LPRN,  KC_ASTR,       CU_RPRN,  CU_DIRUP,
        KC_DLR,       CU_7,          CU_6,     CU_5,          CU_0,     CU_9,
        CU_TAB_TAB,   CU_MINS_MINS,  CU_LT,    CU_SLSH_SLSH,  CU_GT,

        /* Right hand */
                  CU_APPSWITCH_RIGHT,  SC_PASTE,  SC_COPY,  SC_CUT,   SC_SELECT_ALL,  KC_HASH,
                  CU_8,                CU_1,      CU_2,     CU_3,     CU_4,           CU_EQL_EQL,
                                       KC_RGUI,   KC_RALT,  KC_RCTL,  CU_SHIFT,       CL_SNAP,

        /* Thumbs */
        CU_ENT_ENT, CU_SPC_SPC, CU_DOT_DOT,   ___X___, ___X___, _______, ___X___,

        /* Encoder button */
        ___X___
    ),


/* EDIT
 
 ,-----------------------------------------.                        ,-----------------------------------------.
 |AppWin|  All |  Cut | Copy | Paste| AppR |                        | ScrL | Home |  Up  |  End | PgUp |ScrR/L|
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |Expose|      |      |      |      |FulScr|                        |TabR/L| Left | Down | Right| PgDn |WinR/L|
 |      |Delete| More |  x4  | Fast |      |                        |      |      |      |      |      |      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      | Undo | Space| Redo |      |AppR/L|
 | FUNC | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      | Shift|      |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 |      |      |      |      |      |  | Enter|BkSp/D|  Tab |      |
 .                 |      |      | (**) |      |      |  |      |      |      |      |
 .                 `------'      `--------------------'  `---------------------------'
*/

    [EDIT] = KEY_LAYOUT_stack(
        /* Left hand */
        SC_EXPOSE_APP,  SC_SELECT_ALL,  SC_CUT,   SC_COPY,  SC_PASTE,  CU_APPSWITCH_RIGHT,
        CU_EXPOSE_ALL,  CE_DELETE,      CE_MORE,  CE_X4,    CE_FAST,   SC_FULLSCREEN,
        CL_FUNC,        CU_SHIFT,       KC_LCTL,  KC_LALT,  KC_LGUI,

        /* Right hand */
                     SC_PREV_SCREEN,  CE_HOME,  CE_UP,    CE_END,    CE_PAGE_UP,    CU_SCREEN_RL,
                     CU_TAB_RIGHT,    CE_LEFT,  CE_DOWN,  CE_RIGHT,  CE_PAGE_DOWN,  CU_NEXT_WINDOW,
                                      SC_UNDO,  KC_SPC,   SC_REDO,   CU_SHIFT,      CU_APPSWITCH_RIGHT,

        /* Thumbs */
        _______, ___X___, ___X___,   CU_ENT_ENT, CU_BSPC_DEL, KC_TAB, ___X___,

        /* Encoder button */
        ___X___
    ),


/* META

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |  Bin | Close|      | Find | BriU |                        | VolU |PrvTrk| Play |NxtTrk| Mute |SysSet|
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | eXit |Reload| Save |newTab|DskTop| BriD |                        | VolD |  New |      | Open |saveAs| Quit |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      | Print| Prev | Next |                                      | Back |  Fwd |AppSet|      |      |
 | (**) | Shift|      |      |      |                                      |      |      |      | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 |      |      |      | Btn1 | Btn2 |  | Btn2 | Btn1 |      |      |
 .                 |      |      | FUNC |      |      |  |      |      | SNAP |      |
 .                 `------'      `--------------------'  `---------------------------'
 */

    [META] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___, SC_BIN,      SC_CLOSE_TAB, ___X___,        SC_FIND,           SC_BRIGHTNESS_UP,
        SC_QUIT, SC_RELOAD,   SC_SAVE,      SC_NEW_TAB,     SC_REVEAL_DESKTOP, SC_BRIGHTNESS_DOWN,
        _______, CU_SHIFT,    SC_PRINT,     SC_PREV_SEARCH, SC_NEXT_SEARCH,

        /* Right hand */
                 KC_VOLU,  KC_MPRV,         KC_MPLY,        KC_MNXT,          KC_MUTE,     SC_SYS_SETTINGS,
                 KC_VOLD,  SC_NEW,          ___X___,        SC_OPEN,          SC_SAVE_AS,  SC_QUIT,
                           SC_BROWSER_BACK, SC_BROWSER_FWD, SC_APP_SETTINGS,  CU_SHIFT,    _______,

        /* Thumbs */
        CL_FUNC, CM_BTN1, CM_BTN2,   CM_BTN2, CM_BTN1, CL_SNAP, ___X___,

        /* Encoder button */
        ___X___
    ),


/* FUNC

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |      |      |      |      |      |                        |      |  F5  |  F6  |  F7  |  F8  |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |      |      | !MAC | !WIN |!LINUX|      |                        |      |  F1  |  F2  |  F3  |  F4  |      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      |  F9  |  F10 |  F11 |  F12 |      |
 | (**) | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      | (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 |      |      |      |      |      |  |      |      |      |      |
 .                 |      |      | (**) |      |      |  |      |      |      |      |
 .                 `------'      `--------------------'  `---------------------------'
 */
    [FUNC] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___,  ___X___,  ___X___,   ___X___,     ___X___,   ___X___,
        ___X___,  ___X___,  CU_MACOS,  CU_WINDOWS,  CU_LINUX,  ___X___,
        _______,  KC_LSFT,  KC_LCTL,   KC_LALT,     KC_LGUI,

        /* Right hand */
                 ___X___,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   ___X___,
                 ___X___,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   ___X___,
                           KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,

        /* Thumbs */
        _______, ___X___, ___X___,   ___X___, ___X___, ___X___, ___X___,

        /* Encoder button */
        ___X___
    ),


/* SNAP

 ,-----------------------------------------.                        ,-----------------------------------------.
 | SnapT| ZmIn | SL23 | SMax | SR23 |LghtUp|                        |      | SPrev| SVert|      |      |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | SnapB| ZmOut| SL12 | SM23 | SR12 |LghtDn|                        |      | SSRgn| SSWin| SSScr| SSApp|!WRITE|
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |  Zm0 | SL14 | SM12 | SR14 |                                      |      |      |      |      |      |
 | (**) |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,---------------------------.
 .                 |  Z0  |      |MvPrev|FulScr|MvNext|  |      | !WIPE|      |      |
 .                 |      |      |      |      |      |  |      |      | (**) |      |
 .                 `------'      `--------------------'  `---------------------------'
*/

    [SNAP] = KEY_LAYOUT_stack(
        /* Left hand */
        SC_SNAP_TOP,    SC_APP_ZOOM_IN,    SC_SNAP_LEFTTWOTHIRDS, SC_SNAP_MAXIMIZE,     SC_SNAP_RIGHTTWOTHIRDS,  CU_LGHTUP,
        SC_SNAP_BOTTOM, SC_APP_ZOOM_OUT,   SC_SNAP_LEFT,          SC_SNAP_MIDTWOTHIRDS, SC_SNAP_RIGHT,           CU_LGHTDN,
        _______,        SC_APP_ZOOM_RESET, SC_SNAP_LEFTQUARTER,   SC_SNAP_MIDDLE,       SC_SNAP_RIGHTQUARTER,

         /* Right hand */
                 ___X___, SC_SNAP_PREVIOUS,  SC_SNAP_VERTICAL,  ___X___,            ___X___,         ___X___,
                 ___X___, CU_SCRSHOT_RGN,    CU_SCRSHOT_WIN,    SC_SCRSHOT_SCREEN,  SC_SCRSHOT_APP,  CU_WRITE,
                          KC_RGUI,           KC_RALT,           KC_RCTL,            KC_RSFT,         _______,

        /* Thumbs */
        SC_MOVETO_PREV_SCREEN, SC_FULLSCREEN, SC_MOVETO_NEXT_SCREEN,   ___X___, CU_WIPE, _______, ___X___,

        /* Encoder button */
        SC_APP_ZOOM_RESET
    ),

};
// clang-format on


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_user_common(keycode, record);
}


