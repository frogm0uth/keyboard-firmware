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


/* Support for the (pre) repeat key.
 *
 * The repeat is active for REPEATKEY_TIMEOUT (default 500ms) after the initial press,
 * or until the key is released, whichever comes last.
 * There are two usage patterns. For pure tapping:

    do {
        tap_code16(keycode);
    } while (repeat_that_output());
 *
 * and if wanting the keycode to remain registered:
 *
    while (repeat_that_output() {
        tap_code16(keycode);
    }
    register_code16(keycode);
 */


static uint16_t repeat_count=0;
static bool     repeatkey_waiting = false;
static bool     repeatkey_down = false;
static uint16_t repeatkey_timer = 0;


// Capture the current counter. This is used for higher-level repeats e.g. a sequence
// of keycodes. The repeat count is set to zero so it doesn't cause repeats at
// lower levels.
//
uint16_t capture_repeat_count() {
    uint16_t rc = repeat_count;
    repeat_count = 0;
    return rc;
}

// Set the repeat count.
//
void set_repeat_count(uint16_t count) {
    if (count > 0) {
        repeat_count = count;
    }
}

// Test if repeat is active
//
bool is_repeat_active() {
    return (repeat_count > 0);
}

// Check if the output should be repeated. See the examples at the top of the file.
//
bool repeat_that_output() {
    if (repeat_count > 0) {
        repeat_count--;
        return true;
    } else {
        return false;
    }
}

// Process the repeat key.
//
bool process_record_repeatkey(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case CU_REPT:
            if (record->event.pressed) {
#ifdef COMBOROLL_ENABLE
                cancel_comboroll(false);   // if waiting for a comboroll, cancel it and register the held letter
#endif
                set_repeat_count(1);       // THEN enable the repeat for the next letter
                repeatkey_timer = timer_read(); // Start the timer to turn off the repeat
                repeatkey_waiting = true;
                repeatkey_down = true;
            } else {
                repeatkey_down = false;
                if (!repeatkey_waiting) {
                    repeat_count = 0;
                }
            }
            return false;
            break;
        default:
            return true;
            break;
    }
}

// Time out the repeat key
//
void repeatkey_tick() {
    if (repeatkey_waiting) {
        if (timer_elapsed(repeatkey_timer) > REPEATKEY_TIMEOUT) {
            repeatkey_waiting = false;
            if (!repeatkey_down) {
                repeat_count = 0;
            }
        }
    }
}

