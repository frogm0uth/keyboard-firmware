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
#pragma once
#include QMK_KEYBOARD_H

#include "keymap.h"

// simplify #define for OLED status output
#if !defined(OLED_DRIVER_ENABLE) && defined(COMPOSE_STATUS_ENABLE)
  #undef COMPOSE_STATUS_ENABLE
#endif


enum compose_type {
  compose_output = 0,
  compose_continue,
  compose_callback,
  compose_terminate
};

// node of the compose tree
struct compose_node {
  uint8_t  node_type;
  uint16_t trigger;
  union {
    uint16_t output_keycode;
    struct compose_node* continuation;
    void (*compose_callback)(uint16_t);
  };
};

extern struct compose_node compose_tree_root[];


// Macros to help in writing the compose tree
#define COMPOSE_CONTINUE(trigger,cont)        {compose_continue,  trigger, {.continuation=cont}}
#define COMPOSE_CALLBACK(trigger, callback)   {compose_callback,  trigger, {.compose_callback=callback}}
#define COMPOSE_OUTPUT(trigger, outcode)      {compose_output,    trigger, {.output_keycode=outcode}}
#define COMPOSE_END                           {compose_terminate, KC_NO}


// Callable functions
void process_record_compose(uint16_t keycode, keyrecord_t *record);
bool compose_key_intercept(uint16_t keycode, keyrecord_t *record);
void compose_key_reset(void);

#ifdef COMPOSE_STATUS_ENABLE
void compose_key_status(void);
#endif
