/*
 * Copyright 2020-2023 @frogm0uth
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

// Define the layers
enum layers {
    ALPHA,
    SYMS,
    EDIT,
    META,
    FUNC,
    SNAP,
    NUM_LAYERS // <- this is needed for layer-tap-toggle
};

// Define layer-tap-toggle keys. If not using LTT, define macros for standard layer switching of a subset
// clang-format off
#ifdef LAYER_TAP_TOGGLE
#    define LAYER_KEYS \
        CL_BASE,       \
        CL_SYMS,       \
        CL_EDIT,       \
        CL_META,       \
        CL_FUNC,       \
        CL_SNAP
#else
#    define CL_BASE TO(ALPHA)
#    define CL_SYMS LT(SYMS,   KC_DQUO)
#    define CL_EDIT LT(EDIT,   KC_TAB)
#    define CL_META LT(META,   KC_NO)
#    define CL_FUNC LT(FUNC,   KC_NO)
#    define CL_SNAP LT(SNAP,   KC_NO)
#endif
// clang-format on

// Must come last, after layer definitions
#include "../common/keycodes.h"


/**
 * Extern functions for keyboard-specific files
 */
void set_keylog(uint16_t keycode, keyrecord_t *record);

void rgblight_control(bool up, uint8_t mods);


/**
 * Define custom version of the layout stack
 */
// clang-format off
#define KEY_LAYOUT_stack( \
    L00, L01, L02, L03, L04, L05, \
    L10, L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24,      \
                                  \
                    R00, R01, R02, R03, R04, R05, \
                    R10, R11, R12, R13, R14, R15, \
                         R21, R22, R23, R24, R25, \
                                 \
    L30, L31, L32, R30, R31, R32 \
  ) \
  { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, L30, L31, L32 }, \
    { R05, R04, R03, R02, R01, R00 }, \
    { R15, R14, R13, R12, R11, R10 }, \
    { R25, R24, R23, R22, R21, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, R32, R31, R30 } \
  }
// clang-format on


