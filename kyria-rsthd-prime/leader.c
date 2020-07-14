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


LEADER_EXTERNS();

void matrix_scan_leader(void){


    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_TWO_KEYS(KC_T, KC_M) { // Trademark symbol
	  tap_code16(A(KC_2));
        }
        SEQ_TWO_KEYS(KC_M, KC_U) { // Mu
	  tap_code16(A(KC_M));
        }
        SEQ_TWO_KEYS(KC_P, KC_I) { // Pi
	  tap_code16(A(KC_P));
        }
	SEQ_TWO_KEYS(KC_C, KC_P) { // Copyright
	  tap_code16(A(KC_G));
        }
        SEQ_THREE_KEYS(KC_O, KC_H, KC_M) { // Ohm
	  tap_code16(A(KC_Z));
        }
        SEQ_THREE_KEYS(KC_D, KC_A, KC_G) { // Dagger
	  tap_code16(A(KC_T));
        }
        SEQ_THREE_KEYS(KC_R, KC_E, KC_G) { // Registered
	  tap_code16(A(KC_R));
        }
        SEQ_THREE_KEYS(KC_D, KC_E, KC_G) { // Degrees
	  tap_code16(S(A(KC_8)));
        }
        SEQ_THREE_KEYS(KC_D, KC_D, KC_G) { // Double dagger
	  tap_code16(S(A(KC_7)));
        }
    }
}
