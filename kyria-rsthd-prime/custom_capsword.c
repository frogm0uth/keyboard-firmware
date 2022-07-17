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

// Caps word flag
static bool bool_capsword = false;
bool is_capsword() {
    return bool_capsword;
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

    if (bool_capsword && host_keyboard_led_state().caps_lock && record->event.pressed) {
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
 * Toggle caps lock and caps word
 */
bool process_record_capsword(uint16_t keycode, keyrecord_t *record) {

    // Handle caps lock switching. Pressing both shift keys turns on caps-word. If the shift keys
    // are one-shot shift, double-tap on one of them also turns on caps-word. Same again to turn
    // off, or type a non-word character such as space. Also turns off full caps lock.
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t ossmods = get_oneshot_mods();
#else
    uint8_t ossmods = mods;
#endif

    switch (keycode) {
        case CU_LSFT:
        case CU_RSFT:
            if (record->event.pressed) {
                if ((mods | ossmods) & MOD_MASK_SHIFT) {
                    bool_capsword = true;
                    del_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_SHIFT);
#endif
                    tap_code(KC_CAPS);
                    return false;
                }
            }
            break;
        // Toggle full caps lock
        case KC_CAPS:
        case ALT_T(KC_CAPS):
            bool_capsword = false;
            break; // let QMK process

        // Monitor mod-taps to check for cancel caps-word
        case ALT_T(KC_TAB):
        case GUI_T(KC_TAB):
            if (record->event.pressed && record->tap.count) {
                process_caps_cancel(KC_TAB, record);
            }
            break; // let QMK process otherwise
    }
	return true;
}
