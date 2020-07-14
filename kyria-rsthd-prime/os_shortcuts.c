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

#include "keymap.h"

/**
 * Platform-dependent shortcuts.
 */

#ifndef OS_SHORTCUTS_STATIC
#ifdef OS_WINDOWS
uint8_t os_index = os_platform_windows;
#else
uint8_t os_index = os_platform_macos;
#endif

void os_set_raw(uint8_t os) {
  os_index = os;
}
uint8_t os_get_raw() {
  return os_index;
}
#endif

// The array of shortcut codes.
//
#ifndef OS_SHORTCUTS_STATIC
const uint16_t PROGMEM os_shortcut_codes[][2] = {
  OS_SC_DEFINE(SC_ID_START), // "Null" keycode, do not use directly, do not remove
  
  // Moving the cursor
  OS_SC_DEFINE(SC_WORD_LEFT),
  OS_SC_DEFINE(SC_WORD_RIGHT),

  OS_SC_DEFINE(SC_START_OF_LINE),
  OS_SC_DEFINE(SC_END_OF_LINE),

  OS_SC_DEFINE(SC_START_OF_PARA),
  OS_SC_DEFINE(SC_END_OF_PARA),

  OS_SC_DEFINE(SC_START_OF_DOC),
  OS_SC_DEFINE(SC_END_OF_DOC),

  // Deletion
  OS_SC_DEFINE(SC_DEL_WORD_LEFT),
  OS_SC_DEFINE(SC_DEL_WORD_RIGHT),

  // Forward and backward
  OS_SC_DEFINE(SC_NEXT_SEARCH),
  OS_SC_DEFINE(SC_PREV_SEARCH),
  OS_SC_DEFINE(SC_BROWSER_BACK),
  OS_SC_DEFINE(SC_BROWSER_FWD),

  // Copy/paste/undo
  OS_SC_DEFINE(SC_SELECT_ALL),
  OS_SC_DEFINE(SC_CUT_SELECTION),
  OS_SC_DEFINE(SC_COPY_SELECTION),
  OS_SC_DEFINE(SC_PASTE_CLIPBOARD),
  OS_SC_DEFINE(SC_UNDO_ACTION),
  OS_SC_DEFINE(SC_REDO_ACTION),
  
  // App switcher
  OS_SC_DEFINE(SC_APPSWITCH_START),
  OS_SC_DEFINE(SC_APPSWITCH_RIGHT),
  OS_SC_DEFINE(SC_APPSWITCH_LEFT),

  // Window/tab navigation
  OS_SC_DEFINE(SC_NEXT_WINDOW),     // next/prev window of current app
  OS_SC_DEFINE(SC_PREV_WINDOW),

  OS_SC_DEFINE(SC_TAB_RIGHT),       // move current tab to the right/left
  OS_SC_DEFINE(SC_TAB_LEFT),

  OS_SC_DEFINE(SC_TAB_RIGHT_ALT),   // Alternate version for some apps (MacOS only)
  OS_SC_DEFINE(SC_TAB_LEFT_ALT),

  // Zooming
  OS_SC_DEFINE(SC_APP_ZOOM_IN),
  OS_SC_DEFINE(SC_APP_ZOOM_OUT),
  OS_SC_DEFINE(SC_APP_ZOOM_RESET),
  
  OS_SC_DEFINE(SC_SCR_ZOOM_IN), // MacOS: needs to be enabled in Accessibility
  OS_SC_DEFINE(SC_SCR_ZOOM_OUT),
  OS_SC_DEFINE(SC_SCR_ZOOM_RESET),

  // Screenshots - will probably need additional code to use
  OS_SC_DEFINE(SC_SHOT_SCREEN), // Take whole screen and save to file.
  OS_SC_DEFINE(SC_SHOT_REGION), // MacOS: starts drag-select. Win: Opens Snip & Sketch

  // Window manager
  OS_SC_DEFINE(SC_EXPOSE_ALL),      // Expose all windows/desktops
  OS_SC_DEFINE(SC_NEXT_SCREEN),     // Prev/next desktop/screen
  OS_SC_DEFINE(SC_PREV_SCREEN),
  OS_SC_DEFINE(SC_FULLSCREEN),      // Toggle window to/from fullscreen
  
  OS_SC_DEFINE(SC_EXPOSE_WINDOWS),  // Expose windows of current app
  OS_SC_DEFINE(SC_NEXT_APP),        // Expose windows of next/prev app (macOS only)
  OS_SC_DEFINE(SC_PREV_APP),

  OS_SC_DEFINE(SC_REVEAL_DESKTOP),  // Reveal desktop

	       // System control
  OS_SC_DEFINE(SC_SCREEN_LOCK),
  OS_SC_DEFINE(SC_SYSTEM_SLEEP),
  
  OS_SC_DEFINE(SC_ID_END) // end marker, does nothing useful, do not use, do not remove
};
#endif

// Implement default processing for custom keycodes for each shortcut. Call
// this at the end of process_record_user().
//
#ifndef OS_SHORTCUTS_STATIC
void process_record_shortcut(uint16_t keycode, keyrecord_t *record) {
  if (keycode > SC_ID_START && keycode < SC_ID_END) {
    uint16_t offset = keycode - SC_ID_START;
    uint16_t shortcut = (pgm_read_word(&os_shortcut_codes[offset][os_index]));
    if (record->event.pressed) {
      register_code16(shortcut);
    } else {
      unregister_code16(shortcut);
    }
  }
}
#endif

// Set the OS from a keycode. Call this from process_record_user(). Not persistent.
//
#ifndef OS_SHORTCUTS_STATIC
void os_set_from_keycode(uint16_t keycode) {
  switch (keycode) {
  case CU_SELECT_MACOS:
    os_index = os_platform_macos;
    break;
      
  case CU_SELECT_WINDOWS:
    os_index = os_platform_windows;
    break;
  }
}
#endif

// Display OS on the OLED
//
#ifdef OLED_DRIVER_ENABLE
void os_shortcut_status () {
#ifdef OS_SHORTCUTS_STATIC
  #ifdef OS_MACOS
    oled_write_P(PSTR("MACOS "), false);
  #else
    oled_write_P(PSTR("WINDOWS "), false);
  #endif
#else
  switch (os_index) {
  case os_platform_macos:
    oled_write_P(PSTR("MACOS "), false);
    break;
  case os_platform_windows:
    oled_write_P(PSTR("WINDOWS "), false);
    break;
  default:
    oled_write_P(PSTR("?OS? "), false);
    break;
  }
#endif
}
#endif
