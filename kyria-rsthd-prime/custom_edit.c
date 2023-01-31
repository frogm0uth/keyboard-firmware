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
enum { ce_inactive, ce_waiting, ce_repeating };
static uint8_t custom_edit_state = ce_inactive;

static uint8_t  custom_edit_mods        = 0;
static uint16_t custom_edit_timer       = 0;
static uint16_t custom_edit_term        = CE_WAIT_TERM;
static uint16_t custom_edit_pressed_key = KC_NO;

static uint16_t ce_output_key             = KC_NO;
static uint8_t  ce_action_count           = 1;
static void (*ce_action_callback)(void)   = NULL;
static void (*ce_response_callback)(void) = NULL;

#define IS_EDIT_DELETE (custom_edit_mods & CE_MOD_BIT(CE_DELETE))
#define IS_EDIT_MORE (custom_edit_mods & CE_MOD_BIT(CE_MORE))
#define IS_EDIT_X5 (custom_edit_mods & CE_MOD_BIT(CE_X5))
#define IS_EDIT_FAST (custom_edit_mods & CE_MOD_BIT(CE_FAST))

#define CE_MOD_BIT(kc) (1U << (kc - CE_DELETE))

/*
 * Action callbacks. Each must do the thing only once.
 */
// Single key
void ce_action_tap_key(void) {
    tap_code16(ce_output_key);
}

// Shift the current keycode then emit delete
void ce_action_shift_and_delete(void) {
    tap_code16(S(ce_output_key));
    tap_code(KC_BSPC);
}

// Move to end of paragaph
void ce_action_move_end_of_paragraph(void) {
    tap_code(KC_RIGHT);
    tap_code16(SC(SC_END_OF_PARA));
    tap_code(KC_LEFT);
}

// Delete to end of paragaph
void ce_action_delete_end_of_paragraph(void) {
    tap_code(KC_RIGHT);
    tap_code16(S(SC(SC_END_OF_PARA)));
    tap_code16(S(KC_LEFT));
    tap_code(KC_BSPC);
    tap_code(KC_BSPC);
}
#ifdef NOTSUREWHICHISBETTER
void ce_action_delete_end_of_paragraph(void) {
    tap_code16(S(SC(SC_END_OF_PARA)));
    tap_code16(S(KC_LEFT));
    tap_code(KC_DEL);
}
#endif

/*
 * Response callbacks. Each must do an action ce_action_count times.
 */

// Call the current action ce_action_count times
void ce_call_action_n_times(void) {
    for (int n = 0; n < ce_action_count; n++) {
        (*ce_action_callback)();
    }
}

// Delete ce_action_count lines up or down
void ce_response_delete_lines_up_down(void) {
    tap_code16(SC(SC_START_OF_LINE));
    for (int n = 0; n < ce_action_count; n++) {
        tap_code16(ce_output_key == CE_UP ? S(KC_UP) : S(KC_DOWN));
        tap_code(KC_BSPC);
    }
    tap_code(KC_LEFT); // Helps reset cursor if it ends up on the wrong line... (macOS)
    tap_code(KC_RIGHT);
}

/*
 * Move the cursor in response to a keypress.
 */
void custom_edit_move(void) {
    // Set the default keycode
    switch (custom_edit_pressed_key) {
        case CE_LEFT:
            ce_output_key = KC_LEFT;
            break;

        case CE_RIGHT:
            ce_output_key = KC_RIGHT;
            break;

        case CE_UP:
            ce_output_key = KC_UP;
            break;

        case CE_DOWN:
            ce_output_key = KC_DOWN;
            break;

        case CE_HOME:
            ce_output_key = KC_HOME;
            break;

        case CE_END:
            ce_output_key = KC_END;
            break;

        case CE_PAGE_UP:
            ce_output_key = KC_PGUP;
            break;

        case CE_PAGE_DOWN:
            ce_output_key = KC_PGDN;
            break;
    }

    // If any normal modifiers are pressed, emit the key and return
    if (get_mods() & MOD_MASK_CAG) {
        tap_code16(ce_output_key);
        return;
    }

    // set defaults for callbacks
    ce_action_callback   = ce_action_tap_key;
    ce_response_callback = ce_call_action_n_times;

    // Change keycodes or callbacks as needed for custom edit
    if (!IS_EDIT_MORE) {
        switch (custom_edit_pressed_key) {
            case CE_HOME:
                ce_output_key = SC(SC_START_OF_LINE); // KC_HOME may not work on macOS, get better shortcut
                break;

            case CE_END:
                ce_output_key = SC(SC_END_OF_LINE); // KC_END may not work on macOS, get better shortcut
                break;
        }
    } else {
        switch (custom_edit_pressed_key) {
            case CE_LEFT:
                ce_output_key = SC(SC_WORD_LEFT);
                break;

            case CE_RIGHT:
                ce_output_key = SC(SC_WORD_RIGHT);
                break;

            case CE_UP:
                ce_output_key = SC(SC_REALPAGE_UP);
                break;

            case CE_DOWN:
                ce_output_key = SC(SC_REALPAGE_DOWN);
                break;

            case CE_HOME:
                ce_output_key = SC(SC_START_OF_PARA);
                break;

            case CE_END:
                ce_action_callback = ce_action_move_end_of_paragraph;
                break;

            case CE_PAGE_UP:
                ce_output_key = SC(SC_START_OF_DOC);
                break;

            case CE_PAGE_DOWN:
                ce_output_key = SC(SC_END_OF_DOC);
                break;
        }
    }
    // Do it
    (*ce_response_callback)();
}

/*
 * Delete text in response to a keypress.
 */
void custom_edit_delete(void) {
    // defaults for callbacks so we don't have to repeat it below
    ce_action_callback   = ce_action_tap_key;
    ce_response_callback = ce_call_action_n_times;

    if (!IS_EDIT_MORE) {
        switch (custom_edit_pressed_key) {
            case CE_LEFT:
                ce_output_key = KC_BSPC;
                break;

            case CE_RIGHT:
                ce_output_key = KC_DEL;
                break;

            case CE_UP:
            case CE_DOWN:
                ce_response_callback = ce_response_delete_lines_up_down;
                break;

            case CE_HOME:
                ce_output_key      = SC(SC_START_OF_LINE);
                ce_action_callback = ce_action_shift_and_delete;
                break;

            case CE_END:
                ce_output_key      = SC(SC_END_OF_LINE);
                ce_action_callback = ce_action_shift_and_delete;
                break;

            case CE_PAGE_UP:
                ce_output_key      = KC_PGUP;
                ce_action_callback = ce_action_shift_and_delete;
                break;

            case CE_PAGE_DOWN:
                ce_output_key      = KC_PGDN;
                ce_action_callback = ce_action_shift_and_delete;
                break;
        }
    } else {
        switch (custom_edit_pressed_key) {
            case CE_LEFT:
                ce_output_key = SC(SC_DEL_WORD_LEFT);
                break;

            case CE_RIGHT:
                ce_output_key = SC(SC_DEL_WORD_RIGHT);
                break;

            case CE_UP:
                ce_output_key = SC(SC_REALPAGE_UP);
                // ce_action_callback = ce_action_shift_and_delete;// doesn't work
                break;

            case CE_DOWN:
                ce_output_key = SC(SC_REALPAGE_DOWN);
                // ce_action_callback = ce_action_shift_and_delete; // doesn't work
                break;

            case CE_HOME:
                ce_output_key      = SC(SC_START_OF_PARA);
                ce_action_callback = ce_action_shift_and_delete;
                break;

            case CE_END:
                ce_action_callback = ce_action_delete_end_of_paragraph;
                break;

            case CE_PAGE_UP:
                ce_output_key      = SC(SC_START_OF_DOC);
                ce_action_callback = ce_action_shift_and_delete;
                break;

            case CE_PAGE_DOWN:
                ce_output_key      = SC(SC_END_OF_DOC);
                ce_action_callback = ce_action_shift_and_delete;
                break;
        }
    }
    // Do it
    (*ce_response_callback)();
}

void custom_edit_do(void) {
    if (IS_EDIT_X5) {
        ce_action_count = 5;
    } else {
        ce_action_count = 1;
    }
    if (IS_EDIT_DELETE) {
        custom_edit_delete();
    } else {
        custom_edit_move();
    }
    custom_edit_timer = timer_read();
}

void custom_edit_tick(void) { // Call from matrix_scan_user()
    switch (custom_edit_state) {
        case ce_inactive:
            break;

        case ce_waiting:
            if (timer_elapsed(custom_edit_timer) > custom_edit_term) {
                custom_edit_do();
                custom_edit_state = ce_repeating;
                custom_edit_term  = CE_REPEAT_TERM;
            }
            break;

        case ce_repeating:
            if (timer_elapsed(custom_edit_timer) > custom_edit_term) {
                custom_edit_do();
            }
            break;
    }
}

/*
 * Handle a custom edit keypress
 */
bool custom_edit_process_record(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CE_LEFT:
        case CE_RIGHT:
        case CE_UP:
        case CE_DOWN:
        case CE_HOME:
        case CE_END:
        case CE_PAGE_UP:
        case CE_PAGE_DOWN:
            if (record->event.pressed) {
                custom_edit_pressed_key = keycode;
                if (IS_EDIT_FAST) {
                    custom_edit_state = ce_repeating;
                    custom_edit_term  = CE_FAST_TERM;
                } else {
                    custom_edit_state = ce_waiting;
                    custom_edit_term  = CE_WAIT_TERM;
                }
                custom_edit_do();
            } else {
                custom_edit_pressed_key = KC_NO;
                custom_edit_state       = ce_inactive;
            }
            return false;
            break;

        case CE_DELETE:
        case CE_MORE:
        case CE_X5:
        case CE_FAST:
            if (record->event.pressed) {
                custom_edit_mods |= CE_MOD_BIT(keycode);
            } else {
                custom_edit_mods &= ~CE_MOD_BIT(keycode);
            }
            if (IS_EDIT_FAST && custom_edit_pressed_key != KC_NO) {
                custom_edit_do();
                custom_edit_state = ce_repeating;
                custom_edit_term  = CE_FAST_TERM;
            } else {
                custom_edit_term = CE_REPEAT_TERM;
            }
            return false;
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool custom_edit_encoder_ready() {
    return custom_edit_mods != 0;
}

// The encoder uses the modifiers differently to normal. MORE is word left/right,
// X5 is paragraph start/end, FAST is page up/down. DELETE is delete.
void custom_edit_encoder(bool clockwise) {
    // Default is to emit the keycode
    ce_action_callback = ce_action_tap_key;
    if (!IS_EDIT_DELETE) {
        if (IS_EDIT_FAST) {
            ce_output_key = clockwise ? KC_PGDN : KC_PGUP;

        } else if (IS_EDIT_X5) {
            if (clockwise) {
                ce_action_callback = ce_action_move_end_of_paragraph;
            } else {
                ce_output_key = SC(SC_START_OF_PARA);
            }

        } else if (IS_EDIT_MORE) {
            ce_output_key = clockwise ? SC(SC_WORD_RIGHT) : SC(SC_WORD_LEFT);
        }
    } else {
        if (IS_EDIT_FAST) {
            if (clockwise) {
                ce_output_key      = KC_PGDN;
                ce_action_callback = ce_action_shift_and_delete;
            } else {
                ce_output_key      = KC_PGUP;
                ce_action_callback = ce_action_shift_and_delete;
            }

        } else if (IS_EDIT_X5) {
            if (clockwise) {
                ce_action_callback = ce_action_delete_end_of_paragraph;
            } else {
                ce_output_key      = SC(SC_START_OF_PARA);
                ce_action_callback = ce_action_shift_and_delete;
            }

        } else if (IS_EDIT_MORE) {
            ce_output_key = clockwise ? SC(SC_DEL_WORD_RIGHT) : SC(SC_DEL_WORD_LEFT);

        } else {
            ce_output_key = clockwise ? KC_DEL : KC_BSPC;
        }
    }
    // Do it
    (*ce_action_callback)();
    ce_output_key = KC_NO;
}
#endif

#ifdef OLED_ENABLE
static const char PROGMEM str_blank1[]   = " ";
static const char PROGMEM str_blank3[]   = "   ";
static const char PROGMEM str_blank5[]   = "     ";
static const char PROGMEM str_blank6[]   = "      ";

void custom_edit_status(bool shift) {
    if (!shift) {
        if (IS_EDIT_DELETE) {
            oled_write_P(PSTR("DELETE"), false);
        } else {
            oled_write_P(str_blank6, false);
        }
    }
    oled_write_P(str_blank1, false);
    if (IS_EDIT_FAST) {
        oled_write_P(PSTR("FAST "), false);
    } else {
        oled_write_P(str_blank5, false);
    }
     if (IS_EDIT_X5) {
        oled_write_P(PSTR("X5 "), false);
    } else {
        oled_write_P(str_blank3, false);
    }
    if (IS_EDIT_MORE) {
        oled_write_P(PSTR("MORE "), false);
    }
}

static const char PROGMEM str_fast_left[]  = "^page  ";
static const char PROGMEM str_fast_right[] = "  pagev";
static const char PROGMEM str_x5_left[]    = "<para  ";
static const char PROGMEM str_x5_right[]   = "  para>";
static const char PROGMEM str_more_left[]  = "<word  ";
static const char PROGMEM str_more_right[] = "  word>";
static const char PROGMEM str_dflt_left[]  = "<char  ";
static const char PROGMEM str_dflt_right[] = "  char>";

void custom_edit_encoder_status() {
    const char *leftstring, *rightstring;

    if (IS_EDIT_FAST) {
        leftstring  = str_fast_left;
        rightstring = str_fast_right;
    } else if (IS_EDIT_X5) {
        leftstring  = str_x5_left;
        rightstring = str_x5_right;
    } else if (IS_EDIT_MORE) {
        leftstring  = str_more_left;
        rightstring = str_more_right;
    } else {
        leftstring  = str_dflt_left;
        rightstring = str_dflt_right;
    }
    oled_write_P(leftstring, false);
    if (IS_EDIT_DELETE) {
        oled_write_P(PSTR(" xxxx "), false);
    } else {
        oled_write_P(PSTR("      "), false);
    }
    oled_write_P(rightstring, false);
}
#endif
