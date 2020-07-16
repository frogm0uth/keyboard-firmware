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

void app_switcher_record(uint16_t keycode, bool pressed);
void rgblight_encoder(bool clockwise, uint8_t mods);
void rgblight_oled_status(void);

// User config structure. Defined here instead of keymap.c in case
//other files need to use it.
typedef union {
  uint32_t raw;
  struct {
    uint8_t     os_selection :2;
  };
} user_config_t;

extern user_config_t user_config;


#ifdef LEADER_ENABLE
LEADER_EXTERNS();
extern void matrix_scan_leader(void);
#else
#define KC_LEAD KC_NO
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
    ADJUST,
    NUM_LAYERS  // <- this is needed for layer-tap-toggle
};
#define ALPHA RSTHD // Must be set to the FIRST default layer...(!)

// Define layer-tap-toggle keys. If not using LTT, define macros for standard layer switching
#ifdef LAYER_TAP_TOGGLE
#define LAYER_KEYS				\
  CU_LLCK,					\
    CU_BASE,					\
    CU_NUMPAD,					\
    CU_SYNTAX,					\
    CU_CURSOR,					\
    CU_EDIT,					\
    CU_FUNC,					\
    CU_ADJUST
#else
#define CU_BASE   TO(ALPHA)  
#define CU_NUMPAD MO(NUMPAD)
#define CU_SYNTAX MO(SYNTAX)
#define CU_EDIT   LT(EDIT,   KC_TAB)
#define CU_CURSOR LT(CURSOR, KC_ENTER)
#define CU_FUNC   TG(FUNC)
#define CU_ADJUST TG(ADJUST)
#define CU_LLCK   KC_NO
#endif

enum custom_keycodes {
  CU_IGNORE = SAFE_RANGE,

  // Custom mouse and wheel movement
#ifdef CUSTOM_MOUSE
  CUSTOM_MOUSE_KEYS,
#endif

  // Custom editing and navigation
#ifdef CUSTOM_EDIT
  CUSTOM_EDIT_KEYS,
#endif
  
  // Keys for layer-tap-toggle
#ifdef LAYER_TAP_TOGGLE
  LAYER_KEYS,
#endif

  CU_DIRU,   // Directory up
  
  CU_LSFT,   // Shift-caps lock keys
  CU_RSFT,

  CU_DOT_UNDERSCORE, // Custom punctuation keys
  CU_COMMA_MINUS,

  CU_HYPER_BACK,    // Hyper back and forward
  CU_HYPER_FORWARD,
  
#ifdef NOTUSED
  CU_RL,     // Right on press, left on shift-press
  CU_UD,     // Up on press, down on shift-press
#endif
  
  CU_SSWIN,  // Screenshot a window
  CU_SSRGN,  // Start drag-select screenshot

  CU_APPR,   // Applications or tab left or right
  CU_APPL,
  CU_TABR,
  CU_TABL,

  CU_WIPE,      // Wipe the EEPROM
  CU_SAVE,      // Save current state to EEPROM
  CU_RSTHD,     // Change default layer and save to EEPROM
  CU_PRIME,

#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
  OS_SELECT_KEYCODES,
  OS_SHORTCUT_KEYCODES,
#endif
};


// Since we are using OS shortcuts, here are some #defines to make them fit better into the keymap
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)

#define CU_SLOCK SC_SCREEN_LOCK
#define CU_SLEEP SC_SYSTEM_SLEEP

#define CU_WALL  SC_EXPOSE_ALL
#define CU_SCRR  SC_NEXT_SCREEN
#define CU_SCRL  SC_PREV_SCREEN
#define CU_FSCR  SC_FULLSCREEN

#define CU_WAPP  SC_EXPOSE_WINDOWS
#define CU_APPN  SC_NEXT_APP
#define CU_APPP  SC_PREV_APP
#define CU_DTOP  SC_REVEAL_DESKTOP

#define CU_ALL   SC_SELECT_ALL
#define CU_CUT   SC_CUT_SELECTION
#define CU_COPY  SC_COPY_SELECTION
#define CU_PAST  SC_PASTE_CLIPBOARD
#define CU_UNDO  SC_UNDO_ACTION
#define CU_REDO  SC_REDO_ACTION

#define CU_SSSCR SC_SHOT_SCREEN

#define CU_WINR  SC_NEXT_WINDOW
#define CU_WINL  SC_PREV_WINDOW

#define CU_APPZ0  SC_APP_ZOOM_RESET
#define CU_SCRZ0  SC_SCR_ZOOM_RESET

#define CU_MAC    CU_SELECT_MACOS
#define CU_WIN    CU_SELECT_WINDOWS

#else

#define CU_SLOCK KC_NO
#define CU_SLEEP KC_NO

#define CU_WALL  KC_NO
#define CU_SCRR  KC_NO
#define CU_SCRL  KC_NO
#define CU_FSCR  KC_NO

#define CU_WAPP  KC_NO
#define CU_APPN  KC_NO
#define CU_APPP  KC_NO
#define CU_DTOP  KC_NO

#define CU_ALL   KC_NO
#define CU_CUT   KC_NO
#define CU_COPY  KC_NO
#define CU_PAST  KC_NO
#define CU_UNDO  KC_NO
#define CU_REDO  KC_NO

#define CU_SSSCR KC_NO

#define CU_WINR  KC_NO
#define CU_WINL  KC_NO

#define CU_APPZ0  KC_NO
#define CU_SCRZ0  KC_NO

#define CU_MAC    KC_NO
#define CU_WIN    KC_NO

#endif
