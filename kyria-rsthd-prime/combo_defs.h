
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

/**
 * This file contains the definitions of combos. This includes both QMK combos
 * and user-space comborolls. Comborolls are triggered by a sequence of
 * keypresses instead of pressing both keys at the same time as with combos.
 *
 * QMK combos support any number of trigger keys. Comborolls support only two
 * keys. Comborolls cannot use mod-taps, either as trigger or output. Comborolls
 * allow modifiers as trigger keys but not as output.
 *
 * The macros are named (CMBO|LtoR|RtoL|LRRL )_(KEY|ARR|LIT|STR ). To
 * use the CMBO_* macros, set COMBO_ENABLE=yes on rule.mk. To use the
 * other (comboroll) macros, set COMBOROLL_ENABLE=yes in rules.mk.
 *
 * CMBO: generates normal QMK combo
 * LtoR: comboroll, triggers pressed from left to right
 * RtoL: comboroll, triggers pressed from right to left
 * LRRL: comboroll, triggers pressed in either direction
 *
 * KEY: arguments are name, keycode, triggers
 * ARR: arguments are name, array of keycodes, triggers
 * LIT: arguments are name, literal string, triggers
 * STR: arguments are name, triggers. The combo output is the name.
 *
 * Note: by convention, the trigger keys should be listed from left to right
 * location in the keymap (where it makes sense to do so ).
 */
// clang-format off

// Anti-SFU, mostly vertical combos
LRRL_STR( sc, KC_S, KC_C )
LRRL_STR( ps, KC_S, KC_P )
LtoR_STR( sp, KC_P, KC_G )
LRRL_STR( tw, KC_T, KC_W )  
LRRL_STR( ui, KC_U, KC_I )

// Anti-pinballing
RtoL_STR( er,  KC_O,    KC_A )
RtoL_STR( es,  KC_O,    CU_RSFT )
RtoL_STR( ed,  CU_COMM, CU_RSFT )

// Awkward bigrams/trigrams
LtoR_STR( qu,  KC_C, KC_W )
LtoR_STR( cr,  KC_W, KC_F )
LtoR_STR( pr,  KC_G, KC_D )
RtoL_STR( my,  KC_M, CU_DOT )
LtoR_STR( min, KC_P, KC_N )

// Inner column minimization
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( ble, KC_T, KC_D )
LRRL_STR( be,  KC_P, CU_COMM )
LRRL_STR( but, KC_G, CU_COMM )
LRRL_STR( by,  KC_D, CU_COMM )

// Alternate punctuation on left hand
LtoR_KEY( comma,  KC_COMM, CU_LSFT, KC_P )
LtoR_KEY( period, KC_DOT,  CU_LSFT, KC_G )

LtoR_KEY( caps, KC_X,  CU_LSFT, KC_D )

// Common word endings, right hand
RtoL_STR( ould, CU_DOT, KC_MINS )
LRRL_STR( ough, KC_U,   KC_MINS )

LRRL_STR( ing,  KC_I, CU_COMM )
LRRL_STR( ight, KC_I, CU_DOT )

RtoL_STR( ally, KC_L, CU_RSFT )
LRRL_STR( ess,  KC_Y, CU_RSFT )

// Common words
RtoL_STR( you,  KC_U, CU_DOT )

LRRL_STR( very, KC_V, KC_Y )
LRRL_STR( ever, KC_E, CU_COMM )

LRRL_STR( was,  KC_W, KC_Y )
LRRL_STR( his,  KC_H, KC_Y )

// Utilities
LRRL_KEY( search,   SC_SEARCH,      KC_SPC,  KC_ENT )       // System search box, right thumb
LRRL_KEY( capslock, KC_CAPS,        KC_E,    CL_SYMS )      // Capslock, left thumb
LtoR_ARR( esc_x,                                            // Escape-X for emacs
        ARRAY_PROTECT( 
            KC_ESC,
            KC_X
     ),
    KC_V, KC_C )

// Syntax layer
RtoL_LIT( openphp,        "<?php", KC_RBRC, KC_QUES )
RtoL_LIT( closeparensemi, ");",    KC_QUES, KC_LBRC )
RtoL_LIT( dirup,          "../",   KC_LBRC, CU_MNCM )

// Window snapping
LRRL_KEY( snaptop,    SC_SNAP_TOP,    SC_SNAP_TOPLEFT,    SC_SNAP_TOPRIGHT )       // Top two quadrants = snap top
LRRL_KEY( snapbottom, SC_SNAP_BOTTOM, SC_SNAP_BOTTOMLEFT, SC_SNAP_BOTTOMRIGHT )    // Bottom two quadrants = snap bottom
