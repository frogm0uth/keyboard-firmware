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
    if (keycode > SAFE_RANGE) {   // handle custom keycodes, a bit iffy but seems to work...
        process_record_user_emit(keycode, record);
    } else {
        if (keycode == KC_CAPS) { // needs special treatment
            tap_code(KC_CAPS);
        } else {
#ifdef CUSTOM_CAPSWORD
            // Check for capsword cancel
            process_caps_cancel(keycode, record);
            if (process_auto_unshift(keycode, record)) {
                register_code16(keycode);   // we did NOT send the code in process_shift_cancel(),
                                            // so send it now
            }
#else
            register_code16(keycode);
#endif
         }
    }
}

// Unregister a single key. Handles custom keycodes.
void unregister_custom_key(uint16_t keycode, keyrecord_t *record) {
    record->event.pressed = false; // force it off
    if (keycode > SAFE_RANGE) {    // handle custom keycodes, a bit iffy but seems to work...
        process_record_user_emit(keycode, record);
    } else {
        unregister_code16(keycode);
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
#ifndef NO_ACTION_ONESHOT
        uint8_t mods    = get_mods();
        uint8_t ossmods = get_oneshot_mods();

        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);

        register_custom_key((mods | ossmods) & MOD_MASK_SHIFT ? shiftedkey : key, record);

        set_mods(mods);
        set_oneshot_mods(ossmods);
        if (ossmods & MOD_MASK_SHIFT) {
            del_oneshot_mods(MOD_MASK_SHIFT);
        }
#else
        uint8_t mods = get_mods();
        del_mods(MOD_MASK_SHIFT);
        register_custom_key(mods & MOD_MASK_SHIFT ? shiftedkey : key, record);
        set_mods(mods);
#endif
    } else {
        unregister_custom_key(key, record);
        unregister_custom_key(shiftedkey, record);
    }
}

// Process a single custom shift key based on the keycode
void process_custom_shift(uint16_t key, keyrecord_t *record) {
    if (key > SHIFT_ID_START && key < SHIFT_ID_END) {
        process_shift_key(READ_SHIFT_KEY(key, 0), READ_SHIFT_KEY(key, 1), record);
    }
}

/**
 * User-level processing of custom keycodes, for those that might output characters.
 * This is split out from process_record_user so that it can be called from other
 * places (via tap_custom_key()).
 */
bool process_record_user_emit(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_CAPSWORD
    // Check for capsword cancel
    process_caps_cancel(keycode, record);
#endif

    // Process custom shift keys
    process_custom_shift(keycode, record);

    // Process OS shortcut keycodes
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    process_record_shortcut(keycode, record);
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
        case CL_SYMS:
            return layer_tap_toggle(KC_ENTER, SYMS, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(KC_TAB, EDIT, record);
            break;

        case CL_META:
            return layer_tap_toggle(KC_NO, META, record);
            break;

        case CL_FUNC:
            return layer_tap_toggle(KC_NO, FUNC, record);
            break;

        case CL_SNAP:
            return layer_tap_toggle(KC_NO, SNAP, record);
            break;
#else
            // layer switching using QMK layer-tap: handle cases where tap code is 16-bit or has custom shift
        case CL_SYMS:
            if (record->tap.count) {
                process_shift_key(KC_DQUO, KC_DQUO, record);
                return false;
            }
            break;
#endif

            /* Switch between applications (like Alt-Tab on Windows or Cmd-Tab on macOS) This must be triggered from
             * a layer so the release event is called from layer_state_set_user() when the layer is released.
             */
        case CU_APPSWITCH_RIGHT:
        case CU_APPSWITCH_LEFT:
            app_switcher_record(keycode, record);
            break;

            /* Take a screenshot of the window under the cursor. Currently works on macOS only.
             */
        case CU_SCRSHOT_WIN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREENSHOT_REGION));
                wait_ms(100);
                tap_code(KC_SPC);
#ifdef MOUSEKEY_ENABLE
                tap_code16(CM_BTN1);
#endif
            }
            break;

            /* Take screenshot of a region. This does the initial mouse press,
             * so press and hold the key, drag with the mouse keys then release the key.
             * Currently works on macOS only.
             */
        case CU_SCRSHOT_RGN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREENSHOT_REGION));
#ifdef MOUSEKEY_ENABLE
                wait_ms(100);
                register_code16(CM_BTN1);
#endif
            } else {
#ifdef MOUSEKEY_ENABLE
                unregister_code16(CM_BTN1);
#endif
            }
            break;

            /* Wipe the EEPROM. Handy if you get stuck when you have multiple
             * default layers.....  After doing this, power-cycle the
             * keyboard. There will be no visible indication...
             */
        case CU_WIPE:
            if (record->event.pressed) {
                eeconfig_init();
            }
            break;

            /* Lock the screen.
             */
        case CU_SLCK:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREEN_LOCK));
                wait_ms(500);
                tap_code16(KC_ESC);
            }
            break;

            /* Save RGB state to EEPROM.
             */
        case CU_WRITE:
            if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
#endif
#ifdef OLED_ENABLE
                user_config.oled_brightness = oled_get_brightness();
                eeconfig_update_user(user_config.raw);
#endif
            }
            break;

            /* Select the OS used for shortcuts and write to EEPROM.
             */
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
        case CU_SELECT_MACOS:
        case CU_SELECT_WINDOWS:
        case CU_SELECT_LINUX:
            if (record->event.pressed) {
                os_set_from_keycode(keycode);
                user_config.os_selection = os_get_raw();
                eeconfig_update_user(user_config.raw);
            }
            break;
#endif
    }
#ifdef CUSTOM_CAPSWORD
    return process_auto_unshift(keycode, record);
#else
    return true;
#endif
}

/**
 * User-level processing of custom keycodes.
 */
bool process_record_user_common(uint16_t keycode, keyrecord_t *record) {
#ifdef LAYER_TAP_TOGGLE
    // Check for interrupt to layer-tap-toggle
    ltt_interrupt(keycode, record);
#endif

#ifdef CUSTOM_CAPSWORD
    // Toggle caps lock.
    if (!process_record_capslock(keycode, record)) {
        return false;
    }
#endif

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
    return process_record_user_emit(keycode, record);
}

/**
 * User-level matrix scan hook.
 */
void matrix_scan_user(void) {
    // App-switcher timeout
    app_switcher_tick();

    // Update ltt_timer
#ifdef LAYER_TAP_TOGGLE
    ltt_tick();
#endif

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
    app_switcher_release();
    return state;
}