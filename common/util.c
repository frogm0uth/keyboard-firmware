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
 * QMK-related utilities
 */


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
    if (mods & MOD_MASK_CTRL) {
        if (up) {
            rgb_matrix_increase_hue_noeeprom();
        } else {
            rgb_matrix_decrease_hue_noeeprom();
        }
    } else if (mods & MOD_MASK_ALT) {
        if (up) {
            rgb_matrix_increase_sat_noeeprom();
        } else {
            rgb_matrix_decrease_sat_noeeprom();
        }
    } else if (mods & MOD_MASK_GUI) {
        if (up) {
            rgb_matrix_increase_val_noeeprom();
        } else {
            rgb_matrix_decrease_val_noeeprom();
        }
    }
#endif
}

/**
 * Functions for outputting characters. Useful for combos and things like that.
 */

// Emit an array of keycodes in PROGMEM. Check auto-unshift after first keycode.
void emit_progmem_array(const uint16_t *keyptr) {
    keyrecord_t record;
    emit_progmem_array_record(keyptr, &record);
}

// Emit an array of keycodes in PROGMEM, allowing custom keycodes. Check auto-unshift after first keycode.
void emit_progmem_array_record(const uint16_t *keyptr, keyrecord_t *record) {
    uint16_t keycode = pgm_read_word(keyptr++);
    tap_custom_key(keycode, record);
    if (check_auto_unshift()) {
        del_mods(MOD_MASK_SHIFT);
    }
    keycode = pgm_read_word(keyptr++);
    while (keycode != KC_NO) {
        tap_custom_key(keycode, record);
        keycode = pgm_read_word(keyptr++);
    }
}

// Emit a PROGMEM string. Check auto-unshift after first character.
void emit_progmem_string(const char *str) {
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