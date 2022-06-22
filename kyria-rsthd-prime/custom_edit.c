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
#include QMK_KEYBOARD_H

#include "keymap.h"

/**
 ** Custom editing operations.  These are intended to make text editing more
 ** platform-independent (and faster).
 **/

static uint8_t  custom_edit_mods  = 0;
static uint16_t edit_keycode      = KC_NO;
static uint16_t custom_edit_timer = 0;
static uint16_t edit_repeat_term  = EDIT_REPEAT_TERM;

#define IS_EDIT_REPT (custom_edit_mods & CE_MOD_BIT(CE_REPT))
#define IS_EDIT_ACC1 (custom_edit_mods & CE_MOD_BIT(CE_ACC1))
#define IS_EDIT_ACC2 (custom_edit_mods & CE_MOD_BIT(CE_ACC2))
#define IS_EDIT_DMOD (custom_edit_mods & CE_MOD_BIT(CE_DMOD))

void custom_edit_delete(void) {
    int i, n;    //loop counters;

    switch (edit_keycode) {
        case CE_MV_L:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_START_OF_LINE)));    // Delete to start of line
                tap_code(KC_BSPC);
            } else {
                n = IS_EDIT_ACC1 ? 5 : 1;
                for (i = n; i > 0; i--) {
                    tap_code(KC_BSPC);    // Delete left
                }
            }
            break;

        case CE_MV_R:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_END_OF_LINE)));    // Delete to end of line
                tap_code(KC_DEL);
            } else {
                n = IS_EDIT_ACC1 ? 5 : 1;
                for (i = n; i > 0; i--) {
                    tap_code(KC_DEL);    // Delete right
                }
            }
            break;

        case CE_WD_L:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_START_OF_PARA)));    // Delete to start of paragraph
                tap_code(KC_BSPC);
            } else {
                n = IS_EDIT_ACC1 ? 5 : 1;
                for (i = n; i > 0; i--) {
                    tap_code16(SC(SC_DEL_WORD_LEFT));    // Delete words left
                }
            }
            break;

        case CE_WD_R:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_END_OF_PARA)));    // Delete to end of paragraph
                tap_code16(S(KC_LEFT));
                tap_code(KC_DEL);
            } else {
                n = IS_EDIT_ACC1 ? 5 : 1;
                for (i = n; i > 0; i--) {
                    tap_code16(SC(SC_DEL_WORD_RIGHT));    // Delete words right
                }
            }
            break;

        case CE_MV_U:
        case CE_MV_D:
            n = IS_EDIT_ACC2 ? 12 : (IS_EDIT_ACC1 ? 5 : 1);
            tap_code16(SC(SC_START_OF_LINE));    // Delete whole lines up or down
            for (i = n; i > 0; i--) {
                tap_code16(edit_keycode == CE_MV_U ? S(KC_UP) : S(KC_DOWN));
                tap_code(KC_BSPC);
            }
            tap_code(KC_LEFT);    // Helps reset cursor if it ends up on the wrong line... (macOS)
            tap_code(KC_RIGHT);
            break;

        case CE_PG_U:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_START_OF_DOC)));    // Delete to start of document
                tap_code(KC_BSPC);
            } else {
                // do nothing (?)
            }
            break;

        case CE_PG_D:
            if (IS_EDIT_ACC2) {
                tap_code16(S(SC(SC_END_OF_DOC)));    // Delete to end of document
                tap_code(KC_DEL);
            } else {
                // do nothing (?)
            }
            break;
    }
}

void custom_edit_move(void) {
    int     i, n;    //loop counters;
    uint8_t mods = get_mods();
    uint8_t key  = KC_NO;

    if (mods & MOD_MASK_CAG) {
        // Act like conventional keys plus modifier
        switch (edit_keycode) {
            case CE_MV_L:
                key = KC_LEFT;
                break;
            case CE_MV_R:
                key = KC_RIGHT;
                break;
            case CE_WD_L:
                key = KC_HOME;
                break;
            case CE_WD_R:
                key = KC_END;
                break;
            case CE_MV_U:
                key = KC_UP;
                break;
            case CE_MV_D:
                key = KC_DOWN;
                break;
            case CE_PG_U:
                key = KC_PGUP;
                break;
            case CE_PG_D:
                key = KC_PGDN;
                break;
        }
        tap_code(key);

    } else {
        switch (edit_keycode) {
            case CE_MV_L:
            case CE_MV_R:
                if (IS_EDIT_ACC2) {
                    tap_code16(edit_keycode == CE_MV_L ? SC(SC_START_OF_LINE) : SC(SC_END_OF_LINE));    // Start or end of line
                } else {
                    n = IS_EDIT_ACC1 ? 5 : 1;
                    for (i = n; i > 0; i--) {
                        tap_code(edit_keycode == CE_MV_L ? KC_LEFT : KC_RIGHT);    // Move left or right
                    }
                }
                break;

            case CE_WD_L:
            case CE_WD_R:
                if (IS_EDIT_ACC2) {
                    tap_code16(edit_keycode == CE_WD_L ? SC(SC_START_OF_PARA) : SC(SC_END_OF_PARA));    // Start or end of paragraph
                } else {
                    n = IS_EDIT_ACC1 ? 5 : 1;
                    for (i = n; i > 0; i--) {
                        tap_code16(edit_keycode == CE_WD_L ? SC(SC_WORD_LEFT) : SC(SC_WORD_RIGHT));    // Move word left or right
                    }
                }
                break;

            case CE_MV_U:
            case CE_MV_D:
                n = IS_EDIT_ACC2 ? 12 : (IS_EDIT_ACC1 ? 5 : 1);
                for (i = n; i > 0; i--) {
                    tap_code(edit_keycode == CE_MV_U ? KC_UP : KC_DOWN);    // Move lines up or down
                }
                break;

            case CE_PG_U:
            case CE_PG_D:
                if (IS_EDIT_ACC2) {
                    // Move to start or end of document NB Doesn't work in Word on macOS
                    tap_code16(edit_keycode == CE_PG_U ? SC(SC_START_OF_DOC) : SC(SC_END_OF_DOC));
                } else {
                    n = IS_EDIT_ACC1 ? 6 : 1;
                    for (i = n; i > 0; i--) {
                        tap_code(edit_keycode == CE_PG_U ? KC_PGUP : KC_PGDN);    // Move page/s up or down
                    }
                }
                break;
        }
        custom_edit_timer = timer_read();
    }
}

void custom_edit_action(void) {
    if (IS_EDIT_DMOD) {
        custom_edit_delete();
    } else {
        custom_edit_move();
    }
    custom_edit_timer = timer_read();
}

void custom_edit_tick(void) {    // Call from matrix_scan_user()
    if (IS_EDIT_REPT) {
        if (timer_elapsed(custom_edit_timer) > edit_repeat_term) {
            custom_edit_action();
        }
    }
}

void custom_edit_mod(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        custom_edit_mods |= CE_MOD_BIT(keycode);
    } else {
        custom_edit_mods &= ~CE_MOD_BIT(keycode);
    }
}

void custom_edit_record(uint16_t keycode, bool pressed) {
    if (pressed) {
        edit_keycode = keycode;
        custom_edit_action();
    } else {
        edit_keycode = KC_NO;
    }
}

void custom_edit_tap(uint16_t keycode) {
    edit_keycode = keycode;
    custom_edit_action();
    edit_keycode = KC_NO;
}

#ifdef ENCODER_ENABLE
void custom_edit_encoder(bool clockwise) {
    uint16_t keycode = KC_NO;
    if (IS_EDIT_REPT) {    // Not really repeat, just change to vertical
        custom_edit_record(clockwise ? CE_MV_D : CE_MV_U, true);
        custom_edit_record(clockwise ? CE_MV_D : CE_MV_U, false);
    } else {
        // encoder is more limited than keys, so special handling of accelerators
        if (!IS_EDIT_DMOD) {
            if (IS_EDIT_ACC1) {
                keycode = clockwise ? SC(SC_WORD_RIGHT) : SC(SC_WORD_LEFT);
            } else if (IS_EDIT_ACC2) {
                keycode = clockwise ? SC(SC_END_OF_PARA) : SC(SC_START_OF_PARA);
            } else {
                keycode = clockwise ? KC_RIGHT : KC_LEFT;
            }
        } else {    // Delete modifier is active
            if (IS_EDIT_ACC1) {
                keycode = clockwise ? SC(SC_DEL_WORD_RIGHT) : SC(SC_DEL_WORD_LEFT);
            } else if (IS_EDIT_ACC2) {
                if (clockwise) {
                    tap_code16(S(SC(SC_END_OF_PARA)));    // Delete to end of paragraph
                    tap_code16(S(KC_LEFT));
                    tap_code(KC_DEL);
                } else {
                    tap_code16(S(SC(SC_START_OF_PARA)));    // Delete to start of paragraph
                    tap_code(KC_BSPC);
                }
            } else {
                keycode = clockwise ? KC_DEL : KC_BSPC;
            }
        }
        if (keycode != KC_NO) {
            tap_code16(keycode);
        }
    }
}
#endif

#ifdef OLED_DRIVER_ENABLE
void custom_edit_status() {
    if (IS_EDIT_DMOD) {
        oled_write_P(PSTR("DEL "), false);
    }
    if (IS_EDIT_REPT) {
        oled_write_P(PSTR("RPT "), false);
    }
    if (IS_EDIT_ACC1) {
        oled_write_P(PSTR("+1 "), false);
    }
    if (IS_EDIT_ACC2) {
        oled_write_P(PSTR("+2 "), false);
    }
}
#endif
