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
#include "custom_mouse.h"
#include "custom_edit.h"
#include "layer_tap_toggle.h"
#include "compose_key.h"

/**
 * Extern functions for core files
 */
bool app_switcher_isactive(void);
void app_switcher_tick(void);
void app_switcher_record(uint16_t keycode, keyrecord_t *record);
void app_switcher_trigger(bool forward);
void app_switcher_release(void);
void rgblight_encoder(bool clockwise, uint8_t mods);
void rgblight_oled_status(void);

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

#ifdef LEADER_ENABLE
LEADER_EXTERNS();
extern void matrix_scan_leader(void);
#endif

// Define the layers
enum layers {
    RSTHD = 0,
    PRIME,
    NUMPAD,
    SYNTAX,
    EDIT,
    CURSOR,
    FUNC,
    NUM_LAYERS    // <- this is needed for layer-tap-toggle
};
#define ALPHA RSTHD    // MUST be set to the FIRST default layer i.e 0

// Define layer-tap-toggle keys. If not using LTT, define macros for standard layer switching of a subset
#ifdef LAYER_TAP_TOGGLE
#    define LAYER_KEYS \
        CL_BASE,       \
        CL_NUMP,       \
        CL_SYNT,       \
        CL_EDIT
#else
#    define CL_BASE TO(ALPHA)
#    define CL_NUMP LT(NUMPAD, KC_QUOT)
#    define CL_SYNT LT(SYNTAX, KC_TAB)
#    define CL_EDIT LT(EDIT, KC_QUOT)
#endif

enum custom_keycodes {
    CU_IGNORE = SAFE_RANGE,

    CU_DIRU,    // Directory up

    CU_LSFT,    // Shift-caps lock keys
    CU_RSFT,

    CU_DOT_UNDERSCORE,    // Custom punctuation keys
    CU_COMMA_MINUS,
    CU_DOT_MINUS,
    CU_COMMA_UNDERSCORE,
    CU_EXCLAIM_QUESTION,

    CU_HYPER_BACK,    // Hyper back and forward
    CU_HYPER_FORWARD,

    CU_SWIN,    // Screenshot a window
    CU_SRGN,    // Start drag-select screenshot

    CU_APPR,    // Applications or tab left or right
    CU_APPL,
    CU_TABR,
    CU_TABL,

    CU_WIPE,    // Wipe the EEPROM
    CU_SAVE,    // Save current state to EEPROM
    CU_PRIM,    // Change default layer and save to EEPROM
    CU_RSTH,

#ifdef LAYER_TAP_TOGGLE
    LAYER_KEYS,    // Keys for layer-tap-toggle
#endif

#ifdef COMPOSE_KEY
    CU_COMPOSE,    // Compose key
#endif

#ifdef CUSTOM_MOUSE
    CUSTOM_MOUSE_KEYS,    // Custom mouse and wheel movement
#endif

#ifdef CUSTOM_EDIT
    CUSTOM_EDIT_KEYS,    // Custom editing and navigation
#endif

#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    OS_SELECT_KEYCODES,
    OS_SHORTCUT_KEYCODES,
#endif
};

// Since we are using OS shortcuts, here are some #defines to make them fit better into the keymap
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)

#    define CU_SLCK SC_SCREEN_LOCK
#    define CU_SSLP SC_SYSTEM_SLEEP

#    define CU_XPSE SC_EXPOSE_ALL
#    define CU_SCRR SC_NEXT_SCREEN
#    define CU_SCRL SC_PREV_SCREEN
#    define CU_FSCR SC_FULLSCREEN

#    define CU_APPX SC_EXPOSE_WINDOWS
#    define CU_APPN SC_NEXT_APP
#    define CU_APPP SC_PREV_APP
#    define CU_DTOP SC_REVEAL_DESKTOP

#    define CU_ALL  SC_SELECT_ALL
#    define CU_CUT  SC_CUT_SELECTION
#    define CU_COPY SC_COPY_SELECTION
#    define CU_PAST SC_PASTE_CLIPBOARD
#    define CU_UNDO SC_UNDO_ACTION
#    define CU_REDO SC_REDO_ACTION

#    define CU_SSCR SC_SHOT_SCREEN

#    define CU_WINR SC_NEXT_WINDOW
#    define CU_WINL SC_PREV_WINDOW

#    define CU_APPZ SC_APP_ZOOM_RESET
#    define CU_SCRZ SC_SCR_ZOOM_RESET

#    define CU_MAC CU_SELECT_MACOS
#    define CU_WIN CU_SELECT_WINDOWS

#else

#    define CU_SLCK KC_NO
#    define CU_SSLP KC_NO

#    define CU_XPSE KC_NO
#    define CU_SCRR KC_NO
#    define CU_SCRL KC_NO
#    define CU_FSCR KC_NO

#    define CU_APPX KC_NO
#    define CU_APPN KC_NO
#    define CU_APPP KC_NO
#    define CU_DTOP KC_NO

#    define CU_ALL  KC_NO
#    define CU_CUT  KC_NO
#    define CU_COPY KC_NO
#    define CU_PAST KC_NO
#    define CU_UNDO KC_NO
#    define CU_REDO KC_NO

#    define CU_SSCR KC_NO

#    define CU_WINR KC_NO
#    define CU_WINL KC_NO

#    define CU_APPZ KC_NO
#    define CU_SCRZ KC_NO

#    define CU_MAC KC_NO
#    define CU_WIN KC_NO

#endif
