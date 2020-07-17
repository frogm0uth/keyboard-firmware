/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#include "platform.h"
#include "keymap.h"


uint16_t copy_paste_timer;
user_config_t user_config;
uint8_t os_selection;

// Initialize from EEPROM 
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  os_selection = user_config.os_selection;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSFT   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   Z  |   X  |   C  |   V  |   B  | CCCV |      |  | Del  |Leader|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+      |  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |      | Space| Enter|  | Bspc | Space|      | Tab  | AltGr|
 *                        |      |      | Lower| Shift| Alt  |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      KC_LSFT, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_CCCV,   KC_CCCV, KC_DEL, KC_LEAD,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_LALT, MO(LOWER), MT(MOD_LSFT, KC_SPC), MT(MOD_LALT, KC_ENT), KC_BSPC, LT(NAV, KC_SPC), MO(RAISE), KC_TAB, KC_RALT
    ),
/* 
 * Second Base Layer: Colemak-DHM
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSFT   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   Z  |   X  |   C  |   D  |   V  | CCCV |      |  | Del  |Leader|   K  |   H  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+      |  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |      | Space| Enter|  | Bspc | Space|      | Tab  | AltGr|
 *                        |      |      | Lower| Shift| Alt  |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [COLEDHM] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_PIPE,
      KC_LSFT, KC_A,   KC_R,   KC_S,   KC_T,   KC_G,                                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
      KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,   KC_CCCV,   XXXXXXX, KC_DEL, KC_LEAD,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_LALT, MO(LOWER), MT(MOD_LSFT, KC_SPC), MT(MOD_LALT, KC_ENT), KC_BSPC, LT(NAV, KC_SPC), MO(RAISE), KC_TAB, KC_RALT
    ),
/* 
 * Third Base Layer: Workman
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   F  |   U  |   P  | ;  : |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSFT   |   A  |   S  |   H  |   T  |   G  |                              |   Y  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   Z  |   X  |   M  |   C  |   V  | CCCV |      |  | Del  |Leader|   K  |   L  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+      |  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |      | Space| Enter|  | Bspc | Space|      | Tab  | AltGr|
 *                        |      |      | Lower| Shift| Alt  |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [WORKMAN] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                                         KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_PIPE,
      KC_LSFT, KC_A,   KC_S,   KC_H,   KC_T,   KC_G,                                         KC_Y,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
      KC_LCTL, KC_Z,   KC_X,   KC_M,   KC_C,   KC_V,   KC_CCCV,   XXXXXXX, KC_DEL, KC_LEAD,  KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_LALT, MO(LOWER), MT(MOD_LSFT, KC_SPC), MT(MOD_LALT, KC_ENT), KC_BSPC, LT(NAV, KC_SPC), MO(RAISE), KC_TAB, KC_RALT
    ),
/* 
 * Fourth Base Layer: RSTHD
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   J  |   C  |   Y  |   F  |   K  |                              |   Z  |   L  | ,  < |   U  |   Q  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSFT   |   R  |   S  |   T  |   H  |   D  |                              |   M  |   N  |   A  |   I  |   O  |  RSFT  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   /  |   V  |   G  |   P  |   B  | CCCV |      |  | Del  |Leader|   X  |   W  | .  > | ;  : | -  _ |  '  "  |
 * `----------------------+------+------+------+------+      |  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |      |   E  | Enter|  | Bspc | Space|      | Tab  | AltGr|
 *                        |      |      | Lower|      | Alt  |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [RSTHD] = LAYOUT(
      KC_ESC,  KC_J,    KC_C,   KC_Y,   KC_F,   KC_K,                                         KC_Z,    KC_L,    KC_COMM, KC_U,    KC_Q,    KC_PIPE,
      KC_LSFT, KC_R,    KC_S,   KC_T,   KC_H,   KC_D,                                         KC_M,    KC_N,    KC_A,    KC_I,    KC_O,    KC_RSFT,
      KC_LCTL, KC_SLSH, KC_V,   KC_G,   KC_P,   KC_B,   KC_CCCV,   XXXXXXX, KC_DEL, KC_LEAD,  KC_X,    KC_W,    KC_DOT,  KC_SCLN, KC_MINS, KC_QUOT,
              KC_LGUI,  KC_LALT, MO(LOWER),     KC_E,   MT(MOD_LALT, KC_ENT), KC_BSPC, LT(NAV, KC_SPC), MO(RAISE), KC_TAB, KC_RALT
    ),
/*
 * Lower Layer: Numpad, Media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | VolUp|      |      |                              | / ?  | 7 &  | 8 *  | 9 (  | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next |      |                              | *    | 4 $  | 5 %  | 6 ^  | , <  | +      |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      | VolDn| Mute |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | = +  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [LOWER] = LAYOUT(
      _______, _______, _______, KC_VOLU, _______, _______,                                     KC_SLSH, KC_7,    KC_8,    KC_9, KC_MINS, _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,                                     KC_ASTR, KC_4,    KC_5,    KC_6, KC_COMM, KC_PLUS,
      _______, _______, _______, KC_VOLD, KC_MUTE, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3, KC_EQL,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |  _   |  €   |      |      |  \     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [RAISE] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, KC_UNDS, ALGR(KC_5),_______,_______,KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |  MAC |  WIN |      |                              | PgUp | Home | Up   | End  |      | ScrlLk |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |QWERTY|COLDHM|WRKMAN| RSTHD|      |                              | PgDn | Left | Down | Right|      | CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | Lower|      |      |  |      | Nav  | Raise|      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [NAV] = LAYOUT(
      _______, _______, _______, KC_MAC,  KC_WIN,  _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, KC_SLCK,
      _______, KC_QWERTY, KC_COLEDHM, KC_WORKMAN, KC_RSTHD, _______,                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_CAPS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      | F7   | F8   | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | SAI  | HUI  | VAI  |      |                              |      | F4   | F5   | F6   | F11  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  |      |      |      |  |      |      |      | F1   | F2   | F3   | F12  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, RGB_SAI, RGB_HUI, RGB_VAI, _______,                                     _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
		  tap_code16(SC(SC_COPY));
                } else { // Tap, paste
		  tap_code16(SC(SC_PASTE));
                }
            }
            break;

	// Switch the default base layer
	case KC_QWERTY:
	    set_single_persistent_default_layer(QWERTY);
	    layer_clear();
	    return false;
	    break;

	case KC_COLEDHM:
	    set_single_persistent_default_layer(COLEDHM);
	    layer_clear();
	    return false;
	    break;

	case KC_WORKMAN:
	    set_single_persistent_default_layer(WORKMAN);
	    layer_clear();
	    return false;
	    break;

	case KC_RSTHD:
	    set_single_persistent_default_layer(RSTHD);
	    layer_clear();
	    return false;
	    break;

	    // Change OS selection
    case KC_MAC:
    case KC_WIN:
      if (record->event.pressed) {
	os_selection = keycode == KC_MAC ? OS_SELECTION_MACOS : OS_SELECTION_WINDOWS;
	user_config.os_selection = os_selection;
	eeconfig_update_user(user_config.raw);
      }
      break;


    }
    return true;
}


void matrix_scan_user(void) {
#ifdef ENCODER_ENABLE    
    matrix_scan_encoder();
#endif
    
#ifdef LEADER_ENABLE    
    matrix_scan_leader();
#endif    
}
