/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

// Timeout for combos
#define COMBO_TERM 70

// This MIGHT cause the Kyria to crash
//#define EXTRA_LONG_COMBOS

// This WILL cause the Kyria to crash immediately
//#define EXTRA_EXTRA_LONG_COMBOS

// Uncomment to use home row mods 
//#define USE_HOMEROWMODS

// Alter these if needed
#define MODIFIER_INDEX  CTL_T
#define MODIFIER_MIDDLE SFT_T
#define MODIFIER_RING   CMD_T
#define MODIFIER_PINKY  ALT_T

// Tapping control
#define TAPPING_TERM 180
//#define TAPPING_TOGGLE 2
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

// uncomment to make all shortcuts be statically compiled.
//#define OS_SHORTCUTS_STATIC

#if defined(OS_SHORTCUTS_STATIC)
     // Uncomment one of these to choose the OS for static shortcuts,
     // or the *initial* default for dynamically defined shortcuts
#    define(OS_MACOS)
//#    define(OS_WINDOWS)
#endif

// Uncomment to enable detailed compose key status on the OLED
#define COMPOSE_STATUS_ENABLE

#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_ANIMATIONS -- turning this off saves over 3k space...
#    define RGBLIGHT_HUE_STEP 6
#    define RGBLIGHT_SAT_STEP 16
#    define RGBLIGHT_VAL_STEP 16
#    define RGBLIGHT_SLEEP
#endif
#define RGBLIGHT_DISABLE_KEYCODES // Saves about 650 bytes
#define RGBMATRIX_DISABLE_KEYCODES

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

// The Kyria seems to have the encoders connected backwards
#define ENCODER_DIRECTION_FLIP

// The Leader key allows to flexibly assign macros to key sequences.
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 400

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// Save some space by removing things I don't use
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
//#define NO_ACTION_TAPPING

//#define DEBUG_MATRIX_SCAN_RATE
