
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

/**
 * This file contains the definitions of combos and comborolls. This works with QMK combos and/or my userspace
 * comboroll implementation. In rules.mk, turn on COMBO_ENABLE for QMK combos and COMBOROLL_ENABLE for comborolls.
 * QMK combos work with modifier keys as they are "early" in the processing chain but comborolls don't. However
 * QMK combos don't work as well when you have overlapping rolls.
 *
 * The definition macros for comborolls are named (LtoR|RtoL|CMBO)_(KEY|ARR|LIT|STR|TRM):
 *
 * LtoR: comboroll, triggers pressed from left to right
 * RtoL: comboroll, triggers pressed from right to left
 * CMBO: triggers nominally pressed as the same time (in either direction)
 *
 * STR: arguments are name, triggers. The name is output as a string.
 * LIT: arguments are name, literal string, triggers
 * KEY: arguments are name, keycode, triggers
 * ARR: arguments are name, array of keycodes, triggers
 * TRM: arguments are name, term. This changes the timeout, and must follow the combo definition.
 *
 * By default, rolls have a longer timeout.
 * 
 * For QMK combos, the macro names are the same but prefixed by "Q_". More than one trigger
 * can be given for the Q_LtoR_ and Q_CMBO_ macros, but not for the Q_RtoL_ macros.
 * 
 * My "best practice" is to use comborolls for everything, and QMK combos only for things
 * that use modifiers and are not typed overlapping with any comborolls.
 */
// clang-format off

// Anti-SFU and anti-pinballing
LtoR_STR( sc, KC_C, KC_W )
LtoR_STR( sp, KC_P, KC_G )

RtoL_STR( lf, KC_F, KC_U )
RtoL_STR( er, KC_O, KC_A )
RtoL_STR( ve, KC_I, CU_COMM )
RtoL_STR( ee, KC_Y, CU_COMM )

RtoL_LIT( quotll, "'ll", KC_L, CU_COMM )

// Verticals
CMBO_STR( tw, KC_T, KC_W )
CMBO_STR( ps, KC_S, KC_C )
CMBO_STR( z,  KC_H, KC_M )
CMBO_STR( fl, KC_N, KC_F )
CMBO_STR( ui, KC_I, KC_U )

// Awkward bigrams/trigrams
LtoR_STR( ght, KC_T, KC_D )
LtoR_STR( cr,  KC_W, KC_M )
LtoR_STR( qu,  KC_B, KC_M )
LtoR_STR( pr,  KC_G, KC_D )

RtoL_STR( you, KC_U, CU_DOT )

// Inner column minimization
LtoR_STR( ck,  KC_C, KC_M )
LtoR_STR( k,   KC_T, KC_M )

LtoR_STR( rk,  KC_R, KC_W )
LtoR_STR( bl,  KC_B, KC_W )
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( b,   KC_S, KC_D )

// Common word endings, right hand
RtoL_STR( ally, KC_F, CU_DOT )
RtoL_STR( ould, KC_I, CU_DOT )
RtoL_STR( all,  KC_N, CU_DOT )
RtoL_STR( ough, KC_N, CU_COMM )

// Right-to-left rolls on left hand
RtoL_KEY( comma,  KC_COMM, KC_P, KC_G )  RtoL_TRM( comma,  300 )
RtoL_KEY( period, KC_DOT,  KC_C, KC_W )  RtoL_TRM( period, 300 )

// Comborolls across both hands
RtoL_STR( ble,  KC_B, CU_COMM )
RtoL_STR( cd,   KC_C, CU_COMM )
RtoL_STR( was,  KC_W, CU_COMM )
RtoL_STR( pwd,  KC_P, CU_COMM )
    
RtoL_STR( be,   KC_R, CU_COMM )
RtoL_STR( his,  KC_S, CU_COMM )
RtoL_STR( but,  KC_T, CU_COMM )
RtoL_STR( had,  KC_H, CU_COMM )
RtoL_STR( vs,   KC_V, CU_COMM )

RtoL_STR( grep, KC_G, CU_COMM )
RtoL_STR( diff, KC_D, CU_COMM )

//RtoL_LIT( ifdef,  "#ifdef",  KC_F, KC_Q )
//RtoL_LIT( endif,  "#endif",  KC_H, KC_Q )
//RtoL_LIT( define, "#define", KC_D, KC_Q )

// Extras and oddballs
RtoL_LIT( apos_s, "'s", KC_S, KC_SCLN )
RtoL_LIT( apos_t, "'t", KC_T, KC_SCLN )

RtoL_LIT( espace, "e ", KC_E, CU_COMM )

// Contractions. Use ARR so that shift doesn't change the quote into double quote
/*
Q_RtoL_ARR( quote_ll,
    ARRAY_PROTECT(
        CU_QUOTE_QUOTE,
        KC_L,
        KC_L
    ), KC_L, KC_RSFT)
Q_RtoL_ARR( quote_re,
    ARRAY_PROTECT(
        CU_QUOTE_QUOTE,
        KC_R,
        KC_E
    ), KC_Y, KC_RSFT)
*/

// Utilities
//Q_CMBO_KEY( search, SC_SEARCH,         KC_QUOT,  KC_E )    // Search key, on right thumb
Q_CMBO_KEY( expose, SC_EXPOSE_WINDOWS, KC_BSPC,  KC_DEL )  // Window expose, left thumb on EDIT layer

CMBO_KEY( search, SC_SEARCH,     KC_M, KC_F )

CMBO_KEY( screenlock, CU_SLCK,   KC_ESC, KC_Q )


// Syntax layer
RtoL_LIT( quesrangle,      "?>",    CU_7, CU_8 )   ___NOSFT( quesrangle )
RtoL_LIT( langleques,      "<?",    CU_8, CU_9 )   ___NOSFT( langleques )

RtoL_LIT( closeparensemi,  ");",    CU_3, CU_0 )   ___NOSFT( closeparensemi )
RtoL_LIT( not_equal,       "!=",    CU_2, CU_0 )   ___NOSFT( not_equal )

RtoL_LIT( threebacktick,   "```",   CU_1, CU_TILDE_DOLLAR ) ___NOSFT( threebacktick )

RtoL_LIT( phpopen,         "<?php", CU_8, CU_0 )   ___NOSFT( phpopen )
RtoL_LIT( phpecho,         "<?=",   CU_9, CU_0 )   ___NOSFT( phpecho )

RtoL_LIT( dirup,           "../",   CU_2, CU_6 )   ___NOSFT( dirup )

RtoL_LIT( lbracedbl,       "{{",    CU_1, CU_6 )   ___NOSFT( lbracedbl )
RtoL_LIT( rbracedbl,       "}}",    CU_4, CU_3 )   ___NOSFT( rbracedbl )
