/* Copyright 2020-2023 @frogm0uth
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

#include "keymap.h"

/**
 ** Platform-dependent shortcuts.
 **/

#ifndef OS_SHORTCUTS_STATIC
#    ifdef OS_WINDOWS
uint8_t os_index = os_platform_windows;
#    else
#        ifdef OS_MACOS
uint8_t os_index = os_platform_macos;
#        else
uint8_t os_index = os_platform_linux;
#        endif
#    endif

void os_set_raw(uint8_t os) {
    os_index = os;
}
uint8_t os_get_raw() {
    return os_index;
}
#endif

/**
 *  The array of codes for dynamically accessed shortcuts.
 */
// clang-format off
#ifndef OS_SHORTCUTS_STATIC
#undef  DEFINE_SHORTCUT
#define DEFINE_SHORTCUT(name,mac,win,linux) [OS_SC_OFFSET(SC_ ## name)] = { mac, win, linux },

const uint16_t PROGMEM os_shortcut_codes[][3] = {
    DEFINE_SHORTCUT( ID_START, KC_NO, KC_NO, KC_NO )
#   include "../common/os_shortcut_defs.h"
    DEFINE_SHORTCUT( ID_END, KC_NO, KC_NO, KC_NO )
};
#endif
// clang-format on

/**
 * Implement default processing for custom keycodes for each shortcut.
 */
#ifndef OS_SHORTCUTS_STATIC
bool process_record_shortcut(uint16_t keycode, keyrecord_t *record) {
    if (keycode > SC_ID_START && keycode < SC_ID_END) {
        uint16_t shortcut = SC(keycode);
        if (record->event.pressed) {
            register_code16(shortcut);
        } else {
            unregister_code16(shortcut);
        }
        return false;
    }
    return true;
}
#endif

/**
 * Set the OS from a keycode. Call this from a keycode handler in
 * process_record_user(). Not persistent.
 */
#ifndef OS_SHORTCUTS_STATIC
void os_set_from_keycode(uint16_t keycode) {
    switch (keycode) {
        case CU_MACOS:
            os_index = os_platform_macos;
            break;

        case CU_WINDOWS:
            os_index = os_platform_windows;
            break;

        case CU_LINUX:
            os_index = os_platform_linux;
            break;
    }
}
#endif

/**
 * Functions for displaying shortcut status on the OLED
 */
// clang-format off
#ifdef OLED_ENABLE
static const char PROGMEM str_mod_gui[]   = "Gui  ";
static const char PROGMEM str_mod_cmd[]   = "Cmd  ";
static const char PROGMEM str_mod_super[] = "Super"; // hopefully this comes at the end of the line

static const char PROGMEM str_os_macos[]   = "   MACOS";
static const char PROGMEM str_os_windows[] = " WINDOWS";
static const char PROGMEM str_os_linux[]   = "   LINUX";

// Display the selected OS on the OLED.
void os_shortcut_status (bool invert) {
#ifdef OS_SHORTCUTS_STATIC
#ifdef OS_MACOS
    oled_write_P(str_os_macos, invert);
#else
    #ifdef OS_WINDOWS
        oled_write_P(str_os_windows, invert);
    #else
        oled_write_P(str_os_linux, invert);
    #endif
#endif
#else
    switch (os_index) {
        case os_platform_macos:
            oled_write_P(str_os_macos, invert);
            break;
        case os_platform_windows:
            oled_write_P(str_os_windows, invert);
            break;
        case os_platform_linux:
            oled_write_P(str_os_linux, invert);
            break;
    }
#endif
}

// Display the Gui/Cmd/Super string on the OLED.
void os_shortcut_cmd_status (bool invert) {
#ifdef OS_SHORTCUTS_STATIC
#ifdef OS_MACOS
    oled_write_P(str_mod_cmd, invert);
#else
    #ifdef OS_WINDOWS
        oled_write_P(str_mod_gui, invert);
    #else
        oled_write_P(str_mod_super, invert);
    #endif
#endif
#else
    switch (os_index) {
        case os_platform_macos:
            oled_write_P(str_mod_cmd, invert);
            break;
        case os_platform_windows:
            oled_write_P(str_mod_gui, invert);
            break;
        case os_platform_linux:
            oled_write_P(str_mod_super, invert);
            break;
    }
#endif
}
#endif
// clang-format on
