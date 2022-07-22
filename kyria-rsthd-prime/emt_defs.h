
/* Copyright 2022 @frogm0uth
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

/**
 * This file contains the definitions of the "bolt on" eager mod-taps. Instead
 * of defining them in the keymap, add them to the list here. This
 * works with 16-bit keycodes.
 *
 * DEFINE_EMT ( layer, tapcode, holdcode )
 */
// clang-format off


/* Uncomment to put only shifts in the EMTs. This is less scary when testing
 * it out.
 */
//#define EMT_TESTING

#ifdef EMT_TESTING

DEFINE_EMT( ALPHA, KC_R, KC_LSFT )
DEFINE_EMT( ALPHA, KC_S, KC_LSFT )
DEFINE_EMT( ALPHA, KC_T, KC_LSFT )
DEFINE_EMT( ALPHA, KC_H, KC_LSFT )

DEFINE_EMT( ALPHA, KC_N, KC_RSFT )
DEFINE_EMT( ALPHA, KC_I, KC_RSFT )
DEFINE_EMT( ALPHA, KC_O, KC_RSFT )
DEFINE_EMT( ALPHA, KC_A, KC_RSFT )

#else

DEFINE_EMT( ALPHA, KC_R, KC_LGUI )
DEFINE_EMT( ALPHA, KC_S, KC_LALT )
DEFINE_EMT( ALPHA, KC_T, KC_LSFT )
DEFINE_EMT( ALPHA, KC_H, KC_LCTL )

DEFINE_EMT( ALPHA, KC_N, KC_RCTL )
DEFINE_EMT( ALPHA, KC_I, KC_RSFT )
DEFINE_EMT( ALPHA, KC_O, KC_RALT )
DEFINE_EMT( ALPHA, KC_A, KC_RGUI )

#endif