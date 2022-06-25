/* Copyright 2020 @frogm0uth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty ofo
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "keymap.h"

/**
 * User-level encoder processing. This switches on the layer to decide what to do for each
 * encoder. Some features may be disabled, depending on the variables in rules.mk.
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
    bool left  = (index == 0); // Just for readibility
    bool right = !left;
    
    uint8_t       mods    = get_mods();
    layer_state_t layer   = get_highest_layer(layer_state);
    uint16_t      keycode = KC_NO;

    /* This goes in two phases. First, handle anything that needs to preserve mods
     * between clicks.
     */
#ifdef OS_SHORTCUTS
    switch (layer) {
        case ALPHA:
            if (right) {
                if (!(mods & ~(MOD_BIT(SC(SC_APPSWITCH_START))))) {
                    app_switcher_trigger(clockwise);
                    return false;
                }
            }
    }
#endif

    /* Now clear all modifiers and do the rest.
     */
    clear_mods();
    switch (layer) {
        // Left encoder by default does volume control
        case ALPHA:
            if (left) {
	      keycode = clockwise ? KC_VOLU : KC_VOLD;
            }
            break;

	// On the Edit layer, zoom the application window, unless a modifier is held
        case EDIT:
            if (left) {
#ifdef CUSTOM_EDIT
                if (!custom_edit_encoder(clockwise)) {
		    keycode = clockwise ? SC(SC_APP_ZOOM_IN) : SC(SC_APP_ZOOM_OUT);
		}
#else
		keycode = clockwise ? SC(SC_APP_ZOOM_IN) : SC(SC_APP_ZOOM_OUT);
#endif
            }
            break;

        // On the Meta layer, scroll through search results, unless a modifier is held. If one is,
	// change backlight color
        case META:
            if (left) {
                if (!(mods & MOD_MASK_CAG)) {
		    keycode = clockwise ? SC(SC_NEXT_SEARCH) : SC(SC_PREV_SEARCH);
                }
#ifdef RGBLIGHT_ENABLE
                rgblight_encoder(clockwise, mods);
#endif
            }
            break;
    }

    if (keycode != KC_NO) { // Send the keycode, if there is one
        tap_code16(keycode);
    }
    set_mods(mods); // Restore the modifiers to original state
    return false;
}
