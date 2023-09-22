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

void oled_print_hex(uint8_t n);
void kb_adjust(bool up, uint8_t mods);


/**
 * User config structure
 */
typedef union {
    uint32_t raw;
    struct {
        uint8_t os_selection : 2;
        uint8_t oled_brightness : 8;
    };
} user_config_t;

extern user_config_t user_config;
