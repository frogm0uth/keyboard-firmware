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
    if (mods & MOD_MASK_GUI) {
        if (clockwise) {
            rgblight_increase_val_noeeprom();
        } else {
            rgblight_decrease_val_noeeprom();
        }
    } else if (mods & MOD_MASK_CTRL) {
        if (clockwise) {
            rgblight_increase_sat_noeeprom();
        } else {
            rgblight_decrease_sat_noeeprom();
        }
    } else {
        if (clockwise) {
            rgblight_increase_hue_noeeprom();
        } else {
            rgblight_decrease_hue_noeeprom();
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
void rgblight_oled_status () {
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_GUI) {
        oled_write_P(PSTR("Adj: VAL"), false);
    } else if (mods & MOD_MASK_CTRL) {
        oled_write_P(PSTR("Adj: SAT"), false);
    } else {
        oled_write_P(PSTR("Adj: HUE"), false);
    }
}
#endif
