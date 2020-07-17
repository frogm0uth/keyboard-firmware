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

#include QMK_KEYBOARD_H

// Defs for OS selection
enum os {
    OS_SELECTION_MACOS = 0, // Don't change the order
    OS_SELECTION_WINDOWS
};
#define IS_MACOS      (os_selection==OS_SELECTION_MACOS)
#define IS_WINDOWS    (os_selection==OS_SELECTION_WINDOWS)

enum layers {
    QWERTY = 0,
    COLEDHM,
    WORKMAN,
    RSTHD,
    LOWER,
    RAISE,
    NAV,
    ADJUST
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,

    KC_QWERTY, // Default layer change keys 
    KC_COLEDHM,
    KC_WORKMAN,
    KC_RSTHD,

    KC_MAC,    // Keys to change OS for shortcuts
    KC_WIN
};

// Shortcuts
enum shortcut_codes {
    // App-switcher
    SC_AS_START,
    SC_AS_RIGHT,
    SC_AS_LEFT,

    // Copy-paste
    SC_COPY,
    SC_PASTE,

    // Undo-redo
    SC_UNDO,
    SC_REDO,

};
#define SC(k) (pgm_read_word(&shortcut_codes[k][os_selection]))


// User config structure for EEPROM
typedef union {
    uint32_t raw;
    struct {
        uint8_t     os_selection :2;
    };
} user_config_t;


// variables defined in keymap.c
extern const uint16_t shortcut_codes[][2];
extern uint8_t os_selection;
extern user_config_t user_config;
extern uint16_t copy_paste_timer;
extern bool is_alt_tab_active;
extern uint16_t alt_tab_timer;

// functions defined in other files
void matrix_scan_encoder(void);

// Leader support
#ifdef LEADER_ENABLE
LEADER_EXTERNS();
void matrix_scan_leader(void);
#else
#define KC_LEAD KC_NO
#endif
