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
    bool left = (index == 0); // Just for readibility

    uint8_t       mods    = get_mods();
    layer_state_t layer   = get_highest_layer(layer_state);
    uint16_t      keycode = KC_NO;

    /* This goes in two phases. First, handle anything that needs to preserve mods
     * between clicks. Left encoder by default is alt-tab.
     */
#ifdef OS_SHORTCUTS
    switch (layer) {
        case ALPHA:
            if (left) {
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
        // Left encoder does volume control if Ctrl is held
        case ALPHA:
            if (left && (mods & MOD_MASK_CTRL)) {
                keycode = clockwise ? KC_VOLU : KC_VOLD;
            }
            break;

            // On the Edit layer, zoom the application window, unless an edit modifier is held.
            // If one is, move within or delete text.
        case EDIT:
            if (left) {
#ifdef CUSTOM_EDIT
                if (custom_edit_encoder_ready()) {
                    custom_edit_encoder(clockwise);
                } else {
                    keycode = clockwise ? SC(SC_APP_ZOOM_IN) : SC(SC_APP_ZOOM_OUT);
                }
#else
                keycode = clockwise ? SC(SC_APP_ZOOM_IN) : SC(SC_APP_ZOOM_OUT);
#endif
            }
            break;

            // On the Meta layer, scroll through search results, unless a modifier is held. If one is,
            // change backlight color or OLED brightness
        case META:
            if (left) {
                if (mods & MOD_MASK_CAG) {
#ifdef RGBLIGHT_ENABLE
                    rgblight_encoder(clockwise, mods);
#endif
                } else if (mods & MOD_MASK_SHIFT) {
#ifdef OLED_DRIVER_ENABLE
                    oled_brightness_encoder(clockwise);
#endif
                } else {
                    keycode = clockwise ? SC(SC_NEXT_SEARCH) : SC(SC_PREV_SEARCH);
                }
            }
            break;
    }

    if (keycode != KC_NO) { // Send the keycode, if there is one
        tap_code16(keycode);
    }
    set_mods(mods); // Restore the modifiers to original state
    return false;
}
