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


/****
 * Functions for processing keycodes
 */


// Register a single key. Handles custom keycodes.
void register_custom_key(uint16_t keycode, keyrecord_t *record) {
    record->event.pressed = true; // force it on
    // Process the keycode so that custom codes work
    while (repeat_that_output()) {
        // if we are repeating a key, do extra events - register
        if (process_record_user_emit(keycode, record)) {
            if (keycode < QK_USER) { // in case of lax return values from previous call
                register_code16(keycode);
            }
        }
        record->event.pressed = false; // unregister
        if (process_record_user_emit(keycode, record)) {
            if (keycode < QK_USER) { // in case of lax return values from previous call
                unregister_code16(keycode);
            }
        }
        record->event.pressed = true; // force it on
    }
    if (process_record_user_emit(keycode, record)) {
        if (keycode < QK_USER) { // in case of lax return values from previous call
            register_code16(keycode);
        }
    }
}

// Unregister a single key. Handles custom keycodes.
void unregister_custom_key(uint16_t keycode, keyrecord_t *record) {
    record->event.pressed = false; // force it off
    if (process_record_user_emit(keycode, record)) {
        if (keycode < QK_USER) {
            unregister_code16(keycode);
        }
    }
}

// Tap a single key. Handles custom keycodes.
void tap_custom_key(uint16_t keycode, keyrecord_t *record) {
    register_custom_key(keycode, record);
    unregister_custom_key(keycode, record);
}

/**
 * Process keys with a custom shift value. Shift codes are defined in shift_defs.h.
 */
// clang-format off
#undef  DEFINE_SHIFT
#define DEFINE_SHIFT(name, normal, shifted) [name - SHIFT_ID_START] = {normal, shifted},

const uint16_t PROGMEM shift_keycodes[][2] = {
    DEFINE_SHIFT(SHIFT_ID_START, KC_NO, KC_NO)
#   include "../common/shift_defs.h"
    DEFINE_SHIFT(SHIFT_ID_END, KC_NO, KC_NO)
};
#define READ_SHIFT_KEY(k, i) (pgm_read_word(&shift_keycodes[k - SHIFT_ID_START][i]))
// clang-format on

// Process a single custom shift key based on passed values
void process_shift_key(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t mods = get_mods();
        del_mods(MOD_MASK_SHIFT);
        register_custom_key(mods & MOD_MASK_SHIFT ? shiftedkey : key, record);
        set_mods(mods);
    } else {
        unregister_custom_key(key, record);
        unregister_custom_key(shiftedkey, record);
    }
}

// Process a single custom shift key based on the keycode
bool process_custom_shift(uint16_t key, keyrecord_t *record) {
    if (key > SHIFT_ID_START && key < SHIFT_ID_END) {
        process_shift_key(READ_SHIFT_KEY(key, 0), READ_SHIFT_KEY(key, 1), record);
        return false;
    }
    return true;
}

/**
 * User-level processing of custom keycodes, for those that might output characters.
 * This is split out from process_record_user so that it can be called from other
 * places (via tap_custom_key()).
 */
bool process_record_user_emit(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();

#ifdef CUSTOM_CAPSWORD
    // Toggle caps lock.
    if (!process_record_capslock(keycode, record)) {
        return false;
    }
#endif

#ifdef CUSTOM_CAPSWORD
    // Check for capsword cancel
    process_caps_cancel(keycode, record);
#endif

    // Process custom shift keys
    if (!process_custom_shift(keycode, record)) {
        return false;
    }

    // Process OS shortcut keycodes
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    if (!process_record_shortcut(keycode, record)) {
        return false;
    }
#endif

    // Process custom editing keycodes
#ifdef CUSTOM_EDIT
    if (!custom_edit_process_record(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
#ifdef LAYER_TAP_TOGGLE
            // layer switching using layer-tap-toggle custom code
#ifdef E_ON_LEFT_THUMB
        case CL_SYMS:
            return layer_tap_toggle(KC_ENTER, SYMS, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(KC_TAB, EDIT, record);
            break;
#else
        case CL_SYMS:
            return layer_tap_toggle(KC_TAB, SYMS, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(KC_ENTER, EDIT, record);
            break;
#endif
        case CL_META:
            return layer_tap_toggle(KC_TAB, META, record);
            break;

        case CL_META_R:
            return layer_tap_toggle(KC_ENTER, META, record);
            break;

        case CL_FUNC:
            return layer_tap_toggle(KC_NO, FUNC, record);
            break;

        case CL_SNAP:
            return layer_tap_toggle(KC_NO, SNAP, record);
            break;
#else
            // layer switching using QMK layer-tap: handle cases where tap code is 16-bit or has custom shift
        //case CL_SYMS:
        //    if (record->tap.count) {
        //        process_shift_key(KC_DQUO, KC_DQUO, record);
        //        return false;
        //    }
        //    break;
#endif

            /*  Emit custom keycodes.
             */
        case CU_DIRUP:
            if (record->event.pressed) {
                clear_mods();
                tap_code(KC_DOT);
                tap_code(KC_DOT);
                tap_code(KC_SLSH);
            }
            return false;
            break;

        case CU_SPCR:
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
            return false;
            break;

            /* Switch between applications (like Alt-Tab on Windows or Cmd-Tab on macOS) This must be triggered from
             * a layer so the release event is called from layer_state_set_user() when the layer is released.
             */
#ifdef APP_SWITCHER_ENABLE
        case CU_APPSWITCH_RIGHT:
        case CU_APPSWITCH_LEFT:
            app_switcher_record(keycode, record);
            return false;
            break;
#endif

            /* Modify keyboard parameters.
             */
        case CU_LGHTUP:
        case CU_LGHTDN:
            if (record->event.pressed) {
                kb_lighting_adjust(keycode == CU_LGHTUP, mods);
                start_key_repeat(keycode, record);
            } else {
                stop_key_repeat();
            }
            return false;
            break;

            /* Take a screenshot of the window under the cursor. Currently works on macOS only.
             */
        case CU_SCRSHOT_WIN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCRSHOT_REGION));
                wait_ms(100);
                tap_code(KC_SPC);
#ifdef MOUSEKEY_ENABLE
                tap_code16(CM_BTN1);
#endif
            }
            return false;
            break;

            /* Take screenshot of a region. This does the initial mouse press,
             * so press and hold the key, drag with the mouse keys then release the key.
             * Currently works on macOS only.
             */
        case CU_SCRSHOT_RGN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCRSHOT_REGION));
#ifdef MOUSEKEY_ENABLE
                wait_ms(100);
                register_code16(CM_BTN1);
#endif
            } else {
#ifdef MOUSEKEY_ENABLE
                unregister_code16(CM_BTN1);
#endif
            }
            return false;
            break;

            /* Wipe the EEPROM. Handy if you get stuck when you have multiple
             * default layers.....  After doing this, power-cycle the
             * keyboard. There will be no visible indication...
             */
        case CU_WIPE:
            if (record->event.pressed) {
                eeconfig_init();
            }
            return false;
            break;

            /* Lock the screen.
             */
        case CU_SLCK:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREEN_LOCK));
                wait_ms(500);
                tap_code16(KC_ESC);
            }
            return false;
            break;

            /* Save RGB state to EEPROM.
             */
        case CU_WRITE:
            if (record->event.pressed) {
                write_lighting_to_eeprom();
            }
            return false;
            break;

            /* Select the OS used for shortcuts and write to EEPROM.
             */
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
        case CU_MACOS:
        case CU_WINDOWS:
        case CU_LINUX:
            if (record->event.pressed) {
                process_os_change(keycode);
            }
            return false;
            break;
#endif
    }

#ifdef CUSTOM_CAPSWORD
    if (!process_auto_unshift(keycode, record)) {
        return false;
    }
#endif

    return true;
}

/**
 * User-level processing of custom keycodes.
 */
bool process_record_user_common(uint16_t keycode, keyrecord_t *record) {
#ifdef LAYER_TAP_TOGGLE
    // Check for interrupt to layer-tap-toggle
    ltt_interrupt(keycode, record);
#endif

    // Check for repeat key
    if (!process_record_repeatkey(keycode, record)) {
        return false;
    }

#ifdef COMBOROLL_ENABLE
    // Check for and process comboroll keys
    if (!process_record_comboroll(keycode, record)) {
        return false;
    }
#endif
/*
    switch (keycode) {
        // Lock/unlock current layer 
        case CU_LOCK:
            ltt_lock(record);
            return false;
            break;
    }
    */
    // Process custom keycodes that output characters
    if (!process_record_user_emit(keycode, record)) {
        return false;
    }

    // Add extra tap events if the repeat key has been pressed
    if (record->event.pressed && keycode < QK_USER && keycode != KC_LSFT && keycode != KC_RSFT) {
        while (repeat_that_output()) {
            tap_code16(keycode);
        }
        return true;
    }

    return true;
}

/**
 * User-level matrix scan hook.
 */
void matrix_scan_user(void) {
    // App-switcher timeout
#ifdef APP_SWITCHER_ENABLE
    app_switcher_tick();
#endif

    // Update ltt_timer
#ifdef LAYER_TAP_TOGGLE
    ltt_tick();
#endif

    // Repeat key timeout
    repeatkey_tick();

    // Key repeat timeout
    key_repeat_tick();

    // Caps word toggle timeout
#ifdef CUSTOM_CAPSWORD
    capsword_tick();
#endif

    // Comboroll timing repeat
#ifdef COMBOROLL_ENABLE
    comboroll_tick();
#endif

    // Editing repeat
#ifdef CUSTOM_EDIT
    custom_edit_tick();
#endif
}

/**
 * User-level layer change hook.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    /* Release the appswitcher on every layer change.
     */
#ifdef APP_SWITCHER_ENABLE
    app_switcher_release();
 #endif
   return state;
}
