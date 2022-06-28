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

/**
 ** Custom mouse code. Currently, this just gives us button presses. The reason for this
 ** is that I ran out of space in the Pro Micro and doing it this way saves a bit over 500 bytes
 ** compared to turning on QMK mouse keys...
 **/
static uint8_t mouse_buttons = 0;

#define IS_MOUSE_BTN1 (mouse_buttons & CM_BUTTON(CM_BTN1))
#define IS_MOUSE_BTN2 (mouse_buttons & CM_BUTTON(CM_BTN2))
#define IS_MOUSE_BTN3 (mouse_buttons & CM_BUTTON(CM_BTN3))


bool custom_mouse_process_record(uint16_t keycode, keyrecord_t *record) {
    report_mouse_t currentReport = pointing_device_get_report();
    if (record->event.pressed) {
        switch (keycode) {
            case CM_BTN1:
                currentReport.buttons |= MOUSE_BTN1;
                break;
            case CM_BTN2:
                currentReport.buttons |= MOUSE_BTN2;
                break;
            case CM_BTN3:
                currentReport.buttons |= MOUSE_BTN3;
                break;
	    default:
	        return true;
        }
        mouse_buttons |= CM_BUTTON(keycode);

    } else {
        switch (keycode) {
            case CM_BTN1:
                currentReport.buttons &= ~MOUSE_BTN1;
                break;
            case CM_BTN2:
                currentReport.buttons &= ~MOUSE_BTN2;
                break;
            case CM_BTN3:
                currentReport.buttons &= ~MOUSE_BTN3;
                break;
	    default:
	        return true;
        }
        mouse_buttons &= ~CM_BUTTON(keycode);
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
    return false;
}
