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
 * ...._STR: arguments are name, triggers. The name is output as a string. Auto-shift works.
 * ...._LIT: arguments are name, literal string, triggers. Shift is ignored.
 * ...._KEY: arguments are name, keycode, triggers. Shift is ignored.
 * ...._ARR: arguments are name, array of keycodes, triggers. Shift is ignored.
 * 
 * ...._TRM: arguments are name, term. This changes the timeout, and must follow the combo definition.
 * _ONSHIFT: argument is the name. Makes the combo trigger only on shift, and must follow the combo definition.
 * _NOSHIFT: argument is the name. Makes the combo trigger only if no shift, and must follow the combo definition.
 *
 * This is an example of the ARR macro:
 *
 * RtoL_ARR( quote_ll,
 *   ARRAY_PROTECT(
 *       CU_QUOTE_QUOTE,
 *       KC_L,
 *       KC_L
 *   ), KC_L, KC_RSFT)
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

// Letters not in alpha and related rolls
LtoR_STR( j,  KC_S, KC_G )
LtoR_STR( k,  KC_W, KC_F )

// Anti-SFU and anti-pinballing
LtoR_STR( m,  KC_S, KC_D )
LtoR_STR( sc, KC_B, KC_W )
LtoR_STR( sp, KC_P, KC_G )

RtoL_STR( ll, KC_N, CU_DOT )
RtoL_STR( er, KC_O, KC_A )
RtoL_STR( ee, KC_Y, CU_COMM )

// Verticals
CMBO_STR( tw, KC_T, KC_W )
CMBO_STR( cs, KC_S, KC_C )
CMBO_STR( ps, KC_H, KC_F )
CMBO_STR( lm, KC_N, KC_M )
CMBO_STR( ui, KC_I, KC_U )

// Awkward bigrams/trigrams
LtoR_STR( cr,  KC_T, KC_F )
LtoR_STR( fr,  KC_S, KC_F )
LtoR_STR( ft,  KC_C, KC_F )
LtoR_STR( qu,  KC_B, KC_F )
LtoR_STR( pr,  KC_G, KC_D )

RtoL_STR( you, KC_U, CU_DOT )

// Inner column minimization and comfort
LtoR_STR( br,  KC_R, KC_H )
LtoR_STR( b,   KC_T, KC_D )
LtoR_STR( v,   KC_P, KC_D )

RtoL_STR( ve, KC_I, CU_COMM )

// Common word endings, right hand
RtoL_STR( ally, KC_M, CU_DOT )
RtoL_STR( ould, KC_I, CU_DOT )
RtoL_STR( ough, KC_N, CU_COMM )

// Right-to-left rolls on left hand
RtoL_KEY( comma,  KC_COMM, KC_P, KC_G )  RtoL_TRM( comma,  300 )
RtoL_KEY( period, KC_DOT,  KC_C, KC_W )  RtoL_TRM( period, 300 )

// Comborolls across both hands
RtoL_STR( cd,   KC_C, CU_COMM )
RtoL_STR( was,  KC_W, CU_COMM )
RtoL_STR( for,  KC_F, CU_COMM )

RtoL_STR( but,  KC_R, CU_COMM )
RtoL_STR( his,  KC_S, CU_COMM )
RtoL_STR( ght,  KC_T, CU_COMM )
RtoL_STR( had,  KC_H, CU_COMM )
RtoL_STR( vs,   KC_V, CU_COMM )

RtoL_STR( pwd,  KC_P, CU_COMM )
RtoL_STR( grep, KC_G, CU_COMM )
RtoL_STR( diff, KC_D, CU_COMM )

RtoL_LIT( ifdef,  "#ifdef",  KC_F, KC_Q )
RtoL_LIT( endif,  "#endif",  KC_H, KC_Q )
RtoL_LIT( define, "#define", KC_D, KC_Q )

// Extras and oddballs
LtoR_STR( from, KC_F, KC_M )

RtoL_LIT( espace, "e ",     KC_E,   CU_COMM )
RtoL_LIT( ospace, "o ",     KC_E,   CU_DOT )
RtoL_LIT( backslash, "\\",  KC_U, KC_MINS )

// Utilities
CMBO_KEY( screenlock, CU_SLCK,   KC_ESC, KC_Q )

// Syntax layer - most only trigger if shift is down
LtoR_LIT( l_c_comment, "/*", CU_LPRN, KC_ASTR ) _ONSHIFT( l_c_comment )
LtoR_LIT( r_c_comment, "*/", KC_ASTR, CU_RPRN ) _ONSHIFT( r_c_comment )

LtoR_LIT( l_j_comment, "{#", CU_3, KC_ASTR ) _ONSHIFT( l_j_comment )
LtoR_LIT( r_j_comment, "#}", KC_ASTR, CU_1 ) _ONSHIFT( r_j_comment )

LtoR_LIT( l_php, "<?php", CU_LT, CU_SLSH_SLSH) _ONSHIFT( l_php )
LtoR_LIT( r_php, "?>",    CU_SLSH_SLSH, CU_GT) _ONSHIFT( r_php )

LtoR_LIT( parensemi, ");", CU_LT,        CU_GT )   _ONSHIFT( parensemi )
LtoR_LIT( eql_gt,    "=>", CU_MINS_MINS, CU_GT)    _ONSHIFT( eql_gt )

LtoR_LIT( htmlcomment, "<!--", CU_MINS_MINS, CU_LT)
LtoR_LIT( code, "```", CU_MINS_MINS, CU_SLSH_SLSH)

//LtoR_LIT( tildeslash,  "~/",   CU_MINS_MINS, CU_SLSH_SLSH)
