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


/***** This is the version with E on the left thumb. It is currently out of date
 * in the upper layers and comborolls. It serves as a tryout of the alternate
 * layout for the alphas though.
 */


/**
 * Keymap
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA v42. E on left thumb
 
 ,-----------------------------------------.                        ,-----------------------------------------.
 |  Esc |   B  |   C  |   W  |   F  |   Z  |                        |Search|   M  |   U  | .  ! | -  _ |   Q  |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   V  |                        | ;  : |   N  |   I  |   O  |   A  | '  " |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |  Tab |      |   P  |   G  |   D  |                                      |   L  |   Y  | ,  ? |      | Enter|
 | META | Shift|      |      |      |                                      |      |      |      | Shift| META |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 | Mute |      | Enter|   E  | Space|  |Repeat| Space|  Tab |
 .                 |      |      | SYMS |      |      |  |      |      | EDIT |
 .                 `------'      `--------------------'  `--------------------'
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
        CL_SYMS, KC_E, KC_SPC,   CU_REPT, KC_SPC, CL_EDIT,

        /* Encoder buttons */
        KC_MUTE, ___X___
    ),


/* SYMS

 ,-----------------------------------------.                        ,-----------------------------------------.
 |   #  |  All |  Cut | Copy | Paste| AppR |                        |  ../ | )  ] |   *  | (  [ |   +  | ^  ~ |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   =  |   7  | 6    | 5 Tab| 0  ` |   8  |                        |   9  | 1  } | 2  % | 3  { | 4  @ |   $  |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      | >  | |   /  | <  & |   -  |  Tab |
 | FUNC | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      |      |
 `----------------------------------'                                      `----------------------------------'

 .              ,------.         ,--------------------.  ,--------------------.         ,------.
 .              |      |         |      |      |      |  |   .  | Space| Enter|         |      |
 .              |      |         | (**) |      |      |  |      |      |      |         |      |
 .              `------'         `--------------------'  `--------------------'         `------'
*/

    [SYMS] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_HASH,     SC_SELECT_ALL,  SC_CUT,   SC_COPY,  SC_PASTE,  CU_APPSWITCH_RIGHT,
        CU_EQL_EQL,  CU_7,           CU_6,     CU_5,     CU_0,      CU_8,
        CL_FUNC,     CU_SHIFT,       KC_LCTL,  KC_LALT,  KC_LGUI,

        /* Right hand */
                  CU_DIRUP, CU_RPRN,  KC_ASTR,       CU_LPRN,  KC_PLUS,       CU_CIRC,
                  CU_9,     CU_1,     CU_2,          CU_3,     CU_4,          KC_DLR,
                            CU_GT,    CU_SLSH_SLSH,  CU_LT,    CU_MINS_MINS,  KC_TILD,

        /* Thumbs */
        _______, ___X___, ___X___,   CU_DOT_DOT, CU_SPC_SPC, CU_ENT_ENT,

        /* Encoder buttons */
        ___X___, ___X___
    ),


/* EDIT
 
 ,-----------------------------------------.                        ,-----------------------------------------.
 |ScrR/L| PgUp | Home |  Up  |  End | ScrL |                        | AppR | Paste| Copy |  Cut |  All |AppWin|
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |WinR/L| PgDn | Left | Down | Right|TabR/L|                        |FulScr|      |      |      |      |Expose|
 |      |      |      |      |      |      |                        |      | Fast |  x4  | More |Delete|      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |AppR/L|      | Undo | Space| Redo |                                      |      |      |      |      | SNAP |
 |      | Shift|      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift|      |
 `----------------------------------'                                      `----------------------------------'
 .
 .              ,------.         ,--------------------.  ,--------------------.         ,------.
 .              |      |         | Enter| BkSp |  Del |  |      |      |      |         |      |
 .              |      |         |      |      |      |  |      |      | (**) |         |      |
 .              `------'         `--------------------'  `--------------------'         `------'
*/

    [EDIT] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_SCREEN_RL,        CE_PAGE_UP,    CE_HOME,  CE_UP,    CE_END,    SC_PREV_SCREEN,
        CU_NEXT_WINDOW,      CE_PAGE_DOWN,  CE_LEFT,  CE_DOWN,  CE_RIGHT,  CU_TAB_RIGHT,
        CU_APPSWITCH_RIGHT,  CU_SHIFT,      SC_UNDO,  KC_SPC,   SC_REDO,

        /* Right hand */
                     CU_APPSWITCH_RIGHT,  SC_PASTE,  SC_COPY,  SC_CUT,   SC_SELECT_ALL, SC_REVEAL_DESKTOP,
                     SC_FULLSCREEN,       CE_FAST,   CE_X4,    CE_MORE,  CE_DELETE,     SC_EXPOSE_ALL,
                                          KC_RGUI,   KC_RALT,  KC_RCTL,  CU_SHIFT,      CL_SNAP,
        /* Thumbs */
        CU_ENT_ENT, KC_BSPC, KC_DEL,   ___X___, ___X___, _______,

        /* Encoder buttons */
        ___X___, ___X___
    ),


/* META

 ,-----------------------------------------.                        ,-----------------------------------------.
 |DskTop|  Bin | Close|      | Find | BriU |                        | VolU |PrvTrk| Play |NxtTrk| Mute |SysSet|
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | eXit |Reload| Save |newTab|      | BriD |                        | VolD |  New |      | Open |saveAs| Quit |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      | Print| Prev | Next |                                      | Back |  Fwd |AppSet|      |      |
 | (**) | Shift|      |      |      |                                      |      |      |      | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .              ,------.         ,--------------------.  ,--------------------.         ,------.
 .              |      |         |      | Btn1 | Btn2 |  | Btn2 | Btn1 |      |         | Mute |
 .              |      |         | FUNC |      |      |  |      |      | SNAP |         |      |
 .              `------'         `--------------------'  `--------------------'         `------'
 */

    [META] = KEY_LAYOUT_stack(
        /* Left hand */
        SC_REVEAL_DESKTOP,  SC_BIN,      SC_CLOSE_TAB, ___X___,        SC_FIND,        SC_BRIGHTNESS_UP,
        SC_QUIT,            SC_RELOAD,   SC_SAVE,      SC_NEW_TAB,     ___X___,        SC_BRIGHTNESS_DOWN,
        _______,            CU_SHIFT,    SC_PRINT,     SC_PREV_SEARCH, SC_NEXT_SEARCH,

        /* Right hand */
                 KC_VOLU,  KC_MPRV,         KC_MPLY,        KC_MNXT,          KC_MUTE,     SC_SYS_SETTINGS,
                 KC_VOLD,  SC_NEW,          ___X___,        SC_OPEN,          SC_SAVE_AS,  SC_QUIT,
                           SC_BROWSER_BACK, SC_BROWSER_FWD, SC_APP_SETTINGS,  CU_SHIFT,    _______,

        /* Thumbs */
        CL_FUNC, CM_BTN1, CM_BTN2,   CM_BTN2, CM_BTN1, CL_SNAP,

        /* Encoder buttons */
        ___X___, KC_MUTE
    ),


/* FUNC

 ,-----------------------------------------.                        ,-----------------------------------------.
 |      |      |      |      |      |      |                        |LghtUp|  F5  |  F6  |  F7  |  F8  |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |!WRITE|      | !MAC | !WIN |!LINUX|      |                        |LghtDn|  F1  |  F2  |  F3  |  F4  |      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      |  F9  |  F10 |  F11 |  F12 |      |
 | (**) | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      | (**) |
 `----------------------------------'                                      `----------------------------------'

 .              ,------.         ,--------------------.  ,--------------------.         ,------.
 .              |      |         |      |      |      |  |      |      |      |         |      |
 .              |      |         | (**) |      |      |  |      |      |      |         |      |
 .              `------'         `--------------------'  `--------------------'         `------'
 */
    [FUNC] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___,   ___X___,  ___X___,   ___X___,     ___X___,   ___X___,
        CU_WRITE,  ___X___,  CU_MACOS,  CU_WINDOWS,  CU_LINUX,  ___X___,
        _______,   CU_SHIFT, KC_LCTL,   KC_LALT,     KC_LGUI,

        /* Right hand */
                 CU_LGHTUP,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   ___X___,
                 CU_LGHTDN,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   ___X___,
                             KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,

        /* Thumbs */
        _______, ___X___, ___X___,   ___X___, CM_BTN1, CM_BTN2,

        /* Encoder buttons */
        ___X___, ___X___
    ),


/* SNAP

 ,-----------------------------------------.                        ,-----------------------------------------.
 | SnapT| ZmIn | SL23 | SMax | SR23 | SPrev|                        |      |      |      |      |      |      |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | SnapB| ZmOut| SL12 | SM23 | SR12 | SVert|                        |      | SSRgn| SSWin| SSScr| SSApp|      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |  Zm0 | SL14 | SM12 | SR14 |                                      |      |      |      |      |      |
 | (**) |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .              ,------.         ,--------------------.  ,--------------------.         ,------.
 .              |  Zm0 |         |MvPrev|FulScr|MvNext|  |      | !WIPE|      |         |      |
 .              |      |         |      |      |      |  |      |      | (**) |         |      |
 .              `------'         `--------------------'  `--------------------'         `------'
*/

    [SNAP] = KEY_LAYOUT_stack(
        /* Left hand */
        SC_SNAP_TOP,    SC_APP_ZOOM_IN,    SC_SNAP_LEFTTWOTHIRDS, SC_SNAP_MAXIMIZE,     SC_SNAP_RIGHTTWOTHIRDS,  SC_SNAP_PREVIOUS,
        SC_SNAP_BOTTOM, SC_APP_ZOOM_OUT,   SC_SNAP_LEFT,          SC_SNAP_MIDTWOTHIRDS, SC_SNAP_RIGHT,           SC_SNAP_VERTICAL,
        _______,        SC_APP_ZOOM_RESET, SC_SNAP_LEFTQUARTER,   SC_SNAP_MIDDLE,       SC_SNAP_RIGHTQUARTER,

         /* Right hand */
                 ___X___, ___X___,         ___X___,         ___X___,            ___X___,         ___X___,
                 ___X___, CU_SCRSHOT_RGN,  CU_SCRSHOT_WIN,  SC_SCRSHOT_SCREEN,  SC_SCRSHOT_APP,  ___X___,
                          KC_RGUI,         KC_RALT,         KC_RCTL,            CU_SHIFT,        _______,

        /* Thumbs */
        SC_MOVETO_PREV_SCREEN, SC_FULLSCREEN, SC_MOVETO_NEXT_SCREEN,   ___X___, CU_WIPE, _______,

        /* Encoder button */
        SC_APP_ZOOM_RESET, ___X___
    ),

};
// clang-format on

