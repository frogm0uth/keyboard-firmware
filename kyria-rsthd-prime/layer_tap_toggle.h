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
 ** Layer-tap-toggle. Layer active while held, Ctrl-tap to toggle on, Tap to send some other key.
 ** Tap to untoggle the layer. Note: there is no auto-repeat on the tap key on second
 ** tap, like with standard LT or mod-tap.
 **
 ** For additional documentation, see
 ** https://github.com/frogm0uth/keyboard-notes/blob/master/qmk-layer-tap-toggle/README.md
 **/

/** 
 * Extern functions
 */
void ltt_update_timer (void) ;
bool ltt_base(void);
void ltt_interrupt(uint16_t keycode, keyrecord_t *record);
bool ltt_lock(keyrecord_t *record);
bool layer_tap_toggle(uint16_t keycode, uint8_t layer, keyrecord_t *record);
bool layer_tap_toggle2(uint16_t keycode, uint8_t layer, uint8_t layer2, keyrecord_t *record);
