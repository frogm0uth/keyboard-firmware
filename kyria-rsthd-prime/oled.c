/*
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
#include QMK_KEYBOARD_H

#include "keymap.h"

// Print byte as hex to OLED
#ifdef OLED_ENABLE
static char hexchars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void oled_print_hex(uint8_t n) {
    oled_write_P(PSTR("0x"), false);
    oled_write_char(hexchars[(n >> 4) & 0x0F], false);
    oled_write_char(hexchars[n & 0x0F], false);
}
#endif

#ifdef ENCODER_ENABLE
void oled_brightness_encoder_status(void) {
    oled_write_P(PSTR("<-   OLED="), false);
    oled_print_hex(oled_get_brightness());
    oled_write_P(PSTR("    +>"), false);
}
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
void rgblight_oled_encoder_status(void) {
    uint8_t mods = get_mods();
    oled_write_P(PSTR("<-    "), false);

    if (mods & (MOD_MASK_CTRL)) {
        oled_write_P(PSTR("HUE="), false);
        oled_print_hex(rgblight_get_hue());
    } else if (mods & MOD_MASK_ALT) {
        oled_write_P(PSTR("SAT="), false);
        oled_print_hex(rgblight_get_sat());
    } else if (mods & MOD_MASK_GUI) {
        oled_write_P(PSTR("VAL="), false);
        oled_print_hex(rgblight_get_val());
    }
    oled_write_P(PSTR("    +>"), false);
}
#endif

#ifndef OLED_BRIGHTNESS_INCREMENT
#    define OLED_BRIGHTNESS_INCREMENT 0x10
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// clang-format off
static void render_qmk_logo(bool invert) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, invert);
}
// clang-format on

static const char PROGMEM str_layer_alpha[] = "ALPHA   ";
static const char PROGMEM str_layer_syms[]  = "SYMS    ";
static const char PROGMEM str_layer_edit[]  = "EDIT    ";
static const char PROGMEM str_layer_meta[]  = "META    ";
static const char PROGMEM str_layer_func[]  = "FUNC    ";
static const char PROGMEM str_layer_snap[]  = "SNAP    ";

// clang-format off
const static char* layer_names[] = {
    [ALPHA] = str_layer_alpha,
    [SYMS]  = str_layer_syms,
    [EDIT]  = str_layer_edit,
    [META]  = str_layer_meta,
    [FUNC]  = str_layer_func,
    [SNAP]  = str_layer_snap
};
//clang-format on

#ifdef ENCODER_ENABLE
static const char PROGMEM str_encoder_volume[]  = "<-     Volume     +>";
static const char PROGMEM str_encoder_zoom[]    = "<-      Zoom      +>";
static const char PROGMEM str_encoder_search[]  = "<Prev  Search  Next>";
static const char PROGMEM str_encoder_history[] = "<Undo          Redo>";
static const char PROGMEM str_encoder_blank[]   = "                    ";
#endif

static const char PROGMEM str_oled_header[]     = "     RSTHD/Prime    ";
static const char PROGMEM str_oled_version[]    = "         v40        ";
static const char PROGMEM str_oled_caps[]       = "        CAPS        ";
static const char PROGMEM str_oled_newline[]    = "\n";

static const char PROGMEM str_mod_shift[] = "Shift ";
static const char PROGMEM str_mod_ctrl[]  = "Ctrl ";
static const char PROGMEM str_mod_alt[]   = "Alt ";
static const char PROGMEM str_mod_gui[]   = "Gui ";
static const char PROGMEM str_mod_rpt[]   = "RPT ";

//static const char PROGMEM str_mod_alt_macos[]   = "Opt ";

//static const char PROGMEM str_mod_gui_macos[]   = "Cmd";
//static const char PROGMEM str_mod_gui_linux[]   = "Super";

static const char PROGMEM str_blank4[]   = "    ";
static const char PROGMEM str_blank5[]   = "     ";
static const char PROGMEM str_blank6[]   = "      ";


static void render_status(void) {
    bool capslock = host_keyboard_led_state().caps_lock;
    bool invert = capslock;

    // QMK Logo and version information
    render_qmk_logo(invert);

    // Host Keyboard LED Status
    invert = false;
    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(str_oled_caps, false);
    }
    oled_write_P(str_oled_newline, false);

    // Display OS and layer
#ifdef CUSTOM_CAPSWORD
    invert = capslock && !is_capsword_active();
#else
    invert = capslock;
#endif
    uint8_t layer = get_highest_layer(layer_state);
#ifdef OS_SHORTCUTS
    os_shortcut_status(invert);
    oled_write_P(PSTR(" :: "), invert);
#endif
    oled_write_P(layer_names[layer], invert);
    oled_write_P(PSTR("\n"), invert);

    // Display modifiers
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t ossmods = get_oneshot_mods();
#else
    uint8_t ossmods = mods;
#endif

#ifndef NO_ACTION_ONESHOT
    if (ossmods & MOD_MASK_CSAG) {
        oled_write_P(PSTR("One-shot "), false);
    }
#endif
    if (is_repeat_active()) {
        oled_write_P(PSTR(str_mod_rpt), true);
    }
    if ((mods | ossmods) & MOD_MASK_SHIFT) {
        oled_write_P(str_mod_shift, false);
    } else {
        if (layer != EDIT) {
            oled_write_P(str_blank6, false);                        
        }
    }
    if ((mods | ossmods) & MOD_MASK_CAG) {
        if ((mods | ossmods) & MOD_MASK_CTRL) {
            oled_write_P(str_mod_ctrl, false);
        } else {
            oled_write_P(str_blank5, false);            
        }
        if ((mods | ossmods) & MOD_MASK_ALT) {
            oled_write_P(str_mod_alt, false);
        } else {
            oled_write_P(str_blank4, false);            
        }
        if ((mods | ossmods) & MOD_MASK_GUI) {
            oled_write_P(str_mod_gui, false);
        }
    }
#ifdef CUSTOM_EDIT
    else {
        if (layer == EDIT) {
            custom_edit_status((mods | ossmods) & MOD_MASK_SHIFT);
        }
    }
#endif
    oled_write_P(str_oled_newline, false);

#ifdef ENCODER_ENABLE
    // encoder help
    switch (layer) {
        case ALPHA:
            oled_write_P(str_encoder_volume, false);
            break;

        case EDIT:
        case SYMS:
#    ifdef CUSTOM_EDIT
            if (custom_edit_encoder_ready()) {
                custom_edit_encoder_status();
            } else {
                oled_write_P(str_encoder_history, false);
            }
#    else
            oled_write_P(str_encoder_history, false);
#    endif
            break;

        case META:
            oled_write_P(str_encoder_search, false);
            break;

        case SNAP:
        case FUNC:
            if (mods & MOD_MASK_CAG) {
#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
                rgblight_oled_encoder_status();
#    endif
            } else if (mods & MOD_MASK_SHIFT) {
                oled_brightness_encoder_status();
            } else {
                oled_write_P(str_encoder_zoom, false);
            }
            break;

        default:
            oled_write_P(str_encoder_blank, false);
    }
#endif
    oled_write_P(str_oled_newline, false);
#ifndef NO_ACTION_ONESHOT
    oled_write_P(str_oled_version, ossmods & MOD_MASK_CSAG);
#else
    oled_write_P(str_oled_version, false);
#endif
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state
    } else {
        render_qmk_logo(false); // Static display
        oled_write_P(str_oled_newline, false);
        oled_write_P(str_oled_header,  false);
        oled_write_P(str_oled_newline, false);
        oled_write_P(str_oled_newline, false);
        oled_write_P(str_oled_newline, false);
        oled_write_P(str_oled_version, false);
    }
    return false;
}
