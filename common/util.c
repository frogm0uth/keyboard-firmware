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

// Print byte as hex to OLED
#ifdef OLED_ENABLE
static char hexchars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void oled_print_hex(uint8_t n) {
    oled_write_P(PSTR("0x"), false);
    oled_write_char(hexchars[(n >> 4) & 0x0F], false);
    oled_write_char(hexchars[n & 0x0F], false);
}
#endif

// User space in EEPROM. Variable and function to read at initialization.

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


// Adjust things based on modifier state
#ifndef OLED_BRIGHTNESS_INCREMENT
#    define OLED_BRIGHTNESS_INCREMENT 0x10
#endif

void kb_adjust(bool up, uint8_t mods) {
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

#ifdef RGBLIGHT_ENABLE
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
}
