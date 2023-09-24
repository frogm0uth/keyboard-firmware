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
 * Caps word implementation using caps lock. Both shift keys turn on caps word, tap on either
 * turns it off. Can also use dedicated keys for caps word and caps lock. Won't work with one-shot
 * shift.
 */

#if !defined (CAPSWORD_TIMEOUT)
#   define CAPSWORD_TIMEOUT 300
#endif

// local vars
static bool     is_capsword      = false; // caps word is active if caps lock on
static bool     is_auto_unshift  = false; // next character cancels shift
static bool     capsword_waiting = false; // waiting to see if shift will be released
static uint16_t capsword_timer   = 0;

bool is_capsword_active() {
    return is_capsword && host_keyboard_led_state().caps_lock;
}

/**
 * Cancel shift to avoid accidental double upper-case. This effectively replaces one-shot
 * shift. It is always active but should probably be a compile option.
 */
bool process_auto_unshift(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && is_auto_unshift && (get_mods() & MOD_MASK_SHIFT)) {
        switch (keycode) {
            case KC_A ... KC_Z:
                register_code16(keycode);
                del_mods(MOD_MASK_SHIFT);
                return false;
                break;
        }
    }
    return true;
}

// Utility function to check if shift should be cancelled
bool check_auto_unshift() {
    return is_auto_unshift
        && (get_mods() & MOD_MASK_SHIFT);
}

// Time out caps word toggle
void capsword_tick() {
    if (capsword_waiting) {
        if (timer_elapsed(capsword_timer) > CAPSWORD_TIMEOUT) {
            capsword_waiting = false;
        }
    }
}

// Toggle caps-word
void toggle_capsword(void) {
    if (!host_keyboard_led_state().caps_lock) {
        is_capsword = true;
        tap_code(KC_CAPS);
    } else {
        if (is_capsword) {
            tap_code(KC_CAPS);
        } else {
            is_capsword = true;
        }
    }
    capsword_waiting = false;
}

// Toggle caps-lock
void toggle_capslock(void) {
    if (!host_keyboard_led_state().caps_lock) {
        is_capsword = false;
        tap_code(KC_CAPS);
    } else {
        if (!is_capsword) {
            tap_code(KC_CAPS);
        } else {
            is_capsword = false;
        }
    }
    capsword_waiting = false;
}

/**
 * Cancel caps-lock automatically if one of the specified keys matches
 */
void process_caps_cancel(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    bool cancel = false;

    if (record->event.pressed && is_capsword_active()) {
        if (mods & MOD_MASK_SHIFT) {
            switch (keycode) { // Keys that cancel caps lock only on shifted version
                case KC_1 ... KC_0:
                    cancel = true;
            }
        }
        if (!(mods & MOD_MASK_SHIFT)) {
            switch (keycode) { // Keys that cancel caps lock only on UNshifted version
                case CU_0 ... CU_9:
                     cancel = true;
           }
        }
        switch (keycode) {     // Keycodes that cancel caps word regardless of shift
            case KC_ENTER:
            case KC_ESCAPE:
            case KC_TAB:
            case KC_SPACE: // exclude KC_BACKSPACE

            case KC_EXCLAIM ... KC_RIGHT_PAREN:
            case KC_EQUAL ... KC_SEMICOLON: // exclude KC_QUOT
            case KC_GRAVE ... KC_SLASH:
            case KC_PLUS ... KC_QUESTION:

	        // add custom keycodes if needed here
                cancel = true;
        }
    }
    // cancel if a key was pressed that ... uh cancels it. If not, make sure that
    // the shift release doesn't accidentally cancel
    if (cancel) {
        tap_code(KC_CAPS);
    } else {
        switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            break;
        default:
            capsword_waiting = false;
            break;
        }
    }
}

/**
 * Turn caps modes on and off.
 */
bool process_record_capslock(uint16_t keycode, keyrecord_t *record) {

    // Handle caps lock switching. Pressing both shift keys toggles caps-word. Tapping either
    // shift key cancels caps word.
    //
    uint8_t mods = get_mods();

    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            if (record->event.pressed) {
                // Toggle caps word if a shift key is pressed while shift already active
                if (mods & MOD_MASK_SHIFT) {
                    toggle_capsword();
                    return false;

                } else {
                    if (host_keyboard_led_state().caps_lock) {
                        // Wait to see if this will cancel caps word
                        capsword_waiting = true;
                        capsword_timer = timer_read();
                    }
                    is_auto_unshift = true;
                    // Let QMK handle shift key down normally
                }
            } else {
                // cancel caps-word or caps lock if shift is released quickly
                if (capsword_waiting && host_keyboard_led_state().caps_lock) {
                    capsword_waiting = false;
                    tap_code(KC_CAPS);
                    // Let QMK handle shift key release normally
                }
            }
            break;

        case CU_SHIFT:
            if (record->event.pressed) {
                register_code16(KC_LSFT);
                is_auto_unshift = false;

                // Wait to see if this will toggle caps word
                capsword_waiting = true;
                capsword_timer = timer_read();

            } else {
                unregister_code16(KC_LSFT);

                // toggle caps-word if key is released quickly
                if (capsword_waiting) {
                    capsword_waiting = false;
                    toggle_capsword();
                }
            }
            return false;
            break;

        // Toggle caps word with dedicated key
        case CU_CAPSWORD:
            if (record->event.pressed) {
                toggle_capsword();
            }
            return false;
            break;

        // Toggle full caps lock with dedicated key
        case KC_CAPS:
            if (record->event.pressed) {
                toggle_capslock();
            }
            return false;
            break;

        default:
            if (capsword_waiting) {
                // Turn off wait for capsword
                capsword_waiting = false;
            }
            break;

    }
	return true;
}
