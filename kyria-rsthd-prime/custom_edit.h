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

/**
 ** Custom editing operations.  These are intended to make text editing more
 ** platform-independent (and faster).
 **
 ** For additional documentation, see
 ** https://github.com/frogm0uth/keyboard-notes/blob/master/qmk-custom-edit/README.md
 **/

// time until first repeat keypress
#ifndef CE_WAIT_TERM
#    define CE_WAIT_TERM 250
#endif

#ifndef CE_REPEAT_TERM
#    define CE_REPEAT_TERM 80
#endif

#ifndef CE_FAST_TERM
#    define CE_FAST_TERM 20
#endif

// clang-format off
#ifdef CUSTOM_EDIT // NB Don't change the order
#    define CUSTOM_EDIT_KEYS         \
         CE_LEFT,		     \
         CE_RIGHT,		     \
         CE_UP,                      \
         CE_DOWN,		     \
         			     \
         CE_HOME,		     \
         CE_END,		     \
         			     \
         CE_PAGE_UP,		     \
         CE_PAGE_DOWN,		     \
         			     \
	 CE_DELETE,                  \
         CE_MORE,                    \
         CE_X5,                      \
         CE_FAST

// clang-format on

#else
#    define CE_LEFT KC_LEFT
#    define CE_RIGHT KC_RIGHT
#    define CE_UP KC_UP
#    define CE_DOWN KC_DOWN

#    define CE_HOME KC_HOME
#    define CE_END KC_END

#    define CE_PAGE_UP KC_PGUP
#    define CE_PAGE_DOWN KC_PGDN

#    define CE_DELETE KC_NO
#    define CE_MORE KC_NO
#    define CE_X5 KC_NO
#    define CE_FAST KC_NO

#endif

/**
 * Extern functions
 */
void custom_edit_action(void);
void custom_edit_tick(void);
bool custom_edit_process_record(uint16_t keycode, keyrecord_t *record);
bool custom_edit_encoder_ready(void);
void custom_edit_encoder(bool clockwise);
void custom_edit_status(void);
void custom_edit_encoder_status(void);
