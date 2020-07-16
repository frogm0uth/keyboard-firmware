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


struct compose_node greek_symbols[] = {
  COMPOSE_OUTPUT(KC_M, A(KC_M)),    // mu
  COMPOSE_OUTPUT(KC_O, A(KC_Z)),    // Ohm
  COMPOSE_OUTPUT(KC_P, A(KC_P)),    // pi
  COMPOSE_END
};

struct compose_node currency_symbols[] = {
  COMPOSE_OUTPUT(KC_E, S(A(KC_2))),    // Euro
  COMPOSE_OUTPUT(KC_Y, A(KC_Y)),       // Yen
  COMPOSE_OUTPUT(KC_P, A(KC_3)),       // Pounds
  COMPOSE_OUTPUT(KC_C, A(KC_4)),       // cents
  COMPOSE_END
};

struct compose_node math_symbols[] = {
  COMPOSE_OUTPUT(KC_RABK, A(KC_DOT)),     // greater or equal
  COMPOSE_OUTPUT(KC_LABK, A(KC_COMM)),    // less or equal
  COMPOSE_OUTPUT(KC_SLSH, A(KC_SLSH)),    // division
  COMPOSE_OUTPUT(KC_DOT,  A(KC_8)),       // mid dot
  COMPOSE_OUTPUT(KC_PLUS, A(S(KC_EQL))),  // plus or minus
  COMPOSE_OUTPUT(KC_EQL,  A(KC_X)),       // approx equal
  COMPOSE_OUTPUT(KC_EXLM, A(KC_EQL)),     // not equal
  COMPOSE_END
};

struct compose_node print_symbols[] = {
  COMPOSE_OUTPUT(KC_C, A(KC_G)),       // copyright
  COMPOSE_OUTPUT(KC_R, A(KC_R)),       // registered
  COMPOSE_OUTPUT(KC_T, A(KC_2)),       // trademark
  COMPOSE_OUTPUT(S(KC_D), S(A(KC_7))), // double dagger
  COMPOSE_OUTPUT(KC_D, A(KC_T)),       // dagger
  COMPOSE_OUTPUT(KC_F, A(S(KC_8))),    // degrees
  COMPOSE_END
};

#ifdef COMPOSE_EXAMPLE_CALLBACK
// Example callback
void print_email(uint16_t keycode) {
  SEND_STRING("myname@mydomain.com");
}
#endif

struct compose_node compose_tree_root[] = {
  // Various symbols
  COMPOSE_CONTINUE(KC_G,    greek_symbols),
  COMPOSE_CONTINUE(KC_DLR,  currency_symbols),
  COMPOSE_CONTINUE(KC_M,    math_symbols),
  COMPOSE_CONTINUE(KC_P,    print_symbols),
  
#ifdef COMPOSE_EXAMPLE_CALLBACK
  COMPOSE_CALLBACK(KC_AT, print_email),    // print email address (example of callback)
#endif

  COMPOSE_END
};

