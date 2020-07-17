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

#include "keymap.h"

// Array of shortcut codes. First entry on each row is for macOS, second is for Windows.
//
const uint16_t PROGMEM shortcut_codes[][2] = {
  // App-switcher
  [SC_AS_START] = {KC_LGUI,   KC_LALT},
  [SC_AS_RIGHT] = {KC_TAB,    KC_TAB},
  [SC_AS_LEFT]  = {S(KC_TAB), S(KC_TAB)},

  // Copy-paste
  [SC_COPY]  = {G(KC_C), C(KC_C)},
  [SC_PASTE] = {G(KC_V), C(KC_V)},

  // Undo-redo
  [SC_UNDO]  = {G(KC_Z),    C(KC_Z)},
  [SC_REDO]  = {S(G(KC_Z)), C(KC_Y)}
};
