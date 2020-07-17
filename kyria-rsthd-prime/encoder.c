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
#include QMK_KEYBOARD_H

#include "keymap.h"


void encoder_update_user(uint8_t index, bool clockwise) {
  bool left = (index == 0);
  bool right = !left;
  uint8_t mods = get_mods();
  layer_state_t layer = get_highest_layer(layer_state);
  uint16_t keycode = KC_NO;
  
  clockwise = !clockwise;  // encoders are wired backwards (??)

  // This goes in two phases. First, handle anything that need to preserve mods between clicks
#ifdef OS_SHORTCUTS
  switch (layer) {
  case ALPHA:
    if (right) {
      if (!(mods & MOD_MASK_CSA)) { // FIXME  for Windows
	app_switcher_record(clockwise ? CU_APPR : CU_APPL, true);
	app_switcher_record(clockwise ? CU_APPR : CU_APPL, false);
	return;
      }
    }
  }
#endif
  
  // Now clear all modifiers and do the rest
  clear_mods();
  switch (layer) {
  case ALPHA:
    if (left) {
      if (mods & MOD_MASK_ALT) {
	keycode = clockwise ? SC(SC_NEXT_SEARCH) : SC(SC_PREV_SEARCH);
      } else if (mods & MOD_MASK_GUI) {
	keycode = clockwise ? SC(SC_BROWSER_FWD) : SC(SC_BROWSER_BACK);
      } else {
	keycode = clockwise ? KC_PGDN : KC_PGUP;
      }
    } else {
      if (mods & MOD_MASK_GUI) {
	keycode = clockwise ? SC(SC_TAB_RIGHT) : SC(SC_TAB_LEFT);
      } else if (mods & MOD_MASK_CTRL) {
	keycode = clockwise ? SC(SC_TAB_RIGHT_ALT) : SC(SC_TAB_LEFT_ALT);
      }
    }
    break;

  case NUMPAD:
    if (left) {
      keycode = clockwise ? SC(SC_SCR_ZOOM_IN) : SC(SC_SCR_ZOOM_OUT);
    } else {
      keycode = clockwise ? SC(SC_APP_ZOOM_IN) : SC(SC_APP_ZOOM_OUT);
    }
    break;

  case SYNTAX:
#ifdef CUSTOM_MOUSE
    if (left) {
      if (mods & MOD_MASK_SHIFT) {
	custom_wheel_encoder(clockwise, false);
      } else {
	custom_wheel_encoder(clockwise, true);
      }
    }
#endif
    break;
    
  case EDIT:
    if (left) {
      keycode = clockwise ? SC(SC_REDO_ACTION) : SC(SC_UNDO_ACTION);
    }
#ifdef CUSTOM_EDIT
    if (right) {
      custom_edit_encoder(clockwise);
    }
#endif
    break;
    
    case CURSOR:
#ifdef CUSTOM_MOUSE
    if (left) {
      custom_mouse_encoder(clockwise);
    }
#endif
    if (right) {
      keycode = clockwise ? SC(SC_REDO_ACTION) : SC(SC_UNDO_ACTION);
    }
    break;

  case FUNC:
    // nothing
    break;
    
  case ADJUST:
    if (left) {
      if (mods & MOD_MASK_SHIFT) {
	keycode = clockwise ? KC_PAUSE : KC_SLCK;
      } else {
	keycode = clockwise ? KC_VOLU : KC_VOLD;
      }
    }
#ifdef RGBLIGHT_ENABLE
    if (right) {
      rgblight_encoder(clockwise, mods);
    }
#endif
    break;
  }
  if (keycode != KC_NO) {  // If we found a single code to send, send it
    tap_code16(keycode);
  }
  set_mods(mods);          // Restore the modifiers to original state
}
