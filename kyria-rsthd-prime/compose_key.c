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

#include "keymap.h"


enum compose_status {
  compose_init = 0,
  compose_active,
  compose_success,
  compose_failed,
  compose_aborted
};
static uint8_t compose_status = compose_init;



#ifdef COMPOSE_STATUS_ENABLE
// Utilities for displaying stuff on the OLED
//

#ifndef COMPOSE_MAX_SEQUENCE
#define COMPOSE_MAX_SEQUENCE 12
#endif
static char compose_sequence[COMPOSE_MAX_SEQUENCE+1];
static uint8_t compose_sequence_last = 0;

// The character conversion array below is copied from
// qmk_firmware/quantum/process_keycode/process_terminal.c, as it's usually not
// compiled in. (Also, the shifted quote character is only a single quote.)
//
#ifndef TERMINAL_ENABLE
const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

const char shifted_keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 0, 0, 0, '\t', ' ', '_', '+', '{', '}', '|', 0, ':', '\"', '~', '<', '>', '?'};

#endif

// Utility functions for managing the array of entered characters
//
void reset_sequence_string(void) {
  compose_sequence_last = 0;
  compose_sequence[0] = '\0';
}

void append_keycode_to_sequence_string(uint16_t keycode, bool shifted) {
  char char_to_add;
  if (shifted) {
    char_to_add = shifted_keycode_to_ascii_lut[keycode & 0xFF];
  } else {
    char_to_add = keycode_to_ascii_lut[keycode];
  }
  if (compose_sequence_last < COMPOSE_MAX_SEQUENCE) {
    compose_sequence[compose_sequence_last] = char_to_add;
    compose_sequence_last++;
    compose_sequence[compose_sequence_last] = '\0';
  }
}
#endif

static struct compose_node* compose_current = compose_tree_root;


// Handle compose key press/release
//
void process_record_compose(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed){
    if (compose_status != compose_active) {
      compose_status = compose_active;
      compose_current = compose_tree_root;
#ifdef COMPOSE_STATUS_ENABLE
      reset_sequence_string();
#endif
    } else {
      compose_status = compose_aborted;
    }
  }
}

// Handle ANY key press/release. Return true if the key was intercepted.
//
bool compose_key_intercept(uint16_t keycode, keyrecord_t *record) {
  uint8_t mods = get_mods();
  bool match;
  
  if (compose_status != compose_active || !record->event.pressed || keycode > QK_MODS_MAX ) {
    return false;
  }
  // Scan for the key
  while (compose_current->node_type != compose_terminate) {

    // Test if the keycode matches this trigger
    match = false;
    if (mods & MOD_MASK_SHIFT) {
      match = (S(keycode) == compose_current->trigger); // compose tree must only use S() modifier
    } else {
      match = keycode == compose_current->trigger;
    }

    // Handle a match
    if (match) {
#ifdef COMPOSE_STATUS_ENABLE
      // Append the keycode for display on the OLED
      append_keycode_to_sequence_string(compose_current->trigger, mods & MOD_MASK_SHIFT);
#endif

      switch (compose_current->node_type) {
	
      case compose_continue:  // Move down one level
	compose_current = compose_current -> continuation;
	break;

      case compose_callback:
	(*(compose_current->compose_callback))(keycode);
	compose_status = compose_success; // Done
	break;

      case compose_output:
	clear_mods();
	tap_code16(compose_current->output_keycode);
	set_mods(mods);
	compose_status = compose_success; // Done
	break;
      }
      return true;
    }
    compose_current++; // Try the next one
  }
  // Failed to match
  compose_status = compose_failed;
  
#ifdef COMPOSE_STATUS_ENABLE
  // Display last keycode even if failure
  append_keycode_to_sequence_string(keycode, mods & MOD_MASK_SHIFT);
#endif

  return true; // swallow the last code, it's not expected that it will output
}

#ifdef COMPOSE_STATUS_ENABLE
static char* compose_status_strings[] = {
  [compose_init]    = "",
  [compose_active]  = "COMPOSE:  ",
  [compose_success] = "COMPLETE: ",
  [compose_failed]  = "FAILED:   ",
  [compose_aborted] = "CANCELED",
};

void compose_key_status() {
  oled_write(compose_status_strings[compose_status], false);
  if (compose_status != compose_init && compose_status != compose_aborted) {
    oled_write(compose_sequence, false);
  }
  oled_write_P(PSTR("\n"), false);
}
#endif