
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



/** Combo definitions. NB don't edit here, edit in combos.def.
 *
 * Code borrowed/adapted from :
 *
 * https://github.com/sevanteri/qmk_firmware/blob/9cca95785e6fd5001367d02fceddae628f6d48c9/users/sevanteri/combos.h
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/gboards/g/keymap_combo.h
 */


#include "config.h"
#include "keymap.h"

#define ARRAY_PROTECT(...) __VA_ARGS__ 

#define CMB_NUL(...)

#define COMBO_KEY_ENUM(name, keycode, ...)  COMBO_ID_##name,
#define COMBO_KEY_DATA(name, keycode, ...)  const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};
#define COMBO_KEY_MAP(name, keycode, ...)  [COMBO_ID_##name] = COMBO(COMBO_SEQ_##name, keycode),
#define COMBO_KEY_EXEC(name, keycode, ...)


#define COMBO_ARR_ENUM(name, protected_array, ...)  \
    COMBO_ID_##name,

#define COMBO_ARR_DATA(name, protected_array, ...)  \
    const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END}; \
    uint16_t combo_array_##name[] = { protected_array, KC_NO };

#define COMBO_ARR_MAP(name, protected_array, ...)  \
    [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),

#define COMBO_ARR_EXEC(name, protected_array, ...) \
    case COMBO_ID_##name: \
        process_combo_array(combo_array_##name); \
    break;


#define COMBO_STR_ENUM(name, ...)  \
    COMBO_ID_##name,

#define COMBO_STR_DATA(name, ...)  \
    const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};

#define COMBO_STR_MAP(name, ...)  \
    [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),

#define COMBO_STR_EXEC(name, ...) \
    case COMBO_ID_##name: \
        process_combo_string(#name); \
    break;


#define COMBO_LIT_ENUM(name, string_literal, ...)    \
    COMBO_ID_##name,

#define COMBO_LIT_DATA(name, string_literal, ...)                        \
    const uint16_t PROGMEM COMBO_SEQ_##name[] = {__VA_ARGS__, COMBO_END};

#define COMBO_LIT_MAP(name, string_literal, ...)         \
    [COMBO_ID_##name] = COMBO_ACTION(COMBO_SEQ_##name),

#define COMBO_LIT_EXEC(name, string_literal, ...)       \
    case COMBO_ID_##name: \
        process_combo_string(string_literal); \
    break;


void process_combo_array(uint16_t *keyptr);
void process_combo_string(char* str);

    
// Enum for combo codes
#undef CMB_KEY
#undef CMB_ARR
#undef CMB_STR
#undef CMB_LIT
#define CMB_KEY COMBO_KEY_ENUM
#define CMB_ARR COMBO_ARR_ENUM
#define CMB_STR COMBO_STR_ENUM
#define CMB_LIT COMBO_LIT_ENUM
enum combo_events {
#include "combos.def"
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// Define combo key sequences in memory
#undef CMB_KEY
#undef CMB_ARR
#undef CMB_STR
#undef CMB_LIT
#define CMB_KEY COMBO_KEY_DATA
#define CMB_ARR COMBO_ARR_DATA
#define CMB_STR COMBO_STR_DATA
#define CMB_LIT COMBO_LIT_DATA
#include "combos.def"

// Define mapping from key sequences to combo codes or actions
#undef CMB_KEY
#undef CMB_ARR
#undef CMB_STR
#undef CMB_LIT
#define CMB_KEY COMBO_KEY_MAP
#define CMB_ARR COMBO_ARR_MAP
#define CMB_STR COMBO_STR_MAP
#define CMB_LIT COMBO_LIT_MAP
combo_t key_combos[] = {
#include "combos.def"
};


// Emit an array of keycodes
void process_combo_array(uint16_t *keyptr) {
    while (*keyptr != KC_NO) {
        tap_code16(*keyptr++);
    }
}

// Emit a string, clear shift after first character
void process_combo_string(char* str) {
    send_char(*str++);
    clear_mods();
    while (*str) {
        send_char(*str++);
    }
}


// Execute code for action combos
#undef CMB_KEY
#undef CMB_ARR
#undef CMB_STR
#undef CMB_LIT
#define CMB_KEY COMBO_KEY_EXEC
#define CMB_ARR COMBO_ARR_EXEC
#define CMB_STR COMBO_STR_EXEC
#define CMB_LIT COMBO_LIT_EXEC

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint8_t mods = get_mods();

    if (pressed) {
        switch(combo_index) {
#include "combos.def"
        }
    }
    set_mods(mods);
}
