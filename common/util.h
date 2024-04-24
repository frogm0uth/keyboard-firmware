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

void kb_lighting_adjust(bool up, uint8_t mods);
void emit_progmem_array(const uint16_t *keyptr);
void emit_progmem_array_record(const uint16_t *keyptr, keyrecord_t *record);
void emit_progmem_string(const char *str);
void emit_progmem_string_autounshift(const char *str);

void process_os_change(uint16_t keycode);
void write_lighting_to_eeprom(void);

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
