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
#pragma once

#include QMK_KEYBOARD_H

#include "os_shortcuts.h"
#include "custom_edit.h"
#include "layer_tap_toggle.h"
#include "combos.h"

/**
 * Extern functions for core files
 */
bool app_switcher_isactive(void);
void app_switcher_tick(void);
void app_switcher_record(uint16_t keycode, keyrecord_t *record);
void app_switcher_trigger(bool forward);
void app_switcher_release(void);
void rgblight_encoder(bool clockwise, uint8_t mods);
void rgblight_oled_encoder_status(void);
bool process_record_user_emit(uint16_t keycode, keyrecord_t *record);
void process_caps_cancel(uint16_t keycode, keyrecord_t *record);

/**
 * User config structure. Defined here instead of keymap.c in case other files
 * need to use it.
 */
typedef union {
    uint32_t raw;
    struct {
        uint8_t os_selection : 2;
    };
} user_config_t;

extern user_config_t user_config;

// Define the layers
enum layers {
    ALPHA,
    SYMS,
    EDIT,
    SNAP,
    FUNC,
    META,
    NUM_LAYERS // <- this is needed for layer-tap-toggle
};

// Define layer-tap-toggle keys. If not using LTT, define macros for standard layer switching of a subset
// clang-format off
#ifdef LAYER_TAP_TOGGLE
#    define LAYER_KEYS \
        CL_BASE,       \
        CL_SYMS,       \
        CL_EDIT,       \
        CL_SNAP,       \
        CL_FUNC,       \
        CL_META
#else
#    define CL_BASE TO(ALPHA)
#    define CL_SYMS LT(SYMS,   KC_QUOT)
#    define CL_SNAP LT(SNAP,   KC_DQUO)
#    define CL_EDIT LT(EDIT,   KC_QUOT)
#    define CL_FUNC LT(FUNC,   KC_NO)
#    define CL_META LT(META,   KC_K)
#endif
// clang-format on

enum custom_keycodes {
    CU_IGNORE = SAFE_RANGE,

    CU_DIRU, // Directory up macro

    CU_SWIN, // Screenshot a window
    CU_SRGN, // Start drag-select screenshot

    CU_APPSWITCH_RIGHT, // Application switcher
    CU_APPSWITCH_LEFT,

    CU_WIPE, // Wipe the EEPROM
    CU_WRIT, // Save current state to EEPROM

#ifdef LAYER_TAP_TOGGLE
    LAYER_KEYS, // Keys for layer-tap-toggle
#endif

#ifdef CUSTOM_EDIT
    CUSTOM_EDIT_KEYS, // Custom editing and navigation
#endif

#ifdef CUSTOM_MOUSE
    CUSTOM_MOUSE_KEYS, // Custom mouse and wheel movement
#endif

// Custom shift keys. Unfortunately we can't do this simply
// by invoking a macro defined elsewhere.
//
// clang-format off
#   undef  DEFINE_SHIFT
#   define DEFINE_SHIFT(name,normal,shifted) name,
    SHIFT_ID_START,
#   include "shift_defs.h"
    SHIFT_ID_END,
// clang-format on

// OS-independent shortcuts. Unfortunately we can't do this simply
// by invoking a macro defined elsewhere.
//
// clang-format off
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)        
    OS_SELECT_KEYCODES,

#   undef  DEFINE_SHORTCUT
#   define DEFINE_SHORTCUT( SC_name, ...) SC_ ## SC_name,
    SC_ID_START,
#   include "os_shortcut_defs.h"
    SC_ID_END,
#endif
    // clang-format on
};

/**
 * Keycodes for modifiers. Most of these are mod-taps, and defining them this
 * ways makes it easier to change the tap action. If you change these, combos
 * might need to be updated!
 */
#define CU_LSFT KC_LSFT
#define CU_RSFT KC_RSFT
#define CU_LALT ALT_T(KC_TAB)
#define CU_RALT ALT_T(KC_CAPS)
#define CU_LCTL CTL_T(KC_X)
#define CU_RCTL CTL_T(KC_Q)
#define CU_LCMD KC_LGUI
#define CU_RCMD KC_RGUI // not actually used

// Mod-taps on symbols layer
#define CU_SSFT KC_LSFT
#define CU_SCTL CTL_T(KC_2)
#define CU_SALT ALT_T(KC_0)
#define CU_SGUI GUI_T(KC_1)

/**
 * Shorter keycodes to put in keymap matrix. These are those with
 * custom processing, for direct shortcuts, see os_shortcut_defs.h
 */
// ALPHA layer
#define CU_COMM CU_COMMA_PIPE
#define CU_DOT CU_DOT_SLASH
#define CU_EXQU CU_EXCLAIM_QUESTION

// SYMS layer
#define CU_DTDT CU_DOT_DOT
#define CU_MNCM CU_MINUS_COMMA
#define CU_QTQT CU_QUOTE_QUOTE
#define CU_SCSC CU_SCLN_SCLN
#define CU_DLUN CU_DOLLAR_UNDERSCORE
