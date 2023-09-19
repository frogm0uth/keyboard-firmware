/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS


// Configuration for combos
#define COMBO_TERM 90
#define COMBOROLL_TERM 200

// Tapping control
#define TAPPING_TERM 500

// uncomment to make OS-dependent shortcuts be statically compiled.
//#define OS_SHORTCUTS_STATIC
#ifdef OS_SHORTCUTS_STATIC
     // Uncomment one of these to choose the OS for static shortcuts
#    define OS_MACOS
//#    define OS_WINDOWS
//#    define OS_LINUX
#endif


#ifdef RGBLIGHT_ENABLE
    //#define RGBLIGHT_EFFECT_BREATHING
    //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
    //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    //#define RGBLIGHT_EFFECT_SNAKE
    //#define RGBLIGHT_EFFECT_KNIGHT
    //#define RGBLIGHT_EFFECT_CHRISTMAS
    //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
    //#define RGBLIGHT_EFFECT_RGB_TEST
    //#define RGBLIGHT_EFFECT_ALTERNATING
    //#define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 4
#    define RGBLIGHT_SAT_STEP 16
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif


// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// Save some space by removing things I don't use. See https://docs.qmk.fm/#/squeezing_avr
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT   // One-shot shifts are not used
#define NO_ACTION_TAPPING   // Mod-taps are not used
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
