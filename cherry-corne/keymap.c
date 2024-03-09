/*
 * Copyright 2020-2023 @frogm0uth

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap.h"


/**
 * Keymap
 * 
 * The Corne keymap is the same as the reference Kyria keymap except that a) the inner thumb
 * key is moved to the outer location (that is, the thumb home is now the innermost thumb keys)
 * and b) there is no encoder button.
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [ALPHA] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_ESC,   KC_V,     KC_C,  KC_W,  KC_F,  KC_K,
        KC_X,     KC_R,     KC_S,  KC_T,  KC_H,  KC_B,
        CL_META,  KC_LSFT,  KC_P,  KC_G,  KC_D,

        /* Right hand */
                  SC_SEARCH, KC_M,  KC_U,  CU_DOT,  KC_MINS, KC_Q,
                  KC_SCLN,   KC_N,  KC_I,  KC_O,    KC_A,    KC_ENT,
                             KC_L,  KC_Y,  CU_COMM, KC_RSFT, CL_META,

        /* Thumbs */
        KC_QUOT, CL_SYMS, KC_E,   KC_SPC, CL_EDIT, CU_SHIFT
    ),


    [SYMS] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___,  SC_SELECT_ALL,  SC_CUT,   SC_COPY,  SC_PASTE,  ___X___,
        KC_BSLS,  KC_PIPE,        KC_LPRN,  KC_ASTR,  KC_RPRN,   CU_TAB_TAB,
        ___X___,  KC_LSFT,        KC_LCTL,  KC_LALT,  KC_LGUI,

        /* Right hand */
                  CU_CIRC_GRAVE,  CU_7,  CU_8,  CU_9,  KC_PLUS,        ___X___,
                  CU_AMP_AT,      CU_1,  CU_2,  CU_3,  CU_0,           CU_TILDE_DOLLAR,
                                  CU_4,  CU_5,  CU_6,  CU_MINUS_MINUS, ___X___,

        /* Thumbs */
        ___X___, _______, KC_BSPC,   KC_SPC, KC_ENT, CU_DOT_DOT
    ),


    [EDIT] = KEY_LAYOUT_stack(
        /* Left hand */
        SC_FULLSCREEN,   CE_PAGE_UP,   CE_HOME,  CE_UP,    CE_END,    CU_PREV_WINDOW,
        CU_TAB_LEFT,     CE_PAGE_DOWN, CE_LEFT,  CE_DOWN,  CE_RIGHT,  CU_APPSWITCH_LEFT,
        SC_PREV_SCREEN,  _______,      SC_UNDO,  KC_ENT,   SC_REDO,


        /* Right hand */
                     CU_NEXT_WINDOW,     SC_PASTE,  SC_COPY,  SC_CUT,   SC_SELECT_ALL, SC_EXPOSE_ALL,
                     CU_APPSWITCH_RIGHT, CE_FAST,   CE_X4,    CE_MORE,  CE_DELETE,     CU_TAB_RIGHT,
                                         KC_RGUI,   KC_RALT,  KC_RCTL,  KC_RSFT,       SC_NEXT_SCREEN,

        /* Thumbs */
        KC_DEL, KC_ENT, KC_BSPC,   KC_BSPC, _______, ___X___
    ),


    [META] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_SLCK, ___X___,     SC_CLOSE_TAB, ___X___,        SC_FIND,        ___X___,
        SC_QUIT, SC_RELOAD,   SC_SAVE,      SC_NEW_TAB,     ___X___,        SC_BIN,
        _______, _______,     SC_PRINT,     SC_PREV_SEARCH, SC_NEXT_SEARCH,

        /* Right hand */
                 KC_VOLU,  KC_MPRV,         KC_MPLY,        KC_MNXT,  KC_MUTE,     CU_SLCK,
                 KC_VOLD,  SC_NEW,          ___X___,        SC_OPEN,  SC_SAVE_AS,  SC_QUIT,
                           SC_BROWSER_BACK, SC_BROWSER_FWD, ___X___,  _______,     _______,

        /* Thumbs */
        CU_NEXT_WINDOW, CL_FUNC, CU_APPSWITCH_RIGHT,   CU_APPSWITCH_RIGHT, CL_SNAP, CU_NEXT_WINDOW
    ),


    [FUNC] = KEY_LAYOUT_stack(
        /* Left hand */
        ___X___, ___X___, ___X___,         ___X___,           ___X___,         ___X___,
        ___X___, ___X___, CU_SELECT_MACOS, CU_SELECT_WINDOWS, CU_SELECT_LINUX, ___X___,
        _______, KC_LSFT, KC_LCTL,         KC_LALT,           KC_LGUI,

        /* Right hand */
                 SC_BRIGHTNESS_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  ___X___,
                 SC_BRIGHTNESS_DOWN, KC_F1,   KC_F2,   KC_F3,   KC_F11,  ___X___,
                                     KC_F4,   KC_F5,   KC_F6,   KC_F12,  _______,

        /* Thumbs */
        ___X___, _______, ___X___,   ___X___, ___X___, ___X___
    ),


    [SNAP] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_KBUP, SC_APP_ZOOM_IN,    SC_SNAP_LEFTTWOTHIRDS, SC_SNAP_TOP,          SC_SNAP_RIGHTTWOTHIRDS,  ___X___,
        CU_KBDN, SC_APP_ZOOM_OUT,   SC_SNAP_LEFT,          SC_SNAP_MIDTWOTHIRDS, SC_SNAP_RIGHT,           ___X___,
        _______, SC_APP_ZOOM_RESET, SC_SNAP_LEFTQUARTER,   SC_SNAP_BOTTOM,       SC_SNAP_RIGHTQUARTER,

         /* Right hand */
                 ___X___, ___X___,         ___X___,         ___X___,              ___X___,           ___X___,
                 ___X___, CU_SCRSHOT_RGN,  CU_SCRSHOT_WIN,  SC_SCREENSHOT_SCREEN, SC_SCREENSHOT_APP, CU_WRITE,
                          KC_RGUI,         KC_RALT,         KC_RCTL,              KC_RSFT,           _______,

        /* Thumbs */
        ___X___, ___X___, ___X___,   CU_WIPE, _______, ___X___
    )

};
// clang-format on


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif
  return process_record_user_common(keycode, record);
}

