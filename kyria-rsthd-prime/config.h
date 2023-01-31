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

// Configuration for combos
#define COMBO_TERM 70
#define COMBOROLL_TERM 200
#define COMBO_MUST_TAP_PER_COMBO // With QMK combos, avoids having the second combo trigger when
				 // overlapping, but means that holds don't work.

// Tapping control
#define TAPPING_TERM 220
//#define TAPPING_TOGGLE 2
//#define ONESHOT_TAP_TOGGLE 2
//#define IGNORE_MOD_TAP_INTERRUPT
//#define PERMISSIVE_HOLD

// uncomment to make OS-dependent shortcuts be statically compiled.
//#define OS_SHORTCUTS_STATIC
#ifdef OS_SHORTCUTS_STATIC
     // Uncomment one of these to choose the OS for static shortcuts
#    define OS_MACOS
//#    define OS_WINDOWS
//#    define OS_LINUX
#endif

#ifdef OLED_ENABLE
#    define OLED_DRIVER SSD1306
#    define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_ANIMATIONS -- turning this off saves over 3k space...
#    define RGBLIGHT_HUE_STEP 4
#    define RGBLIGHT_SAT_STEP 16
#    define RGBLIGHT_VAL_STEP 8
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

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// Save some space by removing things I don't use. See https://docs.qmk.fm/#/squeezing_avr
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT   // Comment out to use one-shot shifts. Needs ~800 bytes
#define NO_ACTION_TAPPING   // Comment out to use mod-taps
#define LAYER_STATE_8BIT
#define EXTRA_SHORT_COMBOS

//#define DEBUG_MATRIX_SCAN_RATE

// See https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
