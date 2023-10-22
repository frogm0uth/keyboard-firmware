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

bool is_capsword_active(void);
bool process_auto_unshift(uint16_t keycode, keyrecord_t *record);
void process_caps_cancel(uint16_t keycode, keyrecord_t *record);
bool process_record_capslock(uint16_t keycode, keyrecord_t *record);
void toggle_capsword(void);
void toggle_capslock(void);
void capsword_tick(void);
bool check_auto_unshift(void);
