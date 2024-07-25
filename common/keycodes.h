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


enum custom_keycodes {
    CU_IGNORE = QK_USER /*SAFE_RANGE*/,

    CU_SLCK,        // Lock the screen
    CU_CAPSWORD,    // Toggle caps-word
    CU_SHIFT,       // Custom shift (not auto-unshift)

    CU_SCRSHOT_WIN, // Screenshot a window
    CU_SCRSHOT_RGN, // Start drag-select screenshot

    CU_APPSWITCH_RIGHT, // Application switcher
    CU_APPSWITCH_LEFT,

    CU_LGHTUP,    // Increase/decrease keyboard lighting
    CU_LGHTDN,

    CU_WIPE, // Wipe the EEPROM
    CU_WRITE, // Save current state to EEPROM

    CU_DIRUP, // Move up a directory
    CU_SPCR,  // Custom space for right thumb

    CU_REPT,  // Repeat the next character (or comboroll)

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
#   include "../common/shift_defs.h"
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
#   include "../common/os_shortcut_defs.h"
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
#define CU_BSLS CU_BSLS_AT

// Make it easier to read null key (instead of XXXXXXX)
#define ___X___ KC_NO

