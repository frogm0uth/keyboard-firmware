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

void rgblight_encoder(bool clockwise, uint8_t mods) {
    if (mods & MOD_MASK_CTRL) {
        if (clockwise) {
            rgblight_increase_hue_noeeprom();
        } else {
            rgblight_decrease_hue_noeeprom();
        }
    } else if (mods & MOD_MASK_ALT) {
        if (clockwise) {
            rgblight_increase_sat_noeeprom();
        } else {
            rgblight_decrease_sat_noeeprom();
        }
    } else if (mods & MOD_MASK_GUI) {
        if (clockwise) {
            rgblight_increase_val_noeeprom();
        } else {
            rgblight_decrease_val_noeeprom();
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
char hexchars[16] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void print_hex(uint8_t n) {
  oled_write_char(hexchars[(n>>4) & 0x0F], false);
  oled_write_char(hexchars[n & 0x0F], false);
}

void rgblight_oled_status() {
    uint8_t mods = get_mods();

    if (mods & (MOD_MASK_CTRL)) {
        oled_write_P(PSTR("HUE "), false);
    } else if (mods & MOD_MASK_ALT) {
        oled_write_P(PSTR("SAT "), false);
    } else if (mods & MOD_MASK_GUI) {
        oled_write_P(PSTR("VAL "), false);
    }
    if (mods & (MOD_MASK_CAG)) {
        print_hex(rgblight_get_hue());
        oled_write_char(',', false);
        print_hex(rgblight_get_sat());
        oled_write_char(',', false);
        print_hex(rgblight_get_val());
    }
}
#endif
