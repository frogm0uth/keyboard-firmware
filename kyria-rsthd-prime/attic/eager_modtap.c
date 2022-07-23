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

/** Implementation of custom EMTs.
 */

#include "keymap.h"

// enum of modes for eager mod-tap
// clang-format off
enum emt_mode {
    EMT_WAITING,
    EMT_DECIDING,
    EMT_TAPPING,
    EMT_HOLDING
};
// clang-format on

// Define an enum of identifiers for eager mod-tap keys
//
#define DEFINE_EMT(layer, keycode, modmask) EMT_ID_##keycode,

// clang-format off
enum emt_ids {
#   include "emt_defs.h"
    EMT_INVALID
};
// clang-format on

// Define the data array describing eager mod-tap keys
// FIXME move to PROGMEM
#undef DEFINE_EMT
#define DEFINE_EMT(layer, keycode, modifier) {0, layer, keycode, modifier},

static emtnode_t emt_data[] = {
#include "emt_defs.h"
};

// variables
static uint16_t emt_deciding_timer = 0; // time since entering deciding mode
static uint16_t emt_tapping_timer  = 0; // time since most recent (non-modifier) key registration
static uint8_t  emt_mode           = EMT_WAITING;

#define EMT_MAX_SUSPENDED 10
static uint8_t emt_suspended[EMT_MAX_SUSPENDED]; // list of suspended mod-tap keys
static uint8_t emt_suspend_count = 0;            // number of suspended mod-tap keys
static uint8_t emt_held_count    = 0;            // number of held mod-tap keys


// Scan for a matching mod-tap. Return EMT_INVALID if not found, id if found.
//
uint8_t emt_scan(uint16_t keycode) {
    uint8_t layer = get_highest_layer(layer_state);

    for (int i = 0; i < EMT_INVALID; i++) {
        if (emt_data[i].layer == layer && emt_data[i].tapcode == keycode) {
            return i;
        }
    }
    return EMT_INVALID;
}

// Suspend a mod-tap key
void emt_suspend(uint8_t emtid) {
    emt_suspended[emt_suspend_count++] = emtid;
}

// Register the tap codes of all suspended mod-taps, and unsuspend them.
//
void emt_unsuspend_and_tap(keyrecord_t *record) {
    uint8_t emtid;
    for (int i = 0; i < emt_suspend_count; i++) {
        emtid = emt_suspended[i];
        register_code16(emt_data[emtid].tapcode); // FIXME allow custom keycodes
    }
    emt_suspend_count = 0;
}

// Register the hold codes of all suspended mod-taps, and unsuspend them.
//
void emt_unsuspend_and_hold(void) {
    uint8_t emtid;
    emt_held_count = emt_suspend_count;
    for (int i = 0; i < emt_suspend_count; i++) {
        emtid = emt_suspended[i];
        register_code16(emt_data[emtid].holdcode);
        emt_data[emtid].is_held = true;
    }
    emt_suspend_count = 0;
}

// Unregister a single held mod-tap key.
//
void emt_unregister_held_key(emtnode_t *emt, keyrecord_t *record) {
    unregister_code16(emt->holdcode);
    emt->is_held = false;
    emt_held_count--;
}

// Start waiting mode
void emt_start_waiting(void) {
    emt_mode = EMT_WAITING;
}

// Start deciding mode
void emt_start_deciding(uint16_t keycode, uint16_t emtid, keyrecord_t *record) {
    emt_suspend(emtid);
    emt_deciding_timer = timer_read();
    emt_mode           = EMT_DECIDING;
}

// Start tapping mode
void emt_start_tapping(uint16_t keycode, emtnode_t *emt, keyrecord_t *record) {
    emt_unsuspend_and_tap(record);
    emt_tapping_timer = timer_read();
    emt_mode          = EMT_TAPPING;
}

// Start holding mode
void emt_start_holding(void) {
    emt_unsuspend_and_hold();
    emt_mode = EMT_HOLDING;
}

// Register a key
void emt_register_key(uint16_t keycode, keyrecord_t *record) {
    register_code16(keycode); // FIXME custom keycodes
    emt_tapping_timer = timer_read();
}

// Unregister a key
void emt_unregister_key(uint16_t keycode, keyrecord_t *record) {
    unregister_code16(keycode); // FIXME custom keycodes
}

// Process an eager mod-tap key. Call from process_record_user().
//
bool process_record_emt(uint16_t keycode, keyrecord_t *record) {
    uint8_t    emtid     = emt_scan(keycode);
    bool       is_emtkey = emtid != EMT_INVALID;
    emtnode_t *emtnode   = is_emtkey ? &emt_data[emtid] : NULL;

    bool qmk_continue = true;   // True to continue normal processing after exit. Will
                                // be set false if a mod-tap key has been intercepted.

    switch (emt_mode) {
        case EMT_WAITING:
            // No action in this state

            if (record->event.pressed) {
                // Transition to deciding mode if an emt key is pressed
                if (is_emtkey) {
                    emt_start_deciding(keycode, emtid, record);
                    qmk_continue = false;
                }
#ifndef EMT_DISABLE_RULE_2
                // Transition to tapping mode if a regular key is pressed
                if (!is_emtkey) {
                    emt_start_tapping(keycode, NULL, record);
                    // qmk_continue = true; continue with further processing of non-EMT key
                }
#endif
            }
            break;

        case EMT_DECIDING:
            // There are several cases to handle. To avoid bugs, they are all just written out separately.
            if (is_emtkey) {
                if (record->event.pressed) {
                    // emt key pressed before combo term: suspend it and stay in deciding mode 
                    if (timer_elapsed(emt_deciding_timer) < EMT_EARLY_TERM) {
                        emt_suspend(emtid);
                        qmk_continue = false;
                    } else {
                        // emt key pressed after combo term: suspend it and switch to tapping mode
                        // (which will unsuspend it and register its tap code)
                        emt_suspend(emtid);
                        emt_start_tapping(keycode, emtnode, record);
                        qmk_continue = false;
                    }
                } else {
                    // emt key is released: switch to tapping mode which will register all the
                    // suspended tap codes. Then unregister the tap code of the released key
                    emt_start_tapping(keycode, emtnode, record);
                    emt_unregister_key(emtnode->tapcode, record);
                    qmk_continue = false;
                }
            } else {
                // Pressing a non-emt key puts us into tapping mode immediately. qmk_continue
                // remains true to handle the non-emt keypress 
                if (record->event.pressed) {
                    emt_start_tapping(keycode, NULL, record);
                    // qmk_continue = true; continue with further processing of non-EMT key
                }
            }
            // Another transition out of this mode, to holding mode, is only by timer - see emt_tick()
            break;

        case EMT_TAPPING:
            // Only handle EMT keys here to un/register the tap code
            if (is_emtkey) {
                if (record->event.pressed) {
                    emt_register_key(emtnode->tapcode, record);
                } else {
                    emt_unregister_key(emtnode->tapcode, record);
                }
                qmk_continue = false;
            } else {
                // We do want to restart the tapping mode timer though on every keypress
                if (record->event.pressed) {
                    emt_tapping_timer = timer_read();
                }
                // qmk_continue = true; continue with further processing of non-EMT key
            }
            // Transition out of this mode is only by timer - see emt_tick()
            break;

        case EMT_HOLDING:
            // Only handle EMT keys here to un/register the tap code. But if it's a held EMT being released,
            // unregister the hold code and check if it was the last one
            if (is_emtkey) {
                if (record->event.pressed) {
                    emt_register_key(emtnode->tapcode, record);
                } else {
                    if (emtnode->is_held) {
                        emt_unregister_held_key(emtnode, record); // This key is held, so unregister the *hold* code

                        // Transition back to waiting if that was the last held key being released
                        if (emt_held_count == 0) {
                            emt_start_waiting();
                        }

                    } else {
                        emt_unregister_key(emtnode->tapcode, record); // Unregister the tap code
                    }
                }
                qmk_continue = false; // Always halt processing if it's an EMT key

            } else {
                // We do want to restart the tapping mode timer though on every non-EMT keypress
                if (record->event.pressed) {
                    emt_tapping_timer = timer_read();
                }
                // qmk_continue = true; continue with further processing of non-EMT key
            }
            break;
    }
    return qmk_continue;
}

// Handle timing of EMTs
//
void emt_tick() {
    switch (emt_mode) {
        case EMT_DECIDING:
            // Transition to holding mode if timer has reached tapping_term since entering deciding mode
            if (timer_elapsed(emt_deciding_timer) > EMT_LATE_TERM) {
                emt_start_holding();
            }
            break;
        case EMT_TAPPING:
            // Transition to waiting mode if timer has reached tapping_term since last key registered
            if (timer_elapsed(emt_tapping_timer) > EMT_LATE_TERM) {
                emt_start_waiting();
            }
            break;
    }
}
