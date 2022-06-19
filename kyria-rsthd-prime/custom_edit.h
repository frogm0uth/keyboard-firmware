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

#ifdef CUSTOM_EDIT
#    define CE_MOD_BIT(kc) (1U << (kc - CE_REPT))
#endif

#ifndef EDIT_REPEAT_TERM
#    define EDIT_REPEAT_TERM 50
#endif

#ifdef CUSTOM_EDIT
// clang-format off
#    define CUSTOM_EDIT_KEYS \
        CE_MV_L,             \
            CE_MV_R,         \
            CE_MV_U,         \
            CE_MV_D,         \
                             \
            CE_WD_L,         \
            CE_WD_R,         \
                             \
            CE_PG_U,         \
            CE_PG_D,         \
                             \
            CE_REPT,         \
            CE_ACC1,         \
            CE_ACC2,         \
            CE_DMOD
// clang-format on

#    define CUSTOM_EDIT_PROCESS_RECORD(kc, rec)         \
        case CE_MV_L:                                   \
        case CE_MV_R:                                   \
        case CE_MV_U:                                   \
        case CE_MV_D:                                   \
        case CE_WD_L:                                   \
        case CE_WD_R:                                   \
        case CE_PG_U:                                   \
        case CE_PG_D:                                   \
            custom_edit_record(kc, rec->event.pressed); \
            break;                                      \
                                                        \
        case CE_REPT:                                   \
        case CE_DMOD:                                   \
        case CE_ACC1:                                   \
        case CE_ACC2:                                   \
            custom_edit_mod(kc, rec);                   \
            break

#else
#    define CE_MV_L KC_LEFT
#    define CE_MV_R KC_RIGHT
#    define CE_MV_U KC_UP
#    define CE_MV_D KC_DOWN

#    define CE_WD_L KC_HOME
#    define CE_WD_R KC_END

#    define CE_PG_U KC_PGUP
#    define CE_PG_D KC_PGDN

#    define CE_DMOD KC_NO
#    define CE_ACC1 KC_NO
#    define CE_ACC2 KC_NO
#    define CE_REPT KC_NO

#endif

/**
 * Extern functions
 */
void custom_edit_action(void);
void custom_edit_tick(void);
void custom_edit_mod(uint16_t keycode, keyrecord_t *record);
void custom_edit_record(uint16_t keycode, bool pressed);
void custom_edit_encoder(bool clockwise);
void custom_edit_status(void);
