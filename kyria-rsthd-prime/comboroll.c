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
 * This is my userspace implementation/variant of combos triggered by rolling keys rather than keys
 * pressed at the same time. Since I started on this, two things happened: QMK acquired the
 * COMBO_MUST_PRESS_IN_ORDER flag, which does the same thing; and I've made the implementation able
 * to handle keys pressed in either order. So basically either can work, and combo_defs.h can be
 * compiled for either. The issue I've had with the QMK combos is that overlapping combos trigger
 * the second one, which is not what I want. There's a #define that can turn it off but also
 * requires that you release quickly. Also, this implmentation is more space-efficient (about
 * 2kbytes with ~40 combos).
 */

#include "config.h"
#include "keymap.h"

// Emit an array of keycodes
void process_comboroll_array(const uint16_t *keyptr) {
    uint16_t keycode = pgm_read_word(keyptr++);
    while (keycode != KC_NO) {
        tap_code16(keycode);
        keycode = pgm_read_word(keyptr++);
    }
}

// Emit a PROGMEM string, clear shift after first character
void process_comboroll_string(const char *str) {
    char ch = pgm_read_byte(str++);
    send_char(ch);
    clear_mods();
    while (ch) {
        ch = pgm_read_byte(str++);
        send_char(ch);
    }
}

// Register a single key. Handles custom keycodes.
void register_comboroll_key(uint16_t keycode, keyrecord_t *record) {
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
void unregister_comboroll_key(uint16_t keycode, keyrecord_t *record) {
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        record->event.pressed = false;
        process_record_user_emit(keycode, record);
    } else {
        unregister_code16(keycode);
    }
}

// Tap a single key. Handles custom keycodes.
void tap_comboroll_key(uint16_t keycode, keyrecord_t *record) {
    register_comboroll_key(keycode, record);
    unregister_comboroll_key(keycode, record);
}

// clang-format off
#undef  ARRAY_PROTECT
#define ARRAY_PROTECT(...) __VA_ARGS__ 


// clang-format off

// This is empty until the last definition
#define _____TRM(name, term)


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

#define LtoR_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_LEFT, COMBOROLL_TERM, {.output_keycode=out}},
#define LtoR_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_LEFT, COMBOROLL_TERM, {.output_array=comboroll_array_##name}},
#define LtoR_LIT(name, out, k1, k2) {comboroll_t_string,  CMB_MATCH_LEFT, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},
#define LtoR_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_LEFT, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},

#define RtoL_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_RIGHT, COMBOROLL_TERM, {.output_keycode=out}},
#define RtoL_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_RIGHT, COMBOROLL_TERM, {.output_array=comboroll_array_##name}},
#define RtoL_LIT(name, out, k1, k2) {comboroll_t_string,  CMB_MATCH_RIGHT, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},
#define RtoL_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_RIGHT, COMBOROLL_TERM, {.output_string=comboroll_string_##name}},

#define CMBO_KEY(name, out, k1, k2) {comboroll_t_keycode, CMB_MATCH_BOTH, COMBO_TERM, {.output_keycode=out}},
#define CMBO_ARR(name, out, k1, k2) {comboroll_t_array,   CMB_MATCH_BOTH, COMBO_TERM, {.output_array=comboroll_array_##name}},
#define CMBO_LIT(name, out, k1, k2) {comboroll_t_string,  CMB_MATCH_BOTH, COMBO_TERM, {.output_string=comboroll_string_##name}},
#define CMBO_STR(name,      k1, k2) {comboroll_t_string,  CMB_MATCH_BOTH, COMBO_TERM, {.output_string=comboroll_string_##name}},


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
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, ...)
#define CMBO_ARR(name, ...)
#define CMBO_LIT(name, ...)
#define CMBO_STR(name, ...)

#define LtoR_KEY(name, ...)
#define LtoR_ARR(name, ...)
#define LtoR_LIT(name, ...)
#define LtoR_STR(name, ...)

#define RtoL_KEY(name, ...)
#define RtoL_ARR(name, ...)
#define RtoL_LIT(name, ...)
#define RtoL_STR(name, ...)

#undef  _____TRM
#define _____TRM(name, targ) comboroll_data[COMBOROLL_ID_##name].term = targ;

void comboroll_post_init() {
#   include "combo_defs.h"
}

// clang-format on

// local vars
static bool        is_in_comboroll  = false;
static uint16_t    firstkey_matched = KC_NO;
static keyrecord_t firstkey_record;
static uint16_t    comboroll_timer        = 0;
static uint16_t    comboroll_longest_term = 0;

// Produce output for the given comboroll
void process_comboroll(comboroll_t *cr) {
    switch (cr->type) {
            // We have to do a tap for an output key. We can't register it, because we don't have a
            // way to remember it to unregister later. This is why we can't have hold type keys as
            // combo output. To be able to remember a held key, we would need a stack or list of
            // active combos (or something along those lines).
        case comboroll_t_keycode:
            tap_comboroll_key(cr->output_keycode, &firstkey_record);
            break;

        case comboroll_t_array:
            process_comboroll_array(cr->output_array);
            break;

        case comboroll_t_string:
            process_comboroll_string(cr->output_string);
            break;
    }
}

// Scan for match on first key. Return true on success, and comboroll_longest_term is set
// to the highest term of possible matches
bool comboroll_scan_firstkey(uint16_t keycode) {
  //comboroll_t *cr = comboroll_data;
    bool         found = false;

    comboroll_longest_term = 0;
    for (int i = 0; i < COMBOROLL_COUNT; i++) {
        if (
            (CMB_IS_MATCHES_LEFT(comboroll_data[i].direction) && keycode == CMB_KEY_1(i))
            || (CMB_IS_MATCHES_RIGHT(comboroll_data[i].direction) && keycode == CMB_KEY_2(i))) {

            found = true;
            if (comboroll_data[i].term > comboroll_longest_term) {
                comboroll_longest_term = comboroll_data[i].term;
            }
        }
    }
    return found;
}

// Scan for match on second key. If a match is found, AND the elapsed time since the first key was
// pressed is less than its term, return the pointer to the comboroll_t struct. Otherwise return
// NULL.
comboroll_t *comboroll_scan_secondkey(uint16_t firstkey, uint16_t secondkey) {
  //comboroll_t *cr = comboroll_data;
    comboroll_t *result = NULL;

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
        if (is_in_comboroll) {
            is_in_comboroll = false;
            // Look for match on second key
            comboroll_t *second = comboroll_scan_secondkey(firstkey_matched, keycode);
            if (second) {
                process_comboroll(second);                                    // matched second key, so emit the combo
                unregister_comboroll_key(firstkey_matched, &firstkey_record); // unregister first key prematurely to avoid hanging mods
                return false;                                                 // no further processing

            } else {                                                        // no match
                register_comboroll_key(firstkey_matched, &firstkey_record); // register the first key
                                                                            // fall through to check for start of comboroll again
            }
        }
        // If still here, check for a match as first key
        if (comboroll_scan_firstkey(keycode)) {
            is_in_comboroll  = true;
            firstkey_record  = *record;      // Make a copy of the record for later use
            firstkey_matched = keycode;      // QMK doesn't use record->keycode - ?
            comboroll_timer  = timer_read(); // Restart the timer
            return false;                    // no further processing as we've held the key
        } else {
            return true; // let QMK handle the key as normal
        }
    } else {
        if (is_in_comboroll) {
            // If we're here, check to see if it was the first key that was just released. If so,
            // send it and cancel the combo
            if (keycode == firstkey_matched) {
                tap_comboroll_key(firstkey_matched, &firstkey_record);
                is_in_comboroll = false;
                // not entirely sure why, but letting this fall through and have QMK also handle
                // release of the key seems to prevent stuck modifiers
            }
        }
    }
    return true;
}

// Handle timing and output first key if too long for second. Must call from matrix_scan_user()
//
void comboroll_tick() {
    if (is_in_comboroll) {
        if (timer_elapsed(comboroll_timer) > comboroll_longest_term) {
            is_in_comboroll = false;
            register_comboroll_key(firstkey_matched, &firstkey_record); // register the first key
        }
    }
}
