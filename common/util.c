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
#include "quantum/color.h"


/**
 * QMK-related utilities
 */

// Variables for timer
enum { repeat_inactive, repeat_waiting, repeat_repeating };

static uint16_t    repeat_timer   = 0;
static uint16_t    repeat_term    = KEY_WAIT_TERM;
static uint16_t    repeat_key     = KC_NO;
static keyrecord_t repeat_record;
static uint8_t     repeat_state   = repeat_inactive;

// Start repeating a key. Call from process_record_user().
//
void start_key_repeat(uint16_t keycode, keyrecord_t *record) {
    switch (repeat_state) {
        case repeat_inactive:
            repeat_key = keycode;
            repeat_record = *record; // make a copy
            repeat_term  = KEY_WAIT_TERM;
            repeat_state = repeat_waiting;
            repeat_timer = timer_read();
            break;
    }
}

// Stop repeating a key. Call from process_record_user().
//
void stop_key_repeat() {
    repeat_state = repeat_inactive;
}

// Process a key repeat tick. Call from matrix_scan_user()
//
void key_repeat_tick() {
    switch (repeat_state) {
        case repeat_inactive:
            break;

        case repeat_waiting:
            if (timer_elapsed(repeat_timer) > repeat_term) {
                tap_custom_key(repeat_key, &repeat_record);
                repeat_state = repeat_repeating;
                repeat_term  = KEY_REPEAT_TERM;
                repeat_timer = timer_read();
            }
            break;

        case repeat_repeating:
            if (timer_elapsed(repeat_timer) > repeat_term) {
                tap_custom_key(repeat_key, &repeat_record);
                repeat_state = repeat_repeating; // WHY is this necessary??!
                repeat_timer = timer_read();
            }
            break;
    }
}


/**
 * User space in EEPROM. Variable and function to read at initialization.
*/
user_config_t user_config;

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    // Set OS
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    os_set_raw(user_config.os_selection);
#endif
#if defined(OLED_ENABLE)
    oled_set_brightness(MAX(user_config.oled_brightness, 0x10)); // set a minimum, to avoid blank display
#endif

    // Other functions init
#if defined(COMBOROLL_ENABLE)
    comboroll_post_init();
#endif
}

// Set the OS and store in EEPROM
void process_os_change(uint16_t keycode) {
    os_set_from_keycode(keycode);
    user_config.os_selection = os_get_raw();
    eeconfig_update_user(user_config.raw);
}

// Write current lighting values to EEPROM
void write_lighting_to_eeprom() {
#ifdef RGBLIGHT_ENABLE
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val());
#endif
#ifdef OLED_ENABLE
    user_config.oled_brightness = oled_get_brightness();
    eeconfig_update_user(user_config.raw);
#endif
}

/**
 *  Adjust keyboard lighting based on modifier state
 */
#ifndef OLED_BRIGHTNESS_INCREMENT
#    define OLED_BRIGHTNESS_INCREMENT 0x10
#endif

void kb_lighting_adjust(bool up, uint8_t mods) {
#ifdef OLED_ENABLE
    int16_t brightness = oled_get_brightness();
    if (!(mods & MOD_MASK_CAG)) {
        if (up) {
            brightness = MIN(brightness + OLED_BRIGHTNESS_INCREMENT, 0xff);
        } else {
            brightness = MAX(brightness - OLED_BRIGHTNESS_INCREMENT, 0x01);
        }
        oled_set_brightness(brightness);
    }
#endif

#if defined(RGBLIGHT_ENABLE)
    if (mods & MOD_MASK_CTRL) {
        if (up) {
            rgblight_increase_hue_noeeprom();
        } else {
            rgblight_decrease_hue_noeeprom();
        }
    } else if (mods & MOD_MASK_ALT) {
        if (up) {
            rgblight_increase_sat_noeeprom();
        } else {
            rgblight_decrease_sat_noeeprom();
        }
    } else if (mods & MOD_MASK_GUI) {
        if (up) {
            rgblight_increase_val_noeeprom();
        } else {
            rgblight_decrease_val_noeeprom();
        }
    }
#endif
#if defined(RGB_MATRIX_ENABLE)
    HSV hsv = rgb_matrix_get_hsv();
    if (mods & MOD_MASK_CTRL) {
        uint8_t hue;
        if (up) {
            hue = (hsv.h + 4) % 256;
        } else {
            hue = (hsv.h - 4) % 256;
        }
        rgb_matrix_sethsv_noeeprom(hue, hsv.s, hsv.v);

    } else if (mods & MOD_MASK_ALT) {
        if (up) {
            rgb_matrix_increase_sat_noeeprom();
        } else {
            rgb_matrix_decrease_sat_noeeprom();
        }
    } else if (mods & MOD_MASK_GUI) {
        uint8_t val;
        if (up) {
            val = hsv.v < (255 - 8) ? hsv.v + 8 : 255;
        } else {
            val = hsv.v > 8 ? (hsv.v - 8) : 0;
        }
        rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, val);
    }
#endif
}

/**
 * Functions for outputting characters. Useful for combos and things like that.
 */

// Emit an array of keycodes in PROGMEM.
void emit_progmem_array(const uint16_t *keyptr) {
    keyrecord_t record;
    emit_progmem_array_record(keyptr, &record);
}

// Emit an array of keycodes in PROGMEM, allowing custom keycodes.
void emit_progmem_array_record(const uint16_t *keyptr, keyrecord_t *record) {
    uint16_t keycode = pgm_read_word(keyptr++);
    while (keycode != KC_NO) {
        tap_custom_key(keycode, record);
        keycode = pgm_read_word(keyptr++);
    }
}

// Emit a PROGMEM string.
void emit_progmem_string(const char *str) {
    char ch = pgm_read_byte(str++);
    while (ch) {
        send_char(ch);
        ch = pgm_read_byte(str++);
    }
}

// Emit a PROGMEM string and check auto-unshift after first character.
void emit_progmem_string_autounshift(const char *str) {
    char ch = pgm_read_byte(str++);
    send_char(ch);
    if (check_auto_unshift()) {
        del_mods(MOD_MASK_SHIFT);
    }
    ch = pgm_read_byte(str++);
    while (ch) {
        send_char(ch);
        ch = pgm_read_byte(str++);
    }
}