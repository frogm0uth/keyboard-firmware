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
 * Define custom version of the layout stack
 */
// clang-format off
#ifdef KEYBOARD_splitkb_kyria_rev1
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
#endif

#ifdef KEYBOARD_splitkb_kyria_rev3
    #define KEY_LAYOUT_stack(                           \
        k0G, k0F, k0E, k0D, k0C, k0B,                   \
        k1G, k1F, k1E, k1D, k1C, k1B,                   \
        k2G, k2F, k2E, k2D, k2C,                        \
                                                        \
                        k4B, k4C, k4D, k4E, k4F, k4G,   \
                        k5B, k5C, k5D, k5E, k5F, k5G,   \
                             k6C, k6D, k6E, k6F, k6G,   \
                                                        \
        k3B, k3F, k3A, k7A, k7F, k7B,                   \
                                                        \
        k3E                                             \
    ) {                                                 \
         {KC_NO, k0B,   k0C,   k0D,   k0E,   k0F, k0G},   \
         {KC_NO, k1B,   k1C,   k1D,   k1E,   k1F, k1G},   \
         {KC_NO, KC_NO, k2C,   k2D,   k2E,   k2F, k2G},   \
         {k3A,   k3B,   KC_NO, KC_NO, k3E,   k3F, KC_NO}, \
         {KC_NO, k4B,   k4C,   k4D,   k4E,   k4F, k4G},   \
         {KC_NO, k5B,   k5C,   k5D,   k5E,   k5F, k5G},   \
         {KC_NO, KC_NO, k6C,   k6D,   k6E,   k6F, k6G},   \
         {k7A,   k7B,   KC_NO, KC_NO, KC_NO, k7F, KC_NO}  \
    }
#endif

// clang-format on
