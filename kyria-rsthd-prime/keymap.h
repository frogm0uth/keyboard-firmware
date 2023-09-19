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
#pragma once

#include QMK_KEYBOARD_H

#include "../common/appswitcher.h"
#include "../common/comboroll.h"
#include "../common/custom_capsword.h"
#include "../common/custom_edit.h"
#include "../common/layer_tap_toggle.h"
#include "../common/os_shortcuts.h"
#include "../common/process.h"
#include "../common/util.h"

// Must come last
#include "../common/keycodes.h"


/**
 * Extern functions for keyboard-specific files
 */
void rgblight_encoder(bool clockwise, uint8_t mods);
void rgblight_oled_encoder_status(void);

void oled_brightness_encoder(bool clockwise);
void oled_brightness_encoder_status(void);


/**
 * Define custom version of the layout stack
 */
// clang-format off
#define KEY_LAYOUT_stack(                           \
    L00, L01, L02, L03, L04, L05,                   \
    L12, L13, L14, L15, L16, L17,                   \
    L24, L25, L26, L27, L28,                        \
                                                    \
                  R06, R07, R08, R09, R10, R11,     \
                  R18, R19, R20, R21, R22, R23,     \
                       R35, R36, R37, R38, R39,     \
                                                    \
    L42, L43, L44, R45, R46, R47,          \
    L40                                    \
)                                          \
{                                          \
    { KC_NO, KC_NO, L05,   L04,   L03,   L02,   L01,   L00   }, \
    { KC_NO, KC_NO, L17,   L16,   L15,   L14,   L13,   L12   }, \
    { KC_NO, KC_NO, KC_NO, L28,   L27,   L26,   L25,   L24   }, \
    { L44,   L43,   L42,   KC_NO, L40,   KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, R06,   R07,   R08,   R09,   R10,   R11   }, \
    { KC_NO, KC_NO, R18,   R19,   R20,   R21,   R22,   R23   }, \
    { KC_NO, KC_NO, KC_NO, R35,   R36,   R37,   R38,   R39   }, \
    { R45,   R46,   R47,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
}
// clang-format on
