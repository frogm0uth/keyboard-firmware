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

/** Comboroll implementation. Comborolls are defined in combo_defs.h.
 *
 * This is my userspace implementation/variant of combos triggered by rolling
 * keys rather than keys pressed at the same time. This is an alternative to
 * QMK combos that handles "rolling" combos better. It's also more
 * space-efficient (about 2kbytes with ~40 combos), which helps if space is
 * tight.
 */

#include "config.h"
#include "keymap.h"

// clang-format off
#undef  ARRAY_PROTECT
#define ARRAY_PROTECT(...) __VA_ARGS__ 

// Define QMK combo macros as empty
#define Q_LtoR_KEY(name, ...)
#define Q_LtoR_ARR(name, ...)
#define Q_LtoR_LIT(name, ...)
#define Q_LtoR_STR(name, ...)
#define Q_LtoR_TRM(name, ...)

#define Q_RtoL_KEY(name, ...)
#define Q_RtoL_ARR(name, ...)
#define Q_RtoL_LIT(name, ...)
#define Q_RtoL_STR(name, ...)
#define Q_RtoL_TRM(name, ...)

#define Q_CMBO_KEY(name, ...)
#define Q_CMBO_ARR(name, ...)
#define Q_CMBO_LIT(name, ...)
#define Q_CMBO_STR(name, ...)
#define Q_CMBO_TRM(name, ...)


// Empty until the last definition
#define CMBO_TRM(name, ms)
#define RtoL_TRM(name, ms)
#define LtoR_TRM(name, ms)
#define _ONSHIFT(name)


// Define an enum of identifiers.
#define LtoR_KEY(name, ...) COMBOROLL_ID_##name,
#define LtoR_ARR LtoR_KEY
#define LtoR_LIT LtoR_KEY
#define LtoR_STR LtoR_KEY

#define RtoL_KEY LtoR_KEY
#define RtoL_ARR LtoR_KEY
#define RtoL_LIT LtoR_KEY
#define RtoL_STR LtoR_KEY

#define CMBO_KEY LtoR_KEY
#define CMBO_ARR LtoR_KEY
#define CMBO_LIT LtoR_KEY
#define CMBO_STR LtoR_KEY

enum comboroll_ids {
#   include "combo_defs.h"
    COMBOROLL_COUNT
};


// Define the data arrays and output strings
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

#define LtoR_KEY(name, out, k1, k2)
#define LtoR_ARR(name, out, k1, k2)  const uint16_t PROGMEM comboroll_array_##name[] = { out, KC_NO };
#define LtoR_LIT(name, out, k1, k2)  const char PROGMEM comboroll_string_##name[] = out;
#define LtoR_STR(name,      k1, k2)  const char PROGMEM comboroll_string_##name[] = #name;

#define RtoL_KEY LtoR_KEY
#define RtoL_ARR LtoR_ARR
#define RtoL_LIT LtoR_LIT
#define RtoL_STR LtoR_STR

#define CMBO_KEY LtoR_KEY
#define CMBO_ARR LtoR_ARR
#define CMBO_LIT LtoR_LIT
#define CMBO_STR LtoR_STR

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

#define LtoR_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_LEFT, 0, COMBOROLL_TERM, {.output_keycode=out}},
#define LtoR_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_LEFT, 0, COMBOROLL_TERM, {.output_array=comboroll_array_##name}},
#define LtoR_LIT(name, out, k1, k2) {comboroll_t_literal, CMB_MATCH_LEFT, 0, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},
#define LtoR_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_LEFT, 0, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},

#define RtoL_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_RIGHT, 0, COMBOROLL_TERM, {.output_keycode=out}},
#define RtoL_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_RIGHT, 0, COMBOROLL_TERM, {.output_array=comboroll_array_##name}},
#define RtoL_LIT(name, out, k1, k2) {comboroll_t_literal, CMB_MATCH_RIGHT, 0, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},
#define RtoL_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_RIGHT, 0, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},

#define CMBO_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_BOTH, 0, COMBO_TERM, {.output_keycode=out}},
#define CMBO_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_BOTH, 0, COMBO_TERM, {.output_array=comboroll_array_##name}},
#define CMBO_LIT(name, out, k1, k2) {comboroll_t_literal, CMB_MATCH_BOTH, 0, COMBO_TERM, {.output_string=comboroll_string_##name}},
#define CMBO_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_BOTH, 0, COMBO_TERM, {.output_string=comboroll_string_##name}},

comboroll_t comboroll_data[] = {
#   include "combo_defs.h"
};

// Define the array of trigger keys
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

#define LtoR_KEY(name, out, k1, k2) {k1, k2},
#define LtoR_ARR(name, out, k1, k2) {k1, k2},
#define LtoR_LIT(name, out, k1, k2) {k1, k2},
#define LtoR_STR(name,      k1, k2) {k1, k2},

#define RtoL_KEY(name, out, k1, k2) {k1, k2},
#define RtoL_ARR(name, out, k1, k2) {k1, k2},
#define RtoL_LIT(name, out, k1, k2) {k1, k2},
#define RtoL_STR(name,      k1, k2) {k1, k2},

#define CMBO_KEY(name, out, k1, k2) {k1, k2},
#define CMBO_ARR(name, out, k1, k2) {k1, k2},
#define CMBO_LIT(name, out, k1, k2) {k1, k2},
#define CMBO_STR(name,      k1, k2) {k1, k2},

const uint16_t PROGMEM comboroll_keys[][2] = {
#   include "combo_defs.h"
};

#define CMB_KEY_1(id) (pgm_read_word(&comboroll_keys[id][0]))
#define CMB_KEY_2(id) (pgm_read_word(&comboroll_keys[id][1]))

// Initialize terms with any exceptions
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

#define LtoR_KEY(name, ...)
#define LtoR_ARR(name, ...)
#define LtoR_LIT(name, ...)
#define LtoR_STR(name, ...)

#define RtoL_KEY(name, ...)
#define RtoL_ARR(name, ...)
#define RtoL_LIT(name, ...)
#define RtoL_STR(name, ...)

#define CMBO_KEY(name, ...)
#define CMBO_ARR(name, ...)
#define CMBO_LIT(name, ...)
#define CMBO_STR(name, ...)

void comboroll_post_init() {
#undef  RtoL_TRM
#undef  LtoR_TRM
#define RtoL_TRM(name, targ) comboroll_data[COMBOROLL_ID_##name].term = targ;
#define LtoR_TRM RtoL_TRM

#ifndef COMBO_ENABLE
    #undef  CMBO_TRM
    #define CMBO_TRM RtoL_TRM
#endif

#undef  _ONSHIFT
#define _ONSHIFT(name) comboroll_data[COMBOROLL_ID_##name].onshift = 1;

#include "combo_defs.h"
}

// clang-format on

// local vars
static bool        is_in_comboroll  = false;
static uint16_t    firstkey_matched = KC_NO;
static uint8_t     firstkey_shiftmask = 0;
static keyrecord_t firstkey_record;
static uint16_t    comboroll_timer        = 0;
static uint16_t    comboroll_longest_term = 0;

// Produce output for the given comboroll
void process_comboroll(comboroll_t *cr) {
    uint8_t mods = get_mods();

    // All types of comboroll except string ignore shift
    if (cr->type != comboroll_t_string) {
        del_mods(MOD_MASK_SHIFT);
    }
    // Process by comboroll type.
    // We have to do a tap for output keys. We can't register them, because we don't have a
    // way to remember it to unregister later. This is why we can't have hold type keys as
    // combo output.
    switch (cr->type) {
        uint16_t rc;
        case comboroll_t_keycode:
            // Repeat is done in tap_custom_key()
            tap_custom_key(cr->output_keycode, &firstkey_record);
            break;

        default:
            // Repeat the output if the repeat key has been pressed
            rc = capture_repeat_count();
            do {
                switch (cr->type) {
                    case comboroll_t_array:
                        emit_progmem_array_record(cr->output_array, &firstkey_record);
                        break;

                    case comboroll_t_literal:
                        emit_progmem_string(cr->output_string);
                        break;

                    case comboroll_t_string:
                        emit_progmem_string_autounshift(cr->output_string); // string type uses auto-unshift
                        break;
                }
            } while (rc--);
            break;
    }
    // Restore mods for every comboroll type except strings
    if (cr->type != comboroll_t_string) {
        set_mods(mods);
    }
}

// Scan for match on first key. Return true on success, and comboroll_longest_term is set
// to the highest term of possible matches. Shift keys never match. If the combo has 
// been tagged with _ONSHIFT and shift is not on then it won't match.
bool comboroll_scan_firstkey(uint16_t keycode) {
    bool found = false;

    if (keycode == KC_LSFT || keycode == KC_RSFT) {
        return false;
    }
    comboroll_longest_term = 0;
    for (int i = 0; i < COMBOROLL_COUNT; i++) {
        if (
            ((CMB_IS_MATCHES_LEFT(comboroll_data[i].direction) && keycode == CMB_KEY_1(i))
            || (CMB_IS_MATCHES_RIGHT(comboroll_data[i].direction) && keycode == CMB_KEY_2(i)))
            && !(!(get_mods() & MOD_MASK_SHIFT) && comboroll_data[i].onshift)
            ) {

            found = true;
            if (comboroll_data[i].term > comboroll_longest_term) {
                comboroll_longest_term = comboroll_data[i].term;
            }
            // don't break here - need to keep going to find the longest term for
            // any combo that starts with this letter
        }
    }
    return found;
}

// Scan for match on second key. If a match is found, AND the elapsed time since the first key was
// pressed is less than its term, return the pointer to the comboroll_t struct. Otherwise return
// NULL. Shift keys never match.
comboroll_t *comboroll_scan_secondkey(uint16_t firstkey, uint16_t secondkey) {
    comboroll_t *result = NULL;

    if (secondkey == KC_LSFT || secondkey == KC_RSFT) {
        return NULL;
    }
    for (int i = 0; i < COMBOROLL_COUNT; i++) {
        if (
            (CMB_IS_MATCHES_LEFT(comboroll_data[i].direction) && firstkey == CMB_KEY_1(i) && secondkey == CMB_KEY_2(i))
            || (CMB_IS_MATCHES_RIGHT(comboroll_data[i].direction) && firstkey == CMB_KEY_2(i) && secondkey == CMB_KEY_1(i))) {

	        if (timer_elapsed(comboroll_timer) <= comboroll_data[i].term) { // don't match combo if it took too long
                result = &comboroll_data[i];
            }
            break;
        }
    }
    return result;
}

// Process comboroll. Call from process_record_user().
//
bool process_record_comboroll(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Key press
        if (is_in_comboroll) {
            is_in_comboroll = false;
            // Look for match on second key
            comboroll_t *second = comboroll_scan_secondkey(firstkey_matched, keycode);
            if (second) {
                add_mods(firstkey_shiftmask);       // Set shift how it was when the first key was pressed
                process_comboroll(second);          // matched second key, so emit the combo
                cancel_capsword_tap_timer();        // Cancel the caps-word timer in case shift is down, so
                                                    // it can't activate if subsequently released quickly enough

                return false;                       // no further processing

            } else {                                                       // no match
                add_mods(firstkey_shiftmask);                              // Set shift how it was when the first key was pressed
                tap_custom_key(firstkey_matched, &firstkey_record);        // tap the first key
                                                                           // fall through to check for start of comboroll again
            }
        }
        // If still here, check for a match as first key
        if (comboroll_scan_firstkey(keycode)) {
            is_in_comboroll  = true;
            firstkey_record  = *record;      // Make a copy of the record for later use
            firstkey_matched = keycode;      // QMK doesn't use record->keycode - ?
            firstkey_shiftmask = get_mods() & MOD_MASK_SHIFT; // Record if shifted when the first key is pressed
            comboroll_timer  = timer_read(); // Restart the timer
            return false;                    // no further processing as we've held the key
        } else {
            return true; // let QMK handle the key as normal
        }
    } else {
        // Key release
        if (is_in_comboroll) {
            // If we're here, check to see if it was the first key that was just released. If so,
            // send it and cancel the wait for combo
            if (keycode == firstkey_matched) {
                add_mods(firstkey_shiftmask);  // Set shift how it was when the first key was pressed
                tap_custom_key(firstkey_matched, &firstkey_record);
                is_in_comboroll = false;
	            return false;
            } else if (keycode == KC_LSFT || keycode == KC_RSFT) {

                // If shift was just released, cancel the caps-word tap timer so it can't
                // activate
                cancel_capsword_tap_timer();

                // For good measure, deregister the shift here and don't let it propagate
                unregister_code16(keycode);
                return false;
            }
        }
    }
    return true;
}

// Handle timing and output first key if too long for second. Must call from matrix_scan_user()
//
void comboroll_tick() {
    if (timer_elapsed(comboroll_timer) > comboroll_longest_term) {
        cancel_comboroll();
    }
}


// Cancel a pending comboroll (if there is one)
//
void cancel_comboroll() {
    if (is_in_comboroll) {
        is_in_comboroll = false;
        add_mods(firstkey_shiftmask);  // Set shift how it was when the first key was pressed
        register_custom_key(firstkey_matched, &firstkey_record); // register the first key
    }
}


