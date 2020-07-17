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

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;


void matrix_scan_encoder(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code16(SC(SC_AS_START));
            is_alt_tab_active = false;
        }
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    // If both encoder operate backwards, comment out this next line
    clockwise = !clockwise;

    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case QWERTY:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(SC(SC_REDO));
                } else {
                    tap_code16(SC(SC_UNDO));
                }
                break;
            default:
                // Switch between windows - Alt-tab on Windows, Cmd-tab on Mac.
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code16(SC(SC_AS_START));
                } 
                alt_tab_timer = timer_read();
                if (clockwise) {
                    tap_code16(SC(SC_AS_RIGHT));
                } else {
                    tap_code16(SC(SC_AS_LEFT));
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            default:
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}
