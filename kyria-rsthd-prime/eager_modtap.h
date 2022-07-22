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

/* Uncomment to disable rule 2. Rule 2 is the transition from waiting
 * to tapping mode when a non-EMT key is pressed. By disabling it, a
 * mod-tap key can potentially be a modifier even if pressed
 * immediately after any other key.
 */
#define EMT_DISABLE_RULE_2

/*
 * Definitions for eager mod-taps
 */
//#define EMT_LATE_TERM 1000

#ifndef EMT_EARLY_TERM
#    define EMT_EARLY_TERM COMBO_TERM
#endif

#ifndef EMT_LATE_TERM
#    define EMT_LATE_TERM TAPPING_TERM
#endif

// The structure to represent an EMT
// FIXME move to PROGMEM
typedef struct emt_node {
    bool     is_held : 1; // true if it's held i.e. the modifier has been registered
    uint8_t  layer : 4;   // the layer in which to activate this mod-tap
    uint16_t tapcode;     // the tap code
    uint16_t holdcode;    // the hold code aka modifier keycode
} emtnode_t;

/**
 * Extern functions
 */
bool process_record_emt(uint16_t keycode, keyrecord_t* record);
void emt_tick(void);
