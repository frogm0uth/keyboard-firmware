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
#define CM_BIT(kc) (1U << (kc - CM_MS_L))
#define CM_MOD_BIT(kc) (1U << (kc - CM_REPT))
#define CM_BUTTON(kc) (1U << (kc - CM_BTN1))
#endif

#ifndef MOUSE_REPEAT_TERM
#define MOUSE_REPEAT_TERM 30
#endif

#ifndef WHEEL_REPEAT_TERM
#define WHEEL_REPEAT_TERM 100
#endif

#ifdef CUSTOM_MOUSE
// clang-format off
#define CUSTOM_MOUSE_KEYS			\
  CM_MS_L,					\
    CM_MS_R,					\
    CM_MS_U,					\
    CM_MS_D,					\
    						\
    CM_REPT,					\
    CM_SLOW,					\
    CM_ACC1,					\
    CM_ACC2,					\
    CM_WHEE,					\
						\
    CM_BTN1,					\
    CM_BTN2,					\
    CM_BTN3
// clang-format on

#else
#ifdef MOUSEKEY_ENABLE
#define CM_MS_L KC_MS_L
#define CM_MS_R KC_MS_R
#define CM_MS_U KC_MS_U
#define CM_MS_D KC_MS_D

#define CM_REPT KC_NO
#define CM_SLOW KC_ACL0
#define CM_ACC1 KC_ACL1
#define CM_ACC2 KC_ACL2
#define CM_WHEE KC_NO

#define CM_BTN1 KC_BTN1
#define CM_BTN2 KC_BTN2
#define CM_BTN3 KC_BTN3
#else
#define CM_MS_L KC_TRNS
#define CM_MS_R KC_TRNS
#define CM_MS_U KC_TRNS
#define CM_MS_D KC_TRNS

#define CM_REPT KC_TRNS
#define CM_SLOW KC_TRNS
#define CM_ACC1 KC_TRNS
#define CM_ACC2 KC_TRNS
#define CM_WHEE KC_TRNS

#define CM_BTN1 KC_TRNS
#define CM_BTN2 KC_TRNS
#define CM_BTN3 KC_TRNS
#endif
#endif

#define CUSTOM_MOUSE_PROCESS_RECORD(kc,rec)	\
  case CM_MS_L:					\
  case CM_MS_R:					\
  case CM_MS_U:					\
  case CM_MS_D:					\
    custom_mouse_record(keycode, record);      	\
    break;					\
						\
  case CM_REPT:					\
  case CM_SLOW:					\
  case CM_ACC1:					\
  case CM_ACC2:					\
  case CM_WHEE:					\
    custom_mouse_mod(keycode, record);		\
    break;					\
						\
  case CM_BTN1:					\
  case CM_BTN2:				       	\
  case CM_BTN3:				       	\
    custom_mouse_button_record(keycode, record);\
    break


void custom_mouse_tick (void); // Call from matrix_scan_user()
void custom_mouse_button (uint16_t keycode, keyrecord_t *record);
void custom_mouse_button_record (uint16_t keycode, keyrecord_t *record);
void custom_mouse_button_press (uint16_t keycode, bool pressed);
void custom_mouse_mod(uint16_t keycode, keyrecord_t *record);
void custom_mouse_record(uint16_t keycode, keyrecord_t *record);
void custom_mouse_encoder(bool clockwise);
void custom_wheel_encoder(bool clockwise, bool rotate);
void custom_mouse_status(void);
