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
#pragma once

#include QMK_KEYBOARD_H

/**
 * Support for the (pre) repeat key.
 *
 * usage pattern:

do {
    tap_code16(keycode);
} while (repeat_that_output());

 */

bool process_record_repeatkey(uint16_t keycode, keyrecord_t *record);
void set_repeat_count(uint16_t);
bool repeat_that_output(void);
uint16_t capture_repeat_count(void);
