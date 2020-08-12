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
#include QMK_KEYBOARD_H

#include "compose_key.h"

/**
 ** The actual compose tree. If compose mode is active, this tree gets walked
 ** one level at a time on each keypress.
 **/

//#define COMPOSE_EXAMPLE_CALLBACK_1
//#define COMPOSE_EXAMPLE_CALLBACK_2

/**
 * Symbols that are output from key sequences. Lower nodes of the compose tree
 * are defined first for easy reference in higher nodes.
 * 
 * FIXME these are all Mac-specific, need to use OS-shortcuts for Win/Lin support
 */
struct compose_node greek_symbols[] = {
    COMPOSE_KEYCODE(KC_M, A(KC_M)),    // mu
    COMPOSE_KEYCODE(KC_O, A(KC_Z)),    // Ohm
    COMPOSE_KEYCODE(KC_P, A(KC_P)),    // pi
    COMPOSE_END
};

struct compose_node currency_symbols[] = {
    COMPOSE_KEYCODE(KC_E, S(A(KC_2))),    // Euro
    COMPOSE_KEYCODE(KC_Y, A(KC_Y)),       // Yen
    COMPOSE_KEYCODE(KC_P, A(KC_3)),       // Pounds
    COMPOSE_KEYCODE(KC_C, A(KC_4)),       // cents
    COMPOSE_END
};

struct compose_node math_symbols[] = {
    COMPOSE_KEYCODE(KC_RABK, A(KC_DOT)),     // greater or equal
    COMPOSE_KEYCODE(KC_LABK, A(KC_COMM)),    // less or equal
    COMPOSE_KEYCODE(KC_SLSH, A(KC_SLSH)),    // division
    COMPOSE_KEYCODE(KC_DOT,  A(KC_8)),       // mid dot
    COMPOSE_KEYCODE(KC_PLUS, A(S(KC_EQL))),  // plus or minus
    COMPOSE_KEYCODE(KC_EQL,  A(KC_X)),       // approx equal
    COMPOSE_KEYCODE(KC_EXLM, A(KC_EQL)),     // not equal
    COMPOSE_END
};

struct compose_node print_symbols[] = {
    COMPOSE_KEYCODE(  KC_C,  A(KC_G)),       // copyright
    COMPOSE_KEYCODE(  KC_R,  A(KC_R)),       // registered
    COMPOSE_KEYCODE(  KC_T,  A(KC_2)),       // trademark
    COMPOSE_KEYCODE(S(KC_D), S(A(KC_7))),    // double dagger
    COMPOSE_KEYCODE(  KC_D,  A(KC_T)),       // dagger
    COMPOSE_KEYCODE(  KC_F,  A(S(KC_8))),    // degrees
    COMPOSE_END
};

#ifdef COMPOSE_EXAMPLE_CALLBACK_1
// Example callback. Note: not a good example as this can be done with COMPOSE_ARRAY.
void print_exclaim(uint16_t keycode) {
    tap_code16(KC_QUES);
    tap_code16(KC_EXLM);
}
#endif

#ifdef COMPOSE_EXAMPLE_CALLBACK_2
// Example callback. Note: not a good example as this can be done with COMPOSE_STRING.
void print_email(uint16_t keycode) {
    send_literal_string("myname@mydomain.com");
}
#endif

/**
 * Keycode arrays
 */
uint16_t array_c_comment[] = {
    KC_SLASH,
    KC_ASTERISK,
    KC_SPACE,
    KC_SPACE,
    KC_ASTERISK,
    KC_SLASH,
    KC_LEFT,
    KC_LEFT,
    KC_LEFT,
    KC_NO
};

uint16_t array_c_comment_newline[] = {
    KC_ENTER,
    KC_ASTERISK,
    KC_SPACE,
    KC_TAB,
    KC_NO
};

/**
 * The root of the compose tree
 */
struct compose_node compose_tree_root[] = {
    // Various symbols, walk down a level
    COMPOSE_CONTINUE(KC_G,    greek_symbols),
    COMPOSE_CONTINUE(KC_DLR,  currency_symbols),
    COMPOSE_CONTINUE(KC_M,    math_symbols),
    COMPOSE_CONTINUE(KC_P,    print_symbols),
  
#ifdef COMPOSE_EXAMPLE_CALLBACK_1
    COMPOSE_CALLBACK(KC_EXLM, print_exclaim),    // output a keycode (example of callback)
#endif

#ifdef COMPOSE_EXAMPLE_CALLBACK_2
    COMPOSE_CALLBACK(KC_AT, print_email),    // print email address (example of callback)
#endif

    // String outputs
    COMPOSE_STRING(S(KC_Y), "You"),
    COMPOSE_STRING(  KC_Y,  "you"),
    COMPOSE_STRING(S(KC_H), "His"),
    COMPOSE_STRING(  KC_H,  "his"),
    COMPOSE_STRING(  KC_I,  "ize"),
    COMPOSE_STRING(  KC_N,  "izing"),

    // Array outputs
    COMPOSE_ARRAY(  KC_SLASH,  array_c_comment),
    COMPOSE_ARRAY(S(KC_SLASH), array_c_comment_newline),

    COMPOSE_END // IMPORTANT: leave this at the end!!
};

