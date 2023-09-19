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
#define CU_QTQT CU_QUOTE_QUOTE

// Make it easier to read null key (instead of XXXXXXX)
#define ___X___ KC_NO

