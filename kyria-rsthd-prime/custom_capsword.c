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


/**
 * Caps word implementation using caps lock
 */

#if !defined (CAPSWORD_TIMEOUT)
#   define CAPSWORD_TIMEOUT 300
#endif

// Caps word flag
static bool is_capsword = false;
bool is_capsword_active() {
    return is_capsword && host_keyboard_led_state().caps_lock;
}

// local vars
static bool     capsword_waiting = false; // waiting to see if shift will be released
static uint16_t capsword_timer   = 0;

// Time out caps word toggle
void capsword_tick() {
    if (capsword_waiting) {
        if (timer_elapsed(capsword_timer) > CAPSWORD_TIMEOUT) {
            capsword_waiting = false;
        }
    }
}


/**
 * Cancel caps-lock automatically if one of the specified keys matches
 */
void process_caps_cancel(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t ossmods = get_oneshot_mods();
#else
    uint8_t ossmods = mods;
#endif

    if (record->event.pressed && is_capsword_active()) {
        if ((mods | ossmods) & MOD_MASK_SHIFT) {
            switch (keycode) { // Keys that cancel caps lock only on shifted version
                case KC_1 ... KC_0:
                    tap_code(KC_CAPS);
            }
        }
        if (!((mods | ossmods) & MOD_MASK_SHIFT)) {
            switch (keycode) { // Keys that cancel caps lock only on UNshifted version
                case CU_0 ... CU_9:
                    tap_code(KC_CAPS);
            }
        }
        switch (keycode) {     // Keycodes that cancel caps lock regardless of shift
            case KC_ENTER:
            case KC_ESCAPE:
            case KC_TAB:
            case KC_SPACE:

            case KC_EXCLAIM ... KC_RIGHT_PAREN:
            case KC_EQUAL ... KC_SLASH:
            case KC_PLUS ... KC_QUESTION:

	        // add custom keycodes if needed here
                tap_code(KC_CAPS);
        }
    }
}

/**
 * Turn caps modes on and off.
 */
bool process_record_capslock(uint16_t keycode, keyrecord_t *record) {

    // Handle caps lock switching. Pressing both shift keys toggles capslock. Tapping either
    // shift key toggles caps word.
    //
    // One-shot shift used to cycle options but may not work right any more. It said: If shift keys
    // are one-shot shift, double-tap on one of them also turns on caps-word. Same again to turn
    // off, or type a non-word character such as space. Also turns off full caps lock.
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t ossmods = get_oneshot_mods();
#else
    uint8_t ossmods = mods;
#endif

    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            if (record->event.pressed) {
                // Toggle caps lock if a shift key is pressed while shift already active
                if ((mods | ossmods) & MOD_MASK_SHIFT) {
                    is_capsword = false;
                    capsword_waiting = false;
                    del_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_SHIFT);
#endif
                    tap_code(KC_CAPS);
                    return false;
                } else {
                    // Wait to see if this will toggle caps word
                    capsword_waiting = true;
                    capsword_timer = timer_read();
                    // Let QMK handle shift key down normally
                }
            } else {
                if (capsword_waiting) { // Toggle caps word
                    capsword_waiting = false;
                    is_capsword = true;
                    tap_code(KC_CAPS);
                    // Let QMK handle shift key release normally
                }
            }
            break;

        // Toggle caps word with dedicated key
        case CU_CAPSWORD:
            if (record->event.pressed) {
                if (!host_keyboard_led_state().caps_lock) {
                    is_capsword = true;
                }
            }
            break; // let QMK process

        // Toggle full caps lock with dedicated key
        case KC_CAPS:
            is_capsword = false;
            break; // let QMK process

        default:
            if (capsword_waiting) {
                // Turn off wait for capsword
                capsword_waiting = false;
            }
            break;

    }
	return true;
}
