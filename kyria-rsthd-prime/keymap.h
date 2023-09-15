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
#include "custom_capsword.h"
#include "custom_edit.h"
#include "layer_tap_toggle.h"
#include "comboroll.h"

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
void oled_print_hex(uint8_t n);

void oled_brightness_encoder(bool clockwise);
void oled_brightness_encoder_status(void);

void tap_custom_key(uint16_t keycode, keyrecord_t *record);
void register_custom_key(uint16_t keycode, keyrecord_t *record);
void unregister_custom_key(uint16_t keycode, keyrecord_t *record);

/**
 * User config structure. Defined here instead of keymap.c in case other files
 * need to use it.
 */
typedef union {
    uint32_t raw;
    struct {
        uint8_t os_selection : 2;
        uint8_t oled_brightness : 8;
    };
} user_config_t;

extern user_config_t user_config;

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

enum custom_keycodes {
    CU_IGNORE = QK_USER /*SAFE_RANGE*/,

    CU_SLCK,        // Lock the screen
    CU_CAPSWORD,    // Toggle caps-word
    CU_SHIFT,       // Custom shift (not auto-unshift)

    CU_SCRSHOT_WIN, // Screenshot a window
    CU_SCRSHOT_RGN, // Start drag-select screenshot

    CU_APPSWITCH_RIGHT, // Application switcher
    CU_APPSWITCH_LEFT,

    CU_WIPE, // Wipe the EEPROM
    CU_WRITE, // Save current state to EEPROM

#ifdef LAYER_TAP_TOGGLE
    LAYER_KEYS, // Keys for layer-tap-toggle
#endif

#ifdef CUSTOM_EDIT
    CUSTOM_EDIT_KEYS, // Custom editing and navigation
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
 * Cope with not compiling in mouse keys
 */
#ifdef MOUSEKEY_ENABLE
#    define CM_BTN1 KC_BTN1
#    define CM_BTN2 KC_BTN2
#    define CM_BTN3 KC_BTN3
#else
#    define CM_BTN1 KC_TRNS
#    define CM_BTN2 KC_TRNS
#    define CM_BTN3 KC_TRNS
#endif


/**
 * Shorter keycodes to put in keymap matrix. These are those with
 * custom processing, for direct shortcuts, see os_shortcut_defs.h
 */
#define CU_COMM CU_COMMA_QUES
#define CU_DOT  CU_DOT_EXLM
#define CU_QTQT CU_QUOTE_QUOTE

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
