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

#include "layer_tap_toggle.h"
#include "keymap.h"

/**
 ** Layer-tap-toggle. Layer active while held, Ctrl-tap to toggle on, Tap to send some other key.
 ** Tap to untoggle the layer. Note: there is no auto-repeat on the tap key on second
 ** tap, like with standard LT or mod-tap.
 **/

// State of the layer-tap-toggle for a single layer
enum { 
  LTT_INACTIVE,
  LTT_TAPPING_ON,
  LTT_TAPPED,
  LTT_HOLDING,
  LTT_TOGGLED
};

// State arrays, one element per layer
static uint16_t ltt_timer[NUM_LAYERS];
static uint8_t ltt_state[NUM_LAYERS];
static bool ltt_initialized = false;

// Update the timer(s) for layer-tap-toggle. Must be called from matrix_scan_user.
void ltt_update_timer (void) {
  for (int i=0; i<NUM_LAYERS; i++) {
    if (ltt_state[i] == LTT_TAPPING_ON) {
      if (timer_elapsed(ltt_timer[i]) > TAPPING_TERM) {
	ltt_state[i] = LTT_HOLDING; // Go to holding state when timer expires
      }
    }
  }
}

// Call from process_record_user for keys pressed. Prevents
// false hits if the layer key and another are pressed within
// the tapping term.
void ltt_interrupt(uint16_t keycode, keyrecord_t *record) {
  if (keycode < QK_MODS_MAX) {
    layer_state_t layer = get_highest_layer(layer_state);
    if (record->event.pressed) {
      switch (ltt_state[layer]) {
      case LTT_TAPPING_ON:
	ltt_state[layer] = LTT_TAPPED;
	break;
      }
    }
  }
}


  // Go back to base layer. Call from process_record_user.
bool ltt_base(void) {
  for (int i=0; i<NUM_LAYERS; i++) {
    ltt_state[i] = LTT_INACTIVE;
  }
  layer_clear();
  return false;
}

// Lock the layer. Call this from process-record_user in response to a lock keypress.
bool ltt_lock(keyrecord_t *record) {
  layer_state_t layer = get_highest_layer(layer_state);
  if (record->event.pressed) {
    switch (ltt_state[layer]) {
    case LTT_TAPPING_ON:
    case LTT_HOLDING:
      ltt_state[layer] = LTT_TOGGLED; // Lock it on
      break;
    }
  }
  return false;
}


// Update the layer-tap-toggle state. Must be called from process_record_user.
// Pass KC_NO if you don't want tap to send a key.
//
// Always returns false.
//
bool layer_tap_toggle(uint16_t keycode, uint8_t layer, keyrecord_t *record) {
  if (!ltt_initialized) { // Make sure state array is a known state
    ltt_base();
    ltt_initialized = true;
  }
  if (record->event.pressed) {
    ltt_timer[layer] = timer_read();
    switch (ltt_state[layer]) {
    case LTT_INACTIVE:
      if (get_mods() & MOD_MASK_GUI) {
	ltt_state[layer] = LTT_TOGGLED;    // Toggle immediately
	layer_on(layer);
      } else if (get_mods() & MOD_MASK_ALT) {
	unregister_code16(KC_LALT);
	unregister_code16(KC_RALT);
	tap_code16(keycode);               // Tap immediately
      } else {
	ltt_state[layer] = LTT_TAPPING_ON; // Wait and see
	layer_on(layer);
      }
      break;
    case LTT_TOGGLED:
      ltt_state[layer] = LTT_INACTIVE;     // If toggled on, toggle off
      layer_off(layer);
      break;
    }
  } else {
    switch (ltt_state[layer]) {
    case LTT_TAPPING_ON:
    case LTT_TAPPED:
      if (keycode != KC_NO && ltt_state[layer] == LTT_TAPPING_ON) {
	tap_code16(keycode);              // Send the tap key
      }
      layer_off(layer);
      ltt_state[layer] = LTT_INACTIVE;
      break;
    case LTT_HOLDING:
      layer_off(layer);
      ltt_state[layer] = LTT_INACTIVE;   // Release the hold
      break;
    }
  }
  return false;
}

// Update the layer-tap-toggle state, but use an alternate layer if
// Ctrl is down.
//
bool layer_tap_toggle2(uint16_t keycode, uint8_t layer, uint8_t layer2, keyrecord_t *record) {
  if ((get_mods() & MOD_MASK_CTRL) || (get_highest_layer(layer_state) == layer2)) {
    return layer_tap_toggle(keycode, layer2, record);
  } else {
    return layer_tap_toggle(keycode, layer, record);
  }
}
