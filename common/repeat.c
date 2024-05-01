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
 * Support for the (pre) repeat key.
 *
 * usage pattern:

do {
    tap_code16(keycode);
} while (repeat_that_output());

 */

static uint16_t repeat_count=0;

void set_repeat_count(uint16_t count) {
    if (count > 0) {
        repeat_count = count;
    }
}

bool repeat_that_output() {
    if (repeat_count > 0) {
        repeat_count--;
        return true;
    } else {
        return false;
    }
}
bool is_repeat_active() {
    return repeat_count > 0;
}

/**
 * Enable the repeat.
 */
bool process_record_repeatkey(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case CU_REPT:
            if (record->event.pressed) {
                cancel_comboroll();   // cancel any existing comboroll so first letter is output
                set_repeat_count(1);  // THEN enable the repeat for the next letter
            }
            return false;
            break;
        default:
            return true;
            break;
    }
}

