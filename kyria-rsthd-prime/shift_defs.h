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
DEFINE_SHIFT( CU_4, KC_RCBR, KC_4 )
DEFINE_SHIFT( CU_5, KC_PERC, KC_5 )
DEFINE_SHIFT( CU_6, KC_LCBR, KC_6 )
DEFINE_SHIFT( CU_7, KC_RBRC, KC_7 )
DEFINE_SHIFT( CU_8, KC_HASH, KC_8 )
DEFINE_SHIFT( CU_9, KC_LBRC, KC_9 )

// Custom punctuation pairs on alpha layer
DEFINE_SHIFT( CU_DOT_EXLM,     KC_DOT,  KC_EXLM )
DEFINE_SHIFT( CU_COMMA_QUES,   KC_COMM, KC_QUES )
DEFINE_SHIFT( CU_TAB_DQUOTE,   KC_TAB,  KC_DQUO )

// Custom punctuation pairs on syms layer
DEFINE_SHIFT( CU_TILDE_GRAVE,  KC_TILD, KC_GRV )
DEFINE_SHIFT( CU_AMP_AT,       KC_AMPR, KC_AT )
DEFINE_SHIFT( CU_MINS_PLUS,    KC_MINS, KC_PLUS )

// Keys that are the same whether shifted or not
DEFINE_SHIFT( CU_DOT_DOT,      KC_DOT,  KC_DOT )
DEFINE_SHIFT( CU_TAB_TAB,      KC_TAB,  KC_TAB )
DEFINE_SHIFT( CU_MINUS_MINUS,  KC_MINS, KC_MINS )
DEFINE_SHIFT( CU_EQL_EQL,      KC_EQL,  KC_EQL )
DEFINE_SHIFT( CU_QUOTE_QUOTE,  KC_QUOT, KC_QUOT )

// Custom keys
DEFINE_SHIFT(CU_TAB_RIGHT,   SC_TAB_RIGHT,   SC_TAB_LEFT )
DEFINE_SHIFT(CU_TAB_LEFT,    SC_TAB_LEFT,    SC_TAB_RIGHT )
DEFINE_SHIFT(CU_NEXT_WINDOW, SC_NEXT_WINDOW, SC_PREV_WINDOW )
DEFINE_SHIFT(CU_PREV_WINDOW, SC_PREV_WINDOW, SC_NEXT_WINDOW )
