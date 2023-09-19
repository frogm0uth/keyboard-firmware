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

/**
 * Platform-dependent shortcuts. This can either have platform-specific
 * shortcuts compiled in statically, or selected dynamically (i.e. at runtime).
 */

#ifndef OS_WINDOWS
#    ifndef OS_LINUX
#        define OS_MACOS // this makes macOS the default if nothing is defined
#    endif
#endif

/**
 * The SC() macro is used to access shortcuts in code. Don't directly use the
 * macros further down.  The argument must be a SC_... keycode. Note that the
 * argument MUST be a constant, you can't use a variable name.
 */
// clang-format off

#ifdef OS_SHORTCUTS
#ifdef OS_SHORTCUTS_STATIC
// selected at compile time
#    define SC(k) (k)
#    if defined(OS_WINDOWS)
#        include "os_shortcuts_static/os_shortcuts_windows.h"
#    elif defined(OS_MACOS)
#        include "os_shortcuts_static/os_shortcuts_macos.h"
#    else
#        include "os_shortcuts_static/os_shortcuts_linux.h"
#    endif
#else
// selected at runtime
#    define OS_SC_OFFSET(k) (k - SC_ID_START)
#    define SC(k) (pgm_read_word(&os_shortcut_codes[OS_SC_OFFSET(k)][os_index]))
#endif
#else
#    define SC(k) (k)
#    include "os_shortcuts_static/os_shortcuts_null.h"
#endif

// clang-format on

#ifndef OS_SHORTCUTS_STATIC
// Variables must be extern for the SC() macro to work
extern const uint16_t os_shortcut_codes[][3];
extern uint8_t        os_index;

// Define the platform/OS
enum os_shortcut_platform {
    os_platform_macos = 0, // Don't change the order
    os_platform_windows,
    os_platform_linux
};
#endif

/**
 * Custom keycodes for OS selection, Must be put in the custom_keycodes enum if
 * using runtime shortcode selection.
 */
// clang-format off
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
#   define OS_SELECT_KEYCODES                       \
        CU_SELECT_MACOS,                            \
        CU_SELECT_WINDOWS,                          \
        CU_SELECT_LINUX
#else
#   define CU_SELECT_MACOS KC_NO
#   define CU_SELECT_WINDOWS KC_NO
#   define CU_SELECT_LINUX KC_NO
#endif
// clang-format on

/**
 * Extern functions
 */
void    process_record_shortcut(uint16_t keycode, keyrecord_t *record);
void    os_set_from_keycode(uint16_t keycode);
void    os_set_raw(uint8_t os);
uint8_t os_get_raw(void);
void    os_shortcut_status(bool);
