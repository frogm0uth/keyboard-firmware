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
#pragma once
#include QMK_KEYBOARD_H

/*
 * Timeout for comborolls and directional QMK combos 
 */
#ifndef COMBOROLL_TIMEOUT
#    define COMBOROLL_TIMEOUT 150
#endif


#ifdef COMBOROLL_ENABLE
// Types of comboroll output
enum compose_type {
    comboroll_t_keycode = 0,
    comboroll_t_array,
    comboroll_t_string
};

// The structure to represent a comboroll
typedef struct comboroll_node {
    uint8_t  type;
    uint16_t firstkey;
    uint16_t secondkey;
    union {
        uint16_t         output_keycode;
        const uint16_t*  output_array;
        char*            output_string;
    };
} comboroll_t;


/**
 * Extern functions
 */
bool process_record_comboroll(uint16_t keycode, keyrecord_t* record);
void comboroll_tick(void);

#endif // COMBOROLL_ENABLE
