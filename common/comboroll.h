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

/*
 * Definitions for comborolls
 */

#ifdef COMBOROLL_ENABLE
// Types of comboroll output
enum comboroll_type {
    comboroll_t_keycode = 0,
    comboroll_t_array,
    comboroll_t_literal,
    comboroll_t_string
};

// The structure to represent a comboroll. direction is a bitfield: lsb set if order is key1,key2,
// msb set if order is key2,key1, both set if either order can match.
typedef struct comboroll_node {
    uint8_t  type:2;
    uint8_t  direction:2;
    uint8_t  onshift:1;
    uint16_t term:11;
    //uint16_t key1; // key1 and key2 are stored in a separate array to reduce RAM usage
    //uint16_t key2;
    union {
        uint16_t         output_keycode;
        const uint16_t*  output_array;
        const char*      output_string;
    };
} comboroll_t;

#define CMB_MATCH_LEFT  (0x01)
#define CMB_MATCH_RIGHT (0x02)
#define CMB_MATCH_BOTH  (CMB_MATCH_LEFT | CMB_MATCH_RIGHT)

#define CMB_IS_MATCHES_LEFT(dir)  (dir & 0x01)
#define CMB_IS_MATCHES_RIGHT(dir) (dir & 0x02)

/**
 * Extern functions
 */
void comboroll_post_init(void);
bool process_record_comboroll(uint16_t keycode, keyrecord_t* record);
void comboroll_tick(void);
void cancel_comboroll(void);

#endif // COMBOROLL_ENABLE
