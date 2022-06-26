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

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// clang-format off
static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, host_keyboard_led_state().caps_lock);
}

const static char* layer_names[] = {
    [ALPHA] = "ALPHA",
    [SYMS]  = "SYMS",
    [EDIT]  = "EDIT",
    [SNAP]  = "SNAP",
    [FUNC]  = "FUNC",
    [META]  = "META"
};

enum encoder_info_id {
  encstring_alttab = 0,
  encstring_volume,
  encstring_zoom,
  encstring_search,
  encstring_blank
};

const static char* encoder_info[] = {
    [encstring_alttab] = "<App            App>",
    [encstring_volume] = "<-     Volume     +>",
    [encstring_zoom]   = "<-      Zoom      +>",
    [encstring_search] = "<Prev  Search  Next>",
    [encstring_blank]  = "                    "
};

// clang-format on

static void render_version(void) {
    oled_write_P(PSTR("\nRSTHD/Prime v32\n"), false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();

    // Host Keyboard LED Status
    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR("        CAPS"), false);
    }
    oled_write_P(PSTR("\n"), false);

    // Display OS and layer
    uint8_t layer = get_highest_layer(layer_state);
#ifdef OS_SHORTCUTS
    os_shortcut_status();
    oled_write_P(PSTR(" :: "), false);
#endif
    oled_write(layer_names[layer], false);
    oled_write_P(PSTR("\n"), false);

    // Display modifiers
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_CSAG) {
        if (mods & MOD_MASK_SHIFT) {
            oled_write_P(PSTR("Shift "), false);
        }
        if (mods & MOD_MASK_ALT) {
            oled_write_P(PSTR("Alt "), false);
        }
        if (mods & MOD_MASK_CTRL) {
            oled_write_P(PSTR("Ctrl "), false);
        }
        if (mods & MOD_MASK_GUI) {
            oled_write_P(PSTR("Cmd "), false);
        }
    }

    // Custom status
    switch (layer) {
#ifdef CUSTOM_EDIT
        case EDIT:
            custom_edit_status();
            break;
#endif
    }
    oled_write_P(PSTR("\n"), false);

    // encoder help
    switch (layer) {
        case ALPHA:
            if (!(mods & MOD_MASK_CTRL)) {
                oled_write(encoder_info[encstring_alttab], false);
            } else {
                oled_write(encoder_info[encstring_volume], false);
            }
            break;

        case EDIT:
#ifdef CUSTOM_EDIT
            if (custom_edit_encoder_ready()) {
                custom_edit_encoder_status();
            } else {
                oled_write(encoder_info[encstring_zoom], false);
            }
#else
            oled_write(encoder_info[encstring_zoom], false);
#endif
            break;

        case META:
#ifdef RGBLIGHT_ENABLE
            if (!(mods & MOD_MASK_CAG)) {
                oled_write(encoder_info[encstring_search], false);
            } else {
                rgblight_oled_encoder_status();
            }
#else
            oled_write(encoder_info[encstring_search], false);
#endif
            break;

        default:
            oled_write(encoder_info[encstring_blank], false);
    }
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("         v32        "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_status(); // Renders the current keyboard state
    } else {
        render_qmk_logo(); // Static display
        render_version();
    }
    return false;
}
