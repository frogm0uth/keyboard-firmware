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
 ** Definitions of custom shifts. This file is included in multiple places
 ** with different definitions of DEFINE_SHIFT
 **/

// clang-format off

// Punctuation with numbers on shift
//
DEFINE_SHIFT( CU_0, KC_EQL,  KC_0 )
DEFINE_SHIFT( CU_1, KC_RABK, KC_1 )
DEFINE_SHIFT( CU_2, KC_SLSH, KC_2 )
DEFINE_SHIFT( CU_3, KC_LABK, KC_3 )
DEFINE_SHIFT( CU_4, KC_RBRC, KC_4 )
DEFINE_SHIFT( CU_5, KC_QUES, KC_5 )
DEFINE_SHIFT( CU_6, KC_LBRC, KC_6 )
DEFINE_SHIFT( CU_7, KC_RCBR, KC_7 )
DEFINE_SHIFT( CU_8, KC_PERC, KC_8 )
DEFINE_SHIFT( CU_9, KC_LCBR, KC_9 )

// Custom punctuation pairs on alpha layer
DEFINE_SHIFT( CU_COMMA_PIPE,        KC_COMM, KC_PIPE )
DEFINE_SHIFT( CU_DOT_SLASH,         KC_DOT,  KC_SLASH )
DEFINE_SHIFT( CU_EXCLAIM_QUESTION,  KC_EXLM, KC_QUES )

// Custom punctuation pairs on symbols layer
DEFINE_SHIFT( CU_MINUS_COMMA,       KC_MINS, KC_COMM )
DEFINE_SHIFT( CU_DOLLAR_UNDERSCORE, KC_DLR,  KC_UNDS )

// Keys that are the same whether shifted or not
DEFINE_SHIFT( CU_DOT_DOT,           KC_DOT,  KC_DOT )
DEFINE_SHIFT( CU_QUOTE_QUOTE,       KC_QUOT, KC_QUOT )
DEFINE_SHIFT( CU_SCLN_SCLN,         KC_SCLN, KC_SCLN )

// Custom keys
DEFINE_SHIFT(CU_TAB_RIGHT,   SC_TAB_RIGHT,   SC_TAB_LEFT )
DEFINE_SHIFT(CU_TAB_LEFT,    SC_TAB_LEFT,    SC_TAB_RIGHT )
DEFINE_SHIFT(CU_NEXT_WINDOW, SC_NEXT_WINDOW, SC_PREV_WINDOW )
DEFINE_SHIFT(CU_PREV_WINDOW, SC_PREV_WINDOW, SC_NEXT_WINDOW )
