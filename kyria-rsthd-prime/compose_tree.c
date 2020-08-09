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

//#define COMPOSE_EXAMPLE_CALLBACK

// FIXME these are all Mac-specific, need to use OS-shortcuts for Win/Lin support
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

//#ifdef COMPOSE_EXAMPLE_CALLBACK
// Example callback
void print_email(uint16_t keycode) {
  //SEND_STRING("myname@mydomain.com");
  my_send_string("myname@mydomain.com");
}
//#endif

// Output arrays
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

struct compose_node compose_tree_root[] = {
  // Various symbols
  COMPOSE_CONTINUE(KC_G,    greek_symbols),
  COMPOSE_CONTINUE(KC_DLR,  currency_symbols),
  COMPOSE_CONTINUE(KC_M,    math_symbols),
  COMPOSE_CONTINUE(KC_P,    print_symbols),
  
#ifdef COMPOSE_EXAMPLE_CALLBACK
  COMPOSE_CALLBACK(KC_AT, print_email),    // print email address (example of callback)
#endif
  
  // strings outputs
  COMPOSE_STRING(S(KC_Y), "You"),
  COMPOSE_STRING(  KC_Y,  "you"),
  COMPOSE_STRING(S(KC_H), "His"),
  COMPOSE_STRING(  KC_H,  "his"),
  COMPOSE_STRING(  KC_I,  "ize"),
  COMPOSE_STRING(  KC_N,  "izing"),

  // array outputs
  COMPOSE_ARRAY(  KC_SLASH,  array_c_comment),
  COMPOSE_ARRAY(S(KC_SLASH), array_c_comment_newline),
};

