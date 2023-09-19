
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
 * output. However it takes more space (about 2k in this keymap) and there are other issues when
 * typing with a rolling style.
 *
 * See docs/comborolls.md for more information.
 *
 * The definition macros are named (LtoR|RtoL|CMBO)_(KEY|ARR|LIT|STR):
 *
 * LtoR: comboroll, triggers pressed from left to right
 * RtoL: comboroll, triggers pressed from right to left
 * CMBO: triggers nominally pressed as the same time (in either direction)
 *
 * KEY: arguments are name, keycode, triggers
 * ARR: arguments are name, array of keycodes, triggers
 * LIT: arguments are name, literal string, triggers
 * STR: arguments are name, triggers. The name is output as a string.
 *
 * By default, RtoL and LtoR have a longer timeout, on the assumption they will be typed as a "roll"
 * instead of deliberately both pressed at the same time.  To define a custom term for a combo, use
 * the _____TRM(name,ms) macro. It must be *after* the macro that defines that combo.
 * 
 * Notes:
 * 
 * 1. By convention, the trigger keys should be listed from left to right location in the keymap.
 *
 * 2. If COMBOROLL_ENABLED is defined, none of the macros work with more than two trigger keys. For
 * defs with > 2 trigger keys, wrap them in a #ifdef COMBO_ENABLED.
 *
 * 3. The RtoL version works only for two trigger keys even for QMK combos.
 *
 * 4. If COMBOROLL_ENABLED is defined, don't use modifiers or layer switch keys as triggers or output.
 */
// clang-format off

// Anti-SFU and anti-pinballing
LtoR_STR( m,  KC_S, KC_D )
LtoR_STR( sc, KC_C, KC_W )
LtoR_STR( sp, KC_P, KC_G )

CMBO_STR( et, CU_DOT, KC_MINS ) _____TRM( et,  300 )
RtoL_STR( er, KC_O, KC_A )
RtoL_STR( ed, KC_L, KC_Y )
RtoL_STR( es, KC_L, CU_COMM )
RtoL_STR( ve, KC_I, CU_COMM )
RtoL_STR( ee, KC_Y, CU_COMM )

// Verticals
CMBO_STR( tw, KC_T, KC_W )
CMBO_STR( ps, KC_S, KC_C )
CMBO_STR( z,  KC_H, KC_F )
CMBO_STR( j,  KC_N, KC_M )
CMBO_STR( ui, KC_I, KC_U )
CMBO_KEY( enter, KC_ENT, KC_O, CU_DOT )

// Awkward bigrams/trigrams
LtoR_STR( ght, KC_X, KC_H )
LtoR_STR( cr,  KC_W, KC_F )
LtoR_STR( fr,  KC_S, KC_F )
LtoR_STR( qu,  KC_V, KC_F )
LtoR_STR( pr,  KC_G, KC_D )

RtoL_STR( you, KC_U, CU_DOT )

// Inner column minimization
LtoR_STR( ck,  KC_C, KC_F )
LtoR_STR( k,   KC_T, KC_F )

LtoR_STR( rk,  KC_R, KC_W )
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( b,   KC_T, KC_D )

// Common word endings, right hand
RtoL_STR( ally, KC_M, CU_DOT )
RtoL_STR( ould, KC_I, CU_DOT )
RtoL_STR( all,  KC_N, CU_DOT )
RtoL_STR( ough, KC_N, CU_COMM )

// Right-to-left rolls on left hand
RtoL_KEY( comma,  KC_COMM, KC_P, KC_G )  _____TRM( comma,  300 )
RtoL_KEY( period, KC_DOT,  KC_C, KC_W )  _____TRM( period, 300 )

// Comborolls across both hands
RtoL_STR( vs,   KC_V, CU_COMM )
RtoL_STR( fac,  KC_C, CU_COMM )
RtoL_STR( was,  KC_W, CU_COMM )
RtoL_STR( pwd,  KC_P, CU_COMM )
    
RtoL_STR( be,   KC_R, CU_COMM )
RtoL_STR( his,  KC_S, CU_COMM )
RtoL_STR( but,  KC_T, CU_COMM )
RtoL_STR( had,  KC_H, CU_COMM )

RtoL_STR( for,  KC_F, CU_COMM )
RtoL_STR( grep, KC_G, CU_COMM )
RtoL_STR( diff, KC_D, CU_COMM )

RtoL_LIT( ifdef,  "#ifdef",  KC_F, KC_Q )
RtoL_LIT( endif,  "#endif",  KC_H, KC_Q )
RtoL_LIT( define, "#define", KC_D, KC_Q )

// Extras and oddballs
LtoR_STR( ion, KC_H, KC_QUOT )
LtoR_STR( any, KC_X, KC_D )

// Contractions. Use ARR so that still get single quote even if shift pressed
RtoL_ARR( quote_s,
    ARRAY_PROTECT(
        KC_QUOT,
        KC_S
    ), KC_I, KC_Q)
RtoL_ARR( quote_ll,
    ARRAY_PROTECT(
        KC_QUOT,
        KC_L,
        KC_L
    ), KC_L, KC_Q)
RtoL_ARR( quote_re,
    ARRAY_PROTECT(
        KC_QUOT,
        KC_R,
        KC_E
    ), KC_N, KC_Q)

// Utilities
CMBO_KEY( expose, SC_EXPOSE_WINDOWS, KC_BSPC,  KC_DEL )  // Window expose, left thumb on EDIT layer

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

