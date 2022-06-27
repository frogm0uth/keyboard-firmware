
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
 * This file contains the definitions of combos. This works with either QMK combos
 * or user-space comborolls. Comborolls are triggered by a sequence of
 * keypresses instead of pressing both keys at the same time as with combos.
 *
 * QMK combos support any number of trigger keys. Comborolls support only two
 * keys. Comborolls cannot use mod-taps, either as trigger or output. Comborolls
 * allow modifiers as trigger keys but not as output.
 *
 * The macros are named (LtoR|RtoL|CMBO)_(KEY|ARR|LIT|STR ). LtoR and RtoL require
 * the keys be pressed in the stated direction. CMBO requires they both be pressed
 * at the same time (QMK combos) or that either direction works (comborolls).
 *
 * LtoR: comboroll, triggers pressed from left to right
 * RtoL: comboroll, triggers pressed from right to left
 * CMBO: both pressed at same time OR either direction OK
 *
 * KEY: arguments are name, keycode, triggers
 * ARR: arguments are name, array of keycodes, triggers
 * LIT: arguments are name, literal string, triggers
 * STR: arguments are name, triggers. The combo output is the name.
 *
 * Notes:
 * 
 * 1. By convention, the trigger keys should be listed from left to right
 * location in the keymap (where it makes sense to do so ).
 *
 * 2. The RtoL version works only for two trigger keys.
 *
 * 3. None of the macros above work with more than two trigger keys if COMBOROLL_ENABLED
 * is defined. So if you want > 2 trigger keys, wrap them in a #ifdef COMBO_ENABLED. 
 *
 * 4. Currently, using layer switch keys doesn't work properly: as a source, the layer
 * doesn't activate with a quick roll. As an output, it doesn't work. Needs more work.
 */
// clang-format off

// Anti-SFU, mostly vertical combos
CMBO_STR( sc, KC_S, KC_C )
CMBO_STR( ps, KC_S, KC_P )
LtoR_STR( sp, KC_P, KC_G )
CMBO_STR( tw, KC_T, KC_W )  
CMBO_STR( ui, KC_U, KC_I )

// Anti-pinballing
CMBO_STR( er,  KC_O,    KC_A )
RtoL_STR( es,  KC_O,    CU_RSFT )
CMBO_STR( ed,  CU_COMM, CU_RSFT )

// Awkward bigrams/trigrams
LtoR_STR( qu,  KC_C, KC_W )
LtoR_STR( cr,  KC_W, KC_F )
LtoR_STR( pr,  KC_G, KC_D )
RtoL_STR( my,  KC_M, CU_DOT )
CMBO_STR( min, KC_P, KC_N )

// Inner column minimization
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( ble, KC_T, KC_D )
CMBO_STR( be,  KC_P, CU_COMM )
CMBO_STR( but, KC_G, CU_COMM )
CMBO_STR( by,  KC_D, CU_COMM )

// Alternate punctuation on left hand
CMBO_KEY( comma,  KC_COMM, CU_LSFT, KC_P )
CMBO_KEY( period, KC_DOT,  CU_LSFT, KC_G )

// Common word endings, right hand
RtoL_STR( ould, CU_DOT, KC_MINS )
CMBO_STR( ough, KC_U,   KC_MINS )

CMBO_STR( ing,  KC_I, CU_COMM )
CMBO_STR( ight, KC_I, CU_DOT )

RtoL_STR( ally, KC_L, CU_RSFT )
CMBO_STR( ess,  KC_Y, CU_RSFT )

// Common words
RtoL_STR( you,  KC_U, CU_DOT )
CMBO_STR( very, KC_V, KC_Y )
CMBO_STR( ever, KC_E, CU_COMM )

// Utilities
CMBO_KEY( search,   SC_SEARCH,      KC_SPC,  KC_ENT )       // System search box, right thumb
LtoR_ARR( esc_x,                                            // Escape-X for emacs
        ARRAY_PROTECT( 
            KC_ESC,
            KC_X
     ),
    KC_V, KC_C )

// Utilities that work only for QMK combos
#ifdef COMBO_ENABLE
CMBO_KEY( shiftcaps, SFT_T(KC_CAPS), KC_E,   CL_SYMS )       // Thumb shift on hold, caps lock on tap
CMBO_KEY( funclayer, CL_FUNC,        CU_LCMD, CL_SNAP )      // Activate FUNC layer from thumb
#endif

// Syntax layer
RtoL_LIT( openphp,        "<?php", KC_RBRC, KC_QUES )
RtoL_LIT( closeparensemi, ");",    KC_QUES, KC_LBRC )
RtoL_LIT( dirup,          "../",   CU_DTDT, CU_2 )
