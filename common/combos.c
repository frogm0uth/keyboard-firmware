
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

// Define comboroll macros as empty
#define LtoR_KEY(name, ...)
#define LtoR_ARR(name, ...)
#define LtoR_LIT(name, ...)
#define LtoR_STR(name, ...)
#define LtoR_TRM(name, ...)

#define RtoL_KEY(name, ...)
#define RtoL_ARR(name, ...)
#define RtoL_LIT(name, ...)
#define RtoL_STR(name, ...)
#define RtoL_TRM(name, ...)

#define CMBO_KEY(name, ...)
#define CMBO_ARR(name, ...)
#define CMBO_LIT(name, ...)
#define CMBO_STR(name, ...)
#define CMBO_TRM(name, ...)

// clang-format off
#undef  ARRAY_PROTECT
#define ARRAY_PROTECT(...) __VA_ARGS__ 

// Empty until the last definition
#define Q_CMBO_TRM(name, ms)
#define Q_RtoL_TRM(name, ms)
#define Q_LtoR_TRM(name, ms)
#define _ONSHIFT(name)

// Enum for combo codes
#define Q_CMBO_KEY(name, out, ...)  COMBO_ID_##name,
#define Q_CMBO_ARR(name, out, ...)  COMBO_ID_##name,
#define Q_CMBO_LIT(name, out, ...)  COMBO_ID_##name,
#define Q_CMBO_STR(name, ...)       COMBO_ID_##name,

#define Q_LtoR_KEY Q_CMBO_KEY
#define Q_LtoR_ARR Q_CMBO_ARR
#define Q_LtoR_LIT Q_CMBO_LIT
#define Q_LtoR_STR Q_CMBO_STR

#define Q_RtoL_KEY Q_CMBO_KEY
#define Q_RtoL_ARR Q_CMBO_ARR
#define Q_RtoL_LIT Q_CMBO_LIT
#define Q_RtoL_STR Q_CMBO_STR

enum combo_events {
#   include "combo_defs.h"
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;


// Define combo key sequences in memory
#undef  Q_CMBO_KEY
#undef  Q_CMBO_ARR
#undef  Q_CMBO_STR
#undef  Q_CMBO_LIT

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR

#define Q_CMBO_KEY(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};
#define Q_CMBO_ARR(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END}; \
                                  const uint16_t PROGMEM combo_array_##name[] = { out, KC_NO };
#define Q_CMBO_LIT(name, out, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};
#define Q_CMBO_STR(name, ...)       const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};

#define Q_LtoR_KEY Q_CMBO_KEY
#define Q_LtoR_ARR Q_CMBO_ARR
#define Q_LtoR_LIT Q_CMBO_LIT
#define Q_LtoR_STR Q_CMBO_STR

#define Q_RtoL_KEY(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};
#define Q_RtoL_ARR(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END}; \
                                     const uint16_t PROGMEM combo_array_##name[] = { out, KC_NO };
#define Q_RtoL_LIT(name, out, k1, k2)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};
#define Q_RtoL_STR(name, k1, k2)       const uint16_t PROGMEM COMBO_SEQ_##name[] = {k2, k1, COMBO_END};

#include "combo_defs.h"


// Define mapping from key sequences to combo codes or actions
#undef  Q_CMBO_KEY
#undef  Q_CMBO_ARR
#undef  Q_CMBO_STR
#undef  Q_CMBO_LIT

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR

#define Q_CMBO_KEY(name, out, ...)  [COMBO_ID_##name] = COMBO(COMBO_SEQ_##name, out),
#define Q_CMBO_ARR(name, out, ...)  [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),
#define Q_CMBO_STR(name, out, ...)  [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),
#define Q_CMBO_LIT(name, ...)       [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),

#define Q_LtoR_KEY Q_CMBO_KEY
#define Q_LtoR_ARR Q_CMBO_ARR
#define Q_LtoR_LIT Q_CMBO_LIT
#define Q_LtoR_STR Q_CMBO_STR

#define Q_RtoL_KEY Q_CMBO_KEY
#define Q_RtoL_ARR Q_CMBO_ARR
#define Q_RtoL_LIT Q_CMBO_LIT
#define Q_RtoL_STR Q_CMBO_STR

combo_t key_combos[] = {
#   include "combo_defs.h"
};


// Execute code for action combos
#undef  Q_CMBO_KEY
#undef  Q_CMBO_ARR
#undef  Q_CMBO_STR
#undef  Q_CMBO_LIT

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR

#define Q_CMBO_KEY(name, out, ...)
#define Q_CMBO_ARR(name, out, ...)  case COMBO_ID_##name: emit_progmem_array(combo_array_##name); break;
#define Q_CMBO_LIT(name, out, ...)  case COMBO_ID_##name: emit_progmem_string(PSTR(out)); break;
#define Q_CMBO_STR(name, ...)       case COMBO_ID_##name: emit_progmem_string(PSTR(#name)); break;

#define Q_LtoR_KEY Q_CMBO_KEY
#define Q_LtoR_ARR Q_CMBO_ARR
#define Q_LtoR_LIT Q_CMBO_LIT
#define Q_LtoR_STR Q_CMBO_STR

#define Q_RtoL_KEY Q_CMBO_KEY
#define Q_RtoL_ARR Q_CMBO_ARR
#define Q_RtoL_LIT Q_CMBO_LIT
#define Q_RtoL_STR Q_CMBO_STR

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t mods = get_mods();

    if (pressed) {
        switch(combo_index) {
#           include "combo_defs.h"
        }
    }
    set_mods(mods);
}

// Whether keys must be pressed in order
#undef  Q_CMBO_KEY
#undef  Q_CMBO_ARR
#undef  Q_CMBO_STR
#undef  Q_CMBO_LIT

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR

#define Q_CMBO_KEY(name, out, ...)
#define Q_CMBO_ARR(name, out, ...)
#define Q_CMBO_LIT(name, out, ...)
#define Q_CMBO_STR(name, ...)

#define Q_LtoR_KEY(name, out, ...) case COMBO_ID_##name: return true; break;
#define Q_LtoR_ARR Q_LtoR_KEY
#define Q_LtoR_LIT Q_LtoR_KEY
#define Q_LtoR_STR Q_LtoR_KEY

#define Q_RtoL_KEY Q_LtoR_KEY
#define Q_RtoL_ARR Q_LtoR_KEY
#define Q_RtoL_LIT Q_LtoR_KEY
#define Q_RtoL_STR Q_LtoR_KEY

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
#       include "combo_defs.h"
        default:
          return false;
    }
}


// Provide the timing data
#undef  Q_CMBO_KEY
#undef  Q_CMBO_ARR
#undef  Q_CMBO_STR
#undef  Q_CMBO_LIT

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR

#define Q_CMBO_KEY(name, out, ...)
#define Q_CMBO_ARR(name, out, ...)
#define Q_CMBO_LIT(name, out, ...)
#define Q_CMBO_STR(name, ...)

#define Q_LtoR_KEY(name, out, ...) case COMBO_ID_##name: combo_term = COMBOROLL_TERM; break;
#define Q_LtoR_ARR Q_LtoR_KEY
#define Q_LtoR_LIT Q_LtoR_KEY
#define Q_LtoR_STR Q_LtoR_KEY

#define Q_RtoL_KEY Q_LtoR_KEY
#define Q_RtoL_ARR Q_LtoR_KEY
#define Q_RtoL_LIT Q_LtoR_KEY
#define Q_RtoL_STR Q_LtoR_KEY

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    uint16_t combo_term = COMBO_TERM;
    switch (index) {
#       include "combo_defs.h"
    }

#undef  Q_CMBO_TRM
#define Q_CMBO_TRM(name, ms) case COMBO_ID_##name: combo_term = ms; break;

#undef  Q_LtoR_KEY
#undef  Q_LtoR_ARR
#undef  Q_LtoR_LIT
#undef  Q_LtoR_STR
#undef  Q_LtoR_TRM

#undef  Q_RtoL_KEY
#undef  Q_RtoL_ARR
#undef  Q_RtoL_LIT
#undef  Q_RtoL_STR
#undef  Q_RtoL_TRM

#define Q_LtoR_KEY(name, out, ...)
#define Q_LtoR_ARR Q_LtoR_KEY
#define Q_LtoR_LIT Q_LtoR_KEY
#define Q_LtoR_STR Q_LtoR_KEY
#define Q_LtoR_TRM Q_CMBO_TRM

#define Q_RtoL_KEY Q_LtoR_KEY
#define Q_RtoL_ARR Q_LtoR_KEY
#define Q_RtoL_LIT Q_LtoR_KEY
#define Q_RtoL_STR Q_LtoR_KEY
#define Q_RtoL_TRM Q_CMBO_TRM

    switch (index) {
#       include "combo_defs.h"
    }
    
    return combo_term;
}
