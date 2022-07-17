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
#   include "os_shortcut_defs.h"
    DEFINE_SHORTCUT( ID_END, KC_NO, KC_NO, KC_NO )
};
#endif
// clang-format on

/**
 * Implement default processing for custom keycodes for each shortcut.
 */
#ifndef OS_SHORTCUTS_STATIC
void process_record_shortcut(uint16_t keycode, keyrecord_t *record) {
    if (keycode > SC_ID_START && keycode < SC_ID_END) {
        uint16_t shortcut = SC(keycode);
        if (record->event.pressed) {
            register_code16(shortcut);
        } else {
            unregister_code16(shortcut);
        }
    }
}
#endif

/**
 * Set the OS from a keycode. Call this from a keycode handler in
 * process_record_user(). Not persistent.
 */
#ifndef OS_SHORTCUTS_STATIC
void os_set_from_keycode(uint16_t keycode) {
    switch (keycode) {
        case CU_SELECT_MACOS:
            os_index = os_platform_macos;
            break;

        case CU_SELECT_WINDOWS:
            os_index = os_platform_windows;
            break;

        case CU_SELECT_LINUX:
            os_index = os_platform_linux;
            break;
    }
}
#endif

/**
 * Display the selected OS on the OLED.
 */
// clang-format off
#ifdef OLED_ENABLE
void os_shortcut_status (bool invert) {
#ifdef OS_SHORTCUTS_STATIC
#ifdef OS_MACOS
    oled_write_P(PSTR("   MACOS"), invert);
#else
    #ifdef OS_WINDOWS
        oled_write_P(PSTR(" WINDOWS"), invert);
    #else
        oled_write_P(PSTR("   LINUX"), invert);
    #endif
#endif
#else
    switch (os_index) {
        case os_platform_macos:
            oled_write_P(PSTR("   MACOS"), invert);
            break;
        case os_platform_windows:
            oled_write_P(PSTR(" WINDOWS"), invert);
            break;
        case os_platform_linux:
            oled_write_P(PSTR("   LINUX"), invert);
            break;
    }
#endif
}
#endif
// clang-format on
