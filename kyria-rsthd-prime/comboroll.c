
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


/** Comboroll implementation. Comborolls are defined in combo_defs.h.
 *
 * Macros for combos adapted from:
 *
 * https://github.com/sevanteri/qmk_firmware/blob/9cca95785e6fd5001367d02fceddae628f6d48c9/users/sevanteri/combos.h
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/gboards/g/keymap_combo.h
 */

#include "config.h"
#include "keymap.h"

// Emit an array of keycodes
void process_combo_array(const uint16_t *keyptr) {
    while (*keyptr != KC_NO) {
        tap_code16(*keyptr++);
    }
}

// Emit a string, clear shift after first character
void process_combo_string(const char *str) {
    send_char(*str++);
    clear_mods();
    while (*str) {
        send_char(*str++);
    }
}

// Register a single key. Handles custom keycodes.
void register_combo_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        record->event.pressed = true;
        process_record_user_emit(keycode, record);
    } else {
        // Turn off caps lock at the end of a word
        process_caps_cancel(keycode, record);

        if (keycode == KC_CAPS) { // needs special treatment...
            tap_code16(keycode);
        } else {
            register_code16(keycode);
        }
    }
}

// Unregister a single key. Handles custom keycodes.
void unregister_combo_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        record->event.pressed = false;
        process_record_user_emit(keycode, record);
    } else {
        unregister_code16(keycode);
    }
}

// Tap a single key. Handles custom keycodes.
void tap_combo_key(uint16_t keycode, keyrecord_t *record) {
    register_combo_key(keycode, record);
    unregister_combo_key(keycode, record);
}

// clang-format off
#undef  ARRAY_PROTECT
#define ARRAY_PROTECT(...) __VA_ARGS__ 


/** Comboroll data/functions. This is my userspace implementation/variant of
 * combos triggered by rolling keys rather than keys pressed at the same
 * time. Since I started on this, QMK acquired the COMBO_MUST_PRESS_IN_ORDER
 * flag, which AFAIK does the same thing. However I've kept my version for now
 * as it's more space-efficent and the Pro Micro is *very* tight on space.
 *
 * Comborolls are defined by macros in combo_defs.h. There is a macro that
 * defines the trigger keys in both directions for cases where the direction of
 * the roll is not obvious, or for triggering from both hands or thumb keys when
 * you can't roll.  The time allowed to trigger a comboroll is relatively short
 * (between the QMK combo and tap-hold delay).
 */

// clang-format off



// Define the data arrays for array output comborolls
#define LtoR_ARR(name, out, k1, k2)    const uint16_t comboroll_array_##name[] = { out, KC_NO };
#define RtoL_ARR(name, out, k1, k2)    const uint16_t comboroll_array_##name[] = { out, KC_NO };
#define CMBO_ARR(name, out, k1, k2)    const uint16_t comboroll_array_##name[] = { out, KC_NO };

// Empty defs
#define LtoR_KEY(name, out, k1, k2)
#define LtoR_LIT(name, out, k1, k2)
#define LtoR_STR(name,      k1, k2)

#define RtoL_KEY(name, out, k1, k2)
#define RtoL_LIT(name, out, k1, k2)
#define RtoL_STR(name,      k1, k2)

#define CMBO_KEY(name, out, k1, k2)
#define CMBO_LIT(name, out, k1, k2)
#define CMBO_STR(name,      k1, k2)

#include "combo_defs.h"


// Define the array of comboroll nodes
#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_LIT
#undef  CMBO_STR

#define LtoR_KEY(name, out, k1, k2)     {comboroll_t_keycode, k1, k2, {.output_keycode=out}},
#define LtoR_ARR(name, out, k1, k2)     {comboroll_t_array,   k1, k2, {.output_array=comboroll_array_##name}},
#define LtoR_LIT(name, out, k1, k2)     {comboroll_t_string,  k1, k2, {.output_string=out}},
#define LtoR_STR(name,      k1, k2)     {comboroll_t_string,  k1, k2, {.output_string=#name}},

#define RtoL_KEY(name, out, k1, k2)     {comboroll_t_keycode, k2, k1, {.output_keycode=out}},
#define RtoL_ARR(name, out, k1, k2)     {comboroll_t_array,   k2, k1, {.output_array=comboroll_array_##name}},
#define RtoL_LIT(name, out, k1, k2)     {comboroll_t_string,  k2, k1, {.output_string=out}},
#define RtoL_STR(name,      k1, k2)     {comboroll_t_string,  k2, k1, {.output_string=#name}},

#define CMBO_KEY(name, out, k1, k2)     LtoR_KEY(name, out, k1, k2)   RtoL_KEY(name, out, k1, k2)
#define CMBO_ARR(name, out, k1, k2)     LtoR_ARR(name, out, k1, k2)   RtoL_ARR(name, out, k1, k2)
#define CMBO_LIT(name, out, k1, k2)     LtoR_LIT(name, out, k1, k2)   RtoL_LIT(name, out, k1, k2)
#define CMBO_STR(name,      k1, k2)     LtoR_STR(name,      k1, k2)   RtoL_STR(name,      k1, k2)

comboroll_t comborolls_data[] = {
#   include "combo_defs.h"
};

// clang-format on

// local vars
static bool        is_in_comboroll  = false;
static uint16_t    firstkey_matched = KC_NO;
static keyrecord_t firstkey_record;
static uint16_t    comboroll_timer = 0;

// Produce output for the given comboroll
void process_comboroll(comboroll_t *cr) {
    switch (cr->type) {
            // We have to do a tap for an output key. We can't register it, because we don't have a way to
            // remember it to unregister later. This is why we can't have hold type keys as combo
            // output. To be able to remember a held key, we would need a stack or list of active combos
            // (or something along those lines), as we could activate a second hold key while the first is
            // still active. Perhaps a single remembered combo would be enough, and any subsequent would
            // be forced to be a tap.
        case comboroll_t_keycode:
            tap_combo_key(cr->output_keycode, &firstkey_record);
            break;

        case comboroll_t_array:
            process_combo_array(cr->output_array);
            break;

        case comboroll_t_string:
            process_combo_string(cr->output_string);
            break;
    }
}

// Scan for match on first key
bool comboroll_scan_firstkey(uint16_t keycode) {
    comboroll_t *cr = comborolls_data;
    int          i;

    for (i = 0; i < sizeof comborolls_data / sizeof *comborolls_data; cr++, i++) {
        if (keycode == cr->firstkey) {
            return true;
        }
    }
    return false;
}

// Scan for match on second key
comboroll_t *comboroll_scan_secondkey(uint16_t firstkey, uint16_t secondkey) {
    comboroll_t *cr = comborolls_data;
    int          i;

    for (i = 0; i < sizeof comborolls_data / sizeof *comborolls_data; cr++, i++) {
        if (firstkey == cr->firstkey && secondkey == cr->secondkey) {
            return cr;
        }
    }
    return NULL;
}

// Process comboroll.
bool process_record_comboroll(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (is_in_comboroll) {
            is_in_comboroll = false;
            // Look for match on second key
            comboroll_t *second = comboroll_scan_secondkey(firstkey_matched, keycode);
            if (second) {
                process_comboroll(second);                                // matched second key, so emit the combo
                unregister_combo_key(firstkey_matched, &firstkey_record); // unregister first key prematurely to avoid hanging mods
                return false;                                             // no further processing

            } else {                                                    // no match
                register_combo_key(firstkey_matched, &firstkey_record); // register the first key
                                                                        // fall through to check for start of comboroll again
            }
        }
        // If still here, check for a match as first key
        if (comboroll_scan_firstkey(keycode)) {
            is_in_comboroll  = true;
            firstkey_record  = *record;
            firstkey_matched = keycode; // QMK doesn't use record->keycode - ?
            comboroll_timer  = timer_read();
            return false; // no further processing as we've held the key
        } else {
            return true; // let QMK handle the key as normal
        }
    } else {
        if (is_in_comboroll) {
            // If we're here, the first key was just released. So send it and cancel the combo
            tap_combo_key(firstkey_matched, &firstkey_record);
            is_in_comboroll = false;
            // not enirely sure why, but letting this fall through and have QMK also handle
	    // release of the key prevents stuck modifiers
        }
    }
    return true;
}

// Handle timing and output first key if too long for second. Must call from matrix_scan_user()
void comboroll_tick() {
    if (is_in_comboroll) {
        if (timer_elapsed(comboroll_timer) > COMBOROLL_TIMEOUT) {
            is_in_comboroll = false;
            register_combo_key(firstkey_matched, &firstkey_record); // register the first key
        }
    }
}