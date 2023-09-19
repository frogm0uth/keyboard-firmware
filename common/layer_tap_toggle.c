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
#include QMK_KEYBOARD_H

#include "keymap.h"

/**
 * Layer-tap-toggle. Layer active while held, Tap to send some other key. Note: auto-repeat not
 * implemented. Has functinos to support custom keys to lock the layer (toggle it on) and return to
 * the base layer.  The main entry is layer_tap_toggle() which should be called from
 * process_record_user.. A second entry is layer_tap_toggle2, which will activate a different layer
 * if Alt is held.
 *
 * This is used instead of the QMK layer-tap functionality to a. support shifted and custom keys and
 * b. because QMK layer-tap doesn't activate the layer until the end of the tapping term, which
 * makes it hard to quickly press a key on a layer.
 */

// State of the layer-tap-toggle for a single layer
// clang-format off
enum {
    LTT_INACTIVE,
    LTT_TAPPING,
    LTT_HOLDING,
    LTT_TOGGLED
};
// clang-format on

// State arrays, one element per layer
static uint16_t ltt_timer[NUM_LAYERS];
static uint8_t  ltt_state[NUM_LAYERS];
static bool     ltt_initialized = false;

// record in case needed for rolling shift
static uint16_t    ltt_keycode;
static keyrecord_t ltt_record;


/**
 * Update the timer(s) for layer-tap-toggle. Must be called from
 * matrix_scan_user.
 */
void ltt_tick(void) {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        if (ltt_state[layer] == LTT_TAPPING) {
            if (timer_elapsed(ltt_timer[layer]) > TAPPING_TERM) {
                ltt_state[layer] = LTT_HOLDING; // Go to holding state when timer expires
            }
        }
    }
}

/**
 * Check for key interrupt. Call this from process_record_user for keys
 * pressed. This prevents false hits if the layer key and another are pressed
 * within the tapping term. Also handles rolling shift.
 */
void ltt_interrupt(uint16_t keycode, keyrecord_t *record) {
    layer_state_t layer = get_highest_layer(layer_state);
    if (record->event.pressed) {
        if (ltt_state[layer] == LTT_TAPPING) {
            ltt_state[layer] = LTT_HOLDING; // Go to holding state on any keypress
        }
    } else {
        if ((ltt_state[layer] == LTT_TAPPING) && (keycode == KC_LSFT || keycode == KC_RSFT)) {
            // handle rolling shift case
            tap_custom_key(ltt_keycode, &ltt_record);
            ltt_state[layer] = LTT_INACTIVE;
            layer_off(layer);
            // let QMK handle shift release
        }
    }
}

/**
 * Go back to the base layer. Call this from process_record_user() in response
 * to a custom keycode.
 */
bool ltt_base(void) {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        ltt_state[layer] = LTT_INACTIVE;
    }
    layer_clear();
    return false;
}

/**
 * Lock the layer on if it's being held. If it's already toggled, turn it off.
 * Call this from process_record_user() in response to a lock keypress.
 */
bool ltt_lock(keyrecord_t *record) {
    layer_state_t layer = get_highest_layer(layer_state);
    if (record->event.pressed) {
        switch (ltt_state[layer]) {
            case LTT_TAPPING:
            case LTT_HOLDING:
                ltt_state[layer] = LTT_TOGGLED; // Lock it on
                break;
            case LTT_TOGGLED:
                ltt_state[layer] = LTT_INACTIVE; // If toggled on, toggle off
                layer_off(layer);
                break;
        }
    }
    return false;
}

/**
 * Update the layer-tap-toggle state. Must be called from process_record_user().
 * Pass KC_NO if you don't want tap to send a key.
 *
 * Always returns false.
 */
bool layer_tap_toggle(uint16_t keycode, uint8_t layer, keyrecord_t *record) {
    if (!ltt_initialized) { // Make sure state array is a known state
        ltt_base();
        ltt_initialized = true;
    }
    if (record->event.pressed) {
        ltt_timer[layer] = timer_read();
        switch (ltt_state[layer]) {
            case LTT_INACTIVE:
                ltt_state[layer] = LTT_TAPPING; // Wait and see
                ltt_keycode = keycode; // record in case needed for rolling shift
                ltt_record = *record;
                layer_on(layer);
                break;
            case LTT_TOGGLED:
                ltt_state[layer] = LTT_INACTIVE; // If toggled on, toggle off
                layer_off(layer);
                break;
        }
    } else {
        switch (ltt_state[layer]) {
            case LTT_TAPPING:
                // tap the key
                tap_custom_key(keycode, record);
                // fall through
            case LTT_HOLDING:
                layer_off(layer);
                ltt_state[layer] = LTT_INACTIVE; // Release the hold
                break;
        }
    }
    return false;
}

/**
 * Update the layer-tap-toggle state, but use an alternate layer if Alt is
 * down.
 */
bool layer_tap_toggle2(uint16_t keycode, uint8_t layer, uint8_t layer2, keyrecord_t *record) {
    if (record->event.pressed) {
        if (get_mods() & MOD_MASK_ALT) {
            return layer_tap_toggle(keycode, layer2, record);
        } else {
            return layer_tap_toggle(keycode, layer, record);
        }
    } else {
        if (get_highest_layer(layer_state) == layer2) {
            return layer_tap_toggle(keycode, layer2, record);
        } else {
            return layer_tap_toggle(keycode, layer, record);
        }
    }
}
