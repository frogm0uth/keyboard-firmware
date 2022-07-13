
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
 * This file contains the definitions of combos. This works with either QMK combos or my userspace
 * comboroll implementation. QMK combos are more powerful eg. can be almost any key as trigger or
 * output.  However it takes more space (about 2k in this keymap).
 *
 * Another reason for this code is that, in QMK, overlapping comboes emit the *latest* one whereas I
 * prefer the *earliest* one. In other words, as soon as a combo is detected, I want the output keys
 * to be emitted, rather than waiting to see if there's an overlap. As a workaround, you can define
 * COMBO_MUST_TAP_PER_COMBO in config.h to force all combos to be taps, in which case they don't
 * wait for an overlap. However this also means you cannot linger on the keys (otherwise there is no
 * output at all), and hold-keys cannot be used as output.
 *
 * QMK combos support any number of trigger keys. Comborolls support only two keys. Comborolls
 * cannot use mod-taps, either as trigger or output. Comborolls allow modifiers as trigger keys but
 * not as output.
 *
 * The definition macros are named (LtoR|RtoL|CMBO)_(KEY|ARR|LIT|STR ). LtoR and RtoL require the
 * keys be pressed in the stated direction, while CMBO allows either direction. By default, RtoL and
 * LtoR have a longer timeout, on the assumption they will be typed rapidly as a "roll" instead of
 * deliberately both pressed at the same time.
 *
 * LtoR: comboroll, triggers pressed from left to right
 * RtoL: comboroll, triggers pressed from right to left
 * CMBO: either direction OK
 *
 * KEY: arguments are name, keycode, triggers
 * ARR: arguments are name, array of keycodes, triggers
 * LIT: arguments are name, literal string, triggers
 * STR: arguments are name, triggers. The name is output as a string.
 *
 * To define a custom term for a combo, use the _____TRM(name,ms) macro. It must be *after* the
 * macro that defines that combo (for QMK combos, for userspace comborolls it doesn't matter).
 * 
 * Notes:
 * 
 * 1. By convention, the trigger keys should be listed from left to right location in the keymap
 * (where it makes sense to do so ).
 *
 * 2. The RtoL version works only for two trigger keys.
 *
 * 3. If COMBOROLL_ENABLED is defined, none of the macros work with more than two trigger keys. For
 * defs with > 2 trigger keys, wrap them in a #ifdef COMBO_ENABLED.
 *
 * 4. If COMBOROLL_ENABLED is defined, using layer switch keys doesn't work properly: as a source,
 * the layer doesn't activate with a quick roll. As an output, it just doesn't work.
 */
// clang-format off

// Anti-SFU - rolls
LtoR_STR( sc, KC_C, KC_W )
LtoR_STR( sp, KC_P, KC_G )

// Anti-SFU - vertical
CMBO_STR( ps, KC_C, KC_S )
CMBO_STR( tw, KC_T, KC_W )  
CMBO_STR( lm, KC_M, KC_N )
CMBO_STR( ui, KC_U, KC_I )

// Anti-pinballing
RtoL_STR( er, KC_O, KC_A )
RtoL_STR( ed, KC_L, KC_Y )
RtoL_STR( es, KC_L, CU_COMM )
RtoL_STR( ve, KC_I, CU_COMM )

// Awkward bigrams/trigrams
LtoR_STR( qu,  KC_V, KC_F )
LtoR_STR( cr,  KC_W, KC_F )
_____TRM( cr,  200 )
LtoR_STR( pr,  KC_G, KC_D )
_____TRM( pr,  200 )
LtoR_STR( ght, KC_S, KC_D )

RtoL_STR( my,  KC_M, KC_MINS )
RtoL_STR( you, KC_U, CU_DOT )

CMBO_STR( min, KC_H, CU_DOT )
CMBO_STR( ex,  KC_H, CU_COMM )

// Inner column minimization
LtoR_STR( ck,  KC_C, KC_F )
LtoR_STR( rk,  KC_R, KC_W )
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( bl,  KC_T, KC_D )

CMBO_STR( be,  KC_R, CU_COMM )
CMBO_STR( by,  KC_S, CU_COMM )
CMBO_STR( ke,  KC_T, CU_COMM )

// More typing comfort
LtoR_STR( fr,   KC_S, KC_F )
LtoR_STR( ft,   KC_T, KC_F )
LtoR_STR( ful,  KC_S, KC_G )

CMBO_STR( for,  KC_R, CU_DOT ) 

// Common word endings, right hand
RtoL_STR( ally, KC_M, CU_DOT )
RtoL_STR( ould, KC_I, CU_DOT )
RtoL_STR( ough, KC_N, CU_COMM )
RtoL_STR( ess,  KC_Y, CU_COMM )

// Alternate punctuation on left hand
RtoL_KEY( comma,  KC_COMM, KC_P, KC_G )
_____TRM( comma,  200 )
RtoL_KEY( period, KC_DOT,  KC_C, KC_W )
_____TRM( period, 200 )

#ifdef NOTWORKINGYET
RtoL_LIT( commaspace, ", ", KC_P, KC_D )
_____TRM( commaspace,  200 )

RtoL_ARR( periodspaceOSS,   // precondition's next sentence macro
	ARRAY_PROTECT( 
            KC_DOT,
            KC_SPC,
            OSM(MOD_LSFT)
     ),
    KC_C, KC_F )

_____TRM( periodspaceOSS, 200 )
#endif

// More words
CMBO_STR( abo,  KC_T, CU_DOT )
CMBO_STR( but,  KC_S, CU_DOT )
CMBO_STR( qmk,  KC_C, CU_DOT )

// Trialing/temporary
RtoL_STR( io,  CU_DOT, KC_MINS )
RtoL_STR( any, KC_U, KC_MINS )
RtoL_STR( et,  KC_N, KC_Y )


// Utilities
CMBO_KEY( search,   SC_SEARCH,      KC_SPC,  KC_ENT )       // System search box, right thumb
CMBO_ARR( esc_x,                                            // Escape-X for emacs
        ARRAY_PROTECT( 
            KC_ESC,
            KC_X
     ),
    KC_V, KC_C )

// Utilities that work only for QMK combos
#if defined COMBO_ENABLE && !defined COMBO_MUST_TAP_PER_COMBO
CMBO_KEY( shiftcaps, SFT_T(KC_CAPS), KC_E,    CL_SYMS )      // Thumb shift on hold, caps lock on tap
CMBO_KEY( funclayer, CL_FUNC,        CU_LCMD, CL_SNAP )      // Activate FUNC layer from thumb
#endif

// Syntax layer
RtoL_LIT( openphp,        "<?php", KC_RBRC, KC_QUES )
RtoL_LIT( closeparensemi, ");",    KC_QUES, KC_LBRC )
RtoL_LIT( dirup,          "../",   CU_DTDT, CU_2 )
