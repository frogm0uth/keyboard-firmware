
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

/** Combo implementation. Combos are defined in combo_defs.h.
 *
 * Macros for combos adapted from:
 *
 * https://github.com/sevanteri/qmk_firmware/blob/9cca95785e6fd5001367d02fceddae628f6d48c9/users/sevanteri/combos.h
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/gboards/g/keymap_combo.h
 */

#include "config.h"
#include "keymap.h"


/*
 * Timeout for comborolls / directional QMK combos 
 */
#ifndef COMBOROLL_TERM
#    define COMBOROLL_TERM 120
#endif

// Emit an array of keycodes in PROGMEM
void process_combo_array(const uint16_t *keyptr) {
    uint16_t keycode = pgm_read_word(keyptr++);
    while (keycode != KC_NO) {
        tap_code16(keycode);
        keycode = pgm_read_word(keyptr++);
    }
}

// Emit a PROGMEM string, clear all mods after first character
void process_combo_string(const char *str) {
    char ch = pgm_read_byte(str++);
    send_char(ch);
    clear_mods();
    ch = pgm_read_byte(str++);
    while (ch) {
        send_char(ch);
        ch = pgm_read_byte(str++);
    }
}

// clang-format off
#undef  ARRAY_PROTECT
#define ARRAY_PROTECT(...) __VA_ARGS__ 

// _____TRM is empty until the last set
#define _____TRM(name, ms)
#define ___NOSFT(name)

// Enum for combo codes
#define CMBO_KEY(name, out, ...)  COMBO_ID_##name,
#define CMBO_ARR(name, out, ...)  COMBO_ID_##name,
#define CMBO_LIT(name, out, ...)  COMBO_ID_##name,
#define CMBO_STR(name, ...)       COMBO_ID_##name,

#define LtoR_KEY CMBO_KEY
#define LtoR_ARR CMBO_ARR
#define LtoR_LIT CMBO_LIT
#define LtoR_STR CMBO_STR

#define RtoL_KEY CMBO_KEY
#define RtoL_ARR CMBO_ARR
#define RtoL_LIT CMBO_LIT
#define RtoL_STR CMBO_STR

enum combo_events {
#   include "../common/combo_defs.h"
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;


// Define combo key sequences in memory
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};
#define CMBO_ARR(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END}; \
                                  const uint16_t PROGMEM combo_array_##name[] = { out, KC_NO };
#define CMBO_LIT(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};
#define CMBO_STR(name, ...)       const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};

#define LtoR_KEY CMBO_KEY
#define LtoR_ARR CMBO_ARR
#define LtoR_LIT CMBO_LIT
#define LtoR_STR CMBO_STR

#define RtoL_KEY(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};
#define RtoL_ARR(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END}; \
                                     const uint16_t PROGMEM combo_array_##name[] = { out, KC_NO };
#define RtoL_LIT(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};
#define RtoL_STR(name, k1, k2)       const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};

#include "../common/combo_defs.h"


// Define mapping from key sequences to combo codes or actions
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, out, ...)  [COMBO_ID_##name] = COMBO(COMBO_SEQ_##name, out),
#define CMBO_ARR(name, out, ...)  [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),
#define CMBO_STR(name, out, ...)  [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),
#define CMBO_LIT(name, ...)       [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),

#define LtoR_KEY CMBO_KEY
#define LtoR_ARR CMBO_ARR
#define LtoR_LIT CMBO_LIT
#define LtoR_STR CMBO_STR

#define RtoL_KEY CMBO_KEY
#define RtoL_ARR CMBO_ARR
#define RtoL_LIT CMBO_LIT
#define RtoL_STR CMBO_STR

combo_t key_combos[] = {
#   include "../common/combo_defs.h"
};


// Execute code for action combos
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, out, ...)
#define CMBO_ARR(name, out, ...)  case COMBO_ID_##name: process_combo_array(combo_array_##name); break;
#define CMBO_LIT(name, out, ...)  case COMBO_ID_##name: process_combo_string(PSTR(out)); break;
#define CMBO_STR(name, ...)       case COMBO_ID_##name: process_combo_string(PSTR(#name)); break;

#define LtoR_KEY CMBO_KEY
#define LtoR_ARR CMBO_ARR
#define LtoR_LIT CMBO_LIT
#define LtoR_STR CMBO_STR

#define RtoL_KEY CMBO_KEY
#define RtoL_ARR CMBO_ARR
#define RtoL_LIT CMBO_LIT
#define RtoL_STR CMBO_STR

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t mods = get_mods();

    if (pressed) {
        switch(combo_index) {
#           include "../common/combo_defs.h"
        }
    }
    set_mods(mods);
}

// Whether keys must be pressed in order
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, out, ...)
#define CMBO_ARR(name, out, ...)
#define CMBO_LIT(name, out, ...)
#define CMBO_STR(name, ...)

#define LtoR_KEY(name, out, ...) case COMBO_ID_##name: return true; break;
#define LtoR_ARR LtoR_KEY
#define LtoR_LIT LtoR_KEY
#define LtoR_STR LtoR_KEY

#define RtoL_KEY LtoR_KEY
#define RtoL_ARR LtoR_KEY
#define RtoL_LIT LtoR_KEY
#define RtoL_STR LtoR_KEY

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
#       include "../common/combo_defs.h"
        default:
          return false;
    }
}


// Provide the timing data
#undef  CMBO_KEY
#undef  CMBO_ARR
#undef  CMBO_STR
#undef  CMBO_LIT

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define CMBO_KEY(name, out, ...)
#define CMBO_ARR(name, out, ...)
#define CMBO_LIT(name, out, ...)
#define CMBO_STR(name, ...)

#define LtoR_KEY(name, out, ...) case COMBO_ID_##name: combo_term = COMBOROLL_TERM; break;
#define LtoR_ARR LtoR_KEY
#define LtoR_LIT LtoR_KEY
#define LtoR_STR LtoR_KEY

#define RtoL_KEY LtoR_KEY
#define RtoL_ARR LtoR_KEY
#define RtoL_LIT LtoR_KEY
#define RtoL_STR LtoR_KEY

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    uint16_t combo_term = COMBO_TERM;
    switch (index) {
#       include "../common/combo_defs.h"
    }

#undef  _____TRM
#define _____TRM(name, ms) case COMBO_ID_##name: combo_term = ms; break;

#undef  LtoR_KEY
#undef  LtoR_ARR
#undef  LtoR_LIT
#undef  LtoR_STR

#undef  RtoL_KEY
#undef  RtoL_ARR
#undef  RtoL_LIT
#undef  RtoL_STR

#define LtoR_KEY(name, out, ...)
#define LtoR_ARR LtoR_KEY
#define LtoR_LIT LtoR_KEY
#define LtoR_STR LtoR_KEY

#define RtoL_KEY LtoR_KEY
#define RtoL_ARR LtoR_KEY
#define RtoL_LIT LtoR_KEY
#define RtoL_STR LtoR_KEY

    switch (index) {
#       include "../common/combo_defs.h"
    }
    
    return combo_term;
}

// Make all combos tap-only, to avoid late triggering if combos overlap
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    return true;
}
