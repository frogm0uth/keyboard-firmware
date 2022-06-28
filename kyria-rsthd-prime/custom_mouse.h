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
#include "pointing_device.h"

#ifdef CUSTOM_MOUSE
#    define CM_BUTTON(kc) (1U << (kc - CM_BTN1))
#endif


#ifdef CUSTOM_MOUSE
// clang-format off
#define CUSTOM_MOUSE_KEYS			\
    CM_BTN1,					\
    CM_BTN2,					\
    CM_BTN3
// clang-format on

#else
#    ifdef MOUSEKEY_ENABLE
#        define CM_BTN1 KC_BTN1
#        define CM_BTN2 KC_BTN2
#        define CM_BTN3 KC_BTN3
#    else
#        define CM_BTN1 KC_TRNS
#        define CM_BTN2 KC_TRNS
#        define CM_BTN3 KC_TRNS
#    endif
#endif

bool custom_mouse_process_record(uint16_t keycode, keyrecord_t *record);
