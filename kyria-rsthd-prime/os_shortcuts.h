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

#include "os_shortcuts_static.h"

/**
 ** Platform-dependent shortcuts. This can either have platform-specific
 ** shortcuts compiled in statically, or selected dynamically (i.e. at runtime).
 **
 ** For additional documentation, see
 ** https://github.com/frogm0uth/keyboard-notes/blob/master/qmk-os-shortcuts/README.md
 **/

#ifndef OS_WINDOWS
#    define OS_MACOS    // this makes macOS the default if nothing is defined
#endif

/**
 * The SC() macro is used to access shortcuts in code. Don't directly use the
 * macros further down.  The argument must be a SC_... keycode. Note that the
 * argument MUST be a constant, you can't use a variable name.
 */
// clang-format off
#ifdef OS_SHORTCUTS_STATIC
// selected at compile time
#    ifdef OS_WINDOWS
#        define SC(k) (WIN_ ## k)
#    else
#        define SC(k) (MAC_ ## k)
#    endif
#else
// selected at runtime
#    define SC(k) (pgm_read_word(&os_shortcut_codes[OS_SC_OFFSET(k)][os_index]))
#endif
// clang-format on

#ifndef OS_SHORTCUTS_STATIC
// Variables must be extern for the SC() macro to work
extern const uint16_t os_shortcut_codes[][2];
extern uint8_t        os_index;
#endif

// "Hidden" macros, don't use these directly
#define OS_SC_OFFSET(k) (k - SC_ID_START)
#define OS_SC_DEFINE(k) [OS_SC_OFFSET(k)] = { MAC_ ## k, WIN_ ## k }

// Define the platform/OS
enum os_shortcut_platform {
    os_platform_macos = 0,    // Don't change the order
    os_platform_windows
};

/**
 * Extern functions
 */
void    process_record_shortcut(uint16_t keycode, keyrecord_t *record);
void    os_set_from_keycode(uint16_t keycode);
void    os_set_raw(uint8_t os);
uint8_t os_get_raw(void);
void    os_shortcut_status(void);

/**
 * Custom keycodes for OS selection, Must be put in the custom_keycodes enum if
 * using runtime shortcode selection.
 */
#define OS_SELECT_KEYCODES                      \
    CU_SELECT_MACOS,                            \
    CU_SELECT_WINDOWS

/**
 * Macro to define custom keycodes for all shortcuts. Must be included in the
 * custom_keycodes enum. The first item MUST be SC_ID_START. If you add to this
 * list, also add the definitions to static_shortcuts.h and add OS_SC_DEFINE
 * lines in shortcuts.c.
 *
 * See shortcuts.c for (brief) descriptions.
 *
 * Note to reviewers: the change in indentation between the first and second
 * lines is emacs, and I can't figure out how to change it...
 */
#define OS_SHORTCUT_KEYCODES \
    SC_ID_START,             \
                             \
        SC_WORD_LEFT,        \
        SC_WORD_RIGHT,       \
                             \
        SC_START_OF_LINE,    \
        SC_END_OF_LINE,      \
                             \
        SC_START_OF_PARA,    \
        SC_END_OF_PARA,      \
                             \
        SC_START_OF_DOC,     \
        SC_END_OF_DOC,       \
                             \
        SC_DEL_WORD_LEFT,    \
        SC_DEL_WORD_RIGHT,   \
                             \
        SC_NEXT_SEARCH,      \
        SC_PREV_SEARCH,      \
        SC_BROWSER_BACK,     \
        SC_BROWSER_FWD,      \
                             \
        SC_SELECT_ALL,       \
        SC_CUT_SELECTION,    \
        SC_COPY_SELECTION,   \
        SC_PASTE_CLIPBOARD,  \
        SC_UNDO_ACTION,      \
        SC_REDO_ACTION,      \
                             \
        SC_APPSWITCH_START,  \
        SC_APPSWITCH_RIGHT,  \
        SC_APPSWITCH_LEFT,   \
                             \
        SC_NEXT_WINDOW,      \
        SC_PREV_WINDOW,      \
                             \
        SC_TAB_RIGHT,        \
        SC_TAB_LEFT,         \
                             \
        SC_TAB_RIGHT_ALT,    \
        SC_TAB_LEFT_ALT,     \
                             \
        SC_APP_ZOOM_IN,      \
        SC_APP_ZOOM_OUT,     \
        SC_APP_ZOOM_RESET,   \
                             \
        SC_SCR_ZOOM_IN,      \
        SC_SCR_ZOOM_OUT,     \
        SC_SCR_ZOOM_RESET,   \
                             \
        SC_SHOT_SCREEN,      \
        SC_SHOT_REGION,      \
                             \
        SC_EXPOSE_ALL,       \
        SC_NEXT_SCREEN,      \
        SC_PREV_SCREEN,      \
        SC_FULLSCREEN,       \
                             \
        SC_EXPOSE_WINDOWS,   \
        SC_NEXT_APP,         \
        SC_PREV_APP,         \
                             \
        SC_REVEAL_DESKTOP,   \
                             \
        SC_SCREEN_LOCK,      \
        SC_SYSTEM_SLEEP,     \
                             \
        SC_ID_END
// NB. Leave SC_ID_END at the end
