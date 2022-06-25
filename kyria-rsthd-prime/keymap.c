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
 * User space in EEPROM. Variable and function to read at initialization.
 */
user_config_t user_config;

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    // Set OS
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    os_set_raw(user_config.os_selection);
#endif
}

// Make it easier to read null key (instead of XXXXXXX)
#define ___X___ KC_NO

/**
 * Keymap
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
/* ALPHA v32
 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   V  |   C  |   W  |   F  |   K  |                              |   J  |   M  |   U  | .  / | -  _ | BkSp |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   B  |                              | ;  : |   N  |   I  |   O  |   A  |   Q  |
 | Ctrl |      |      |      |      |      |                    Search    |      |      |      |      |      | Ctrl |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab |      |   P  |   G  |   D  |   Z  |      |      |  |      |      | !  ? |   L  |   Y  | ,  | |      | Caps |
 |  Alt | Shift|      |      |      |      |   E  |   '  |  | Enter| Space|      |      |      |      | Shift|  Alt |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    | Mute |      |   "  |      | SYMS |  |      |      | BkSp |   K  |      |
 |                    |      |  Cmd | SNAP |      |      |  |      |      | EDIT | META |      |
 |                    `----------------------------------'  `----------------------------------'
*/
     [ALPHA] = LAYOUT(
        KC_ESC,  KC_V,    KC_C,   KC_W,    KC_F,    KC_K,                                              KC_J,    KC_M,    KC_U,   CU_DOT,  KC_MINS, KC_BSPC,
        CU_LCTL, KC_R,    KC_S,   KC_T,    KC_H,    KC_B,                                              KC_SCLN, KC_N,    KC_I,   KC_O,    KC_A,    CU_RCTL,
        CU_LALT, CU_LSFT, KC_P,   KC_G,    KC_D,    KC_Z,    ___X___, ___X___, /* */ ___X___, ___X___, CU_EXQU, KC_L,    KC_Y,   CU_COMM, CU_RSFT, CU_RALT,
        /* */                     KC_MUTE, CU_LCMD, CL_SNAP, KC_E,    CL_SYMS, /* */ KC_ENT,  KC_SPC,  CL_EDIT, CL_META, ___X___
        ),
     
/* SYMS

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |   #  |   '  |   :  |   "  |   &  |                              |   ^  | }  7 | %  8 | {  9 | $  _ | BkSp |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |   `  |   \  |   (  |   *  |   )  |   .  |                              |   !  | >  1 | /  2 | <  3 | =  0 |   ~  |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab |      |   2  |   0  |   1  |   @  |      |      |  |      |      |   +  | ]  4 | ?  5 | [  6 | -  , |  ../ |
 |      | Shift| Ctrl |  Alt |  Cmd |      |      | (**) |  | Enter| Space|      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+---------------------------'
 |                    |      |      |      |      |      |  |      |      | BkSp |      |      |
 |                    |      |      |      |      |      |  |      |      |      |CmdCtl|      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [SYMS] = LAYOUT(
        _______, KC_HASH, CU_QTQT, KC_COLN, KC_DQUO, KC_AMPR,                                           KC_CIRC, CU_7,       CU_8,    CU_9,    CU_DLUN, _______,
        KC_GRV,  KC_BSLS, KC_LPRN, KC_ASTR, KC_RPRN, CU_DTDT,                                           KC_EXLM, CU_1,       CU_2,    CU_3,    CU_0,    KC_TILD,
        _______, CU_SSFT, CU_SCTL, CU_SALT, CU_SGUI, KC_AT,   ___X___, ___X___, /* */ ___X___, ___X___, KC_PLUS, CU_4,       CU_5,    CU_6,    CU_MNCM, CU_DIRU,
        /* */                      ___X___, ___X___, ___X___, ___X___, _______, /* */ _______, _______, KC_BSPC, SC_CMD_CTRL, ___X___
        ),

/* EDIT

 ,-----------------------------------------.                              ,-----------------------------------------.
 |Expose|FulScr| Home |  Up  |  End | WinR |                              | WinR | Paste| Copy |  All |  Cut | BkSp |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 | ScrL | PgUp | Left | Down | Right| AppR |                              | AppR |      |      |      |      | ScrR |
 |      |      |      |      |      |      |                              |      | Fast |  x5  | More |Delete|      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab | PgDn | Undo |  Del | Redo | TabR |      |      |  |      |      | TabR |      |      |      |      |AppWin|
 |      |      |      |      |      |      | Space| Enter|  |      |      |      |  Cmd |  Alt | Ctrl | Shift|      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |      |      | BkSp |      |      |  |      |      |      |      |      |
 |                    |      |CmdCtl|      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
     [EDIT] = LAYOUT_stack(
	SC_EXPOSE_ALL,     SC_FULLSCREEN, CE_HOME,         CE_UP,     CE_END,          CU_NEXT_WINDOW,
	SC_PREV_SCREEN,    CE_PAGE_UP,    CE_LEFT,         CE_DOWN,   CE_RIGHT,        CU_APPSWITCH_RIGHT,
	KC_TAB,            CE_PAGE_DOWN,  CU_UNDO_OR_BACK, KC_DEL,    CU_REDO_OR_FWD,  CU_TAB_RIGHT,        ___X___, ___X___,
	                                                   ___X___,   SC_CMD_CTRL,     KC_BSPC,             KC_SPC,  KC_ENT,

	                  CU_NEXT_WINDOW,     SC_PASTE_CLIPBOARD, SC_COPY_SELECTION, SC_SELECT_ALL,  SC_CUT_SELECTION, _______,
	                  CU_APPSWITCH_RIGHT, CE_FAST,            CE_X5,             CE_MORE,        CE_DELETE,        SC_NEXT_SCREEN,
	___X___, ___X___, CU_TAB_RIGHT,       KC_RGUI,            KC_RALT,           KC_RCTL,        KC_RSFT,          SC_EXPOSE_WINDOWS,
	___X___, ___X___, _______,        ___X___,            ___X___
	),
     
/* SNAP

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |  All |  Cut | Copy | Paste| WinR |                              | WinL |SnapTL| SnapT|SnapTR|FulScr|Expose|
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 | ScrL |      | SSScr| SSRgn| SSApp| AppR |                              | AppL | SnapL| SnapV| SnapR| Back | ScrR |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |      |      |      | TabR |      |      |  |      |      | TabL |SnapBL| SnapB|SnapBR|  Fwd |DskTop|
 | FUNC | Shift| Ctrl |  Alt |  Cmd |      |      |      |  |      |      |      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                      |      |      |      |      |      |  |      |      |      |      |      |
                      |      |      | (**) |      |      |  |      |      |      |      |      |
                      `----------------------------------'  `----------------------------------'
*/
    [SNAP] = LAYOUT_stack(
	_______,        SC_CUT_SELECTION, SC_SELECT_ALL,        SC_COPY_SELECTION,    SC_PASTE_CLIPBOARD, CU_NEXT_WINDOW,
	SC_PREV_SCREEN, ___X___,          SC_SCREENSHOT_SCREEN, SC_SCREENSHOT_REGION, SC_SCREENSHOT_APP,  CU_APPSWITCH_RIGHT,
	CL_FUNC,        KC_LSFT,          KC_LCTL,              KC_LALT,              KC_LGUI,            CU_TAB_RIGHT,        ___X___, ___X___,
                                                                ___X___,              ___X___,            _______,             ___X___, ___X___,

	                      CU_PREV_WINDOW,    SC_SNAP_TOPLEFT,    SC_SNAP_TOP,      SC_SNAP_TOPRIGHT,    SC_FULLSCREEN,   SC_EXPOSE_ALL,
	                      CU_APPSWITCH_LEFT, SC_SNAP_LEFT,       SC_SNAP_VERTICAL, SC_SNAP_RIGHT,       SC_BROWSER_BACK, SC_NEXT_SCREEN,
        ___X___,   ___X___,   CU_TAB_LEFT,       SC_SNAP_BOTTOMLEFT, SC_SNAP_BOTTOM,   SC_SNAP_BOTTOMRIGHT, SC_BROWSER_FWD,  SC_REVEAL_DESKTOP,
        ___X___,   ___X___,   ___X___,           ___X___,            ___X___
    ),

/* FUNC

 ,-----------------------------------------.                              ,-----------------------------------------.
 |      |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |      | !MAC | !WIN |!LINUX|      |                              |      |  F1  |  F2  |  F3  |  F11 |      |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |  |      |      |      |  F4  |  F5  |  F6  |  F12 |      |
 | (**) | Shift| Ctrl |  Alt |  Cmd |      |      |      |  |      |      |      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |      |      |      |      |      |  |      |      |      |      |      |
 |                    |      |      | (**) |      |      |  |      |      |      |CmdCtl|      |
 |                    `----------------------------------'  `----------------------------------'
*/
     [FUNC] = LAYOUT_stack(
        ___X___, ___X___, ___X___,         ___X___,           ___X___,         ___X___,
	___X___, ___X___, CU_SELECT_MACOS, CU_SELECT_WINDOWS, CU_SELECT_LINUX, ___X___,
	_______, KC_LSFT, KC_LCTL,         KC_LALT,           KC_LGUI,         ___X___, ___X___, ___X___,
	                                   ___X___,           ___X___,         _______, ___X___, ___X___,

                          ___X___, KC_F7,       KC_F8,   KC_F9,   KC_F10,  ___X___,
	                  ___X___, KC_F1,       KC_F2,   KC_F3,   KC_F11,  ___X___,
	___X___, ___X___, ___X___, KC_F4,       KC_F5,   KC_F6,   KC_F12,  ___X___,
	___X___, ___X___, ___X___, SC_CMD_CTRL, ___X___
	),

/* META

 ,-----------------------------------------.                              ,-----------------------------------------.
 |      |      | Close|      | Find |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 | eXit |      | Save |newTab|      |  Bin |                              |      |  New |      | Open |saveAs| Quit |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      | Print|      |      |      |      |      |  |      |      |      |      |      |      |      |      |
 |      |      |      |      |      |      | Next |      |  | !WIPE|      |      |  Cmd |  Alt | Ctrl | Shift|      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |!WRITE|      | Prev |      |      |  |      |      |      | (**) |      |
 |                    |      |      |      |      |      |  |      |      |      |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
     [META] = LAYOUT_stack(
        ___X___, ___X___, SC_CLOSE_TAB, ___X___,    SC_FIND,   ___X___,
        SC_QUIT, ___X___, SC_SAVE,      SC_NEW_TAB, ___X___,   SC_BIN, 
        ___X___, ___X___, SC_PRINT,     ___X___,    ___X___,   ___X___,        ___X___,        ___X___,
                                        CU_WRIT,    ___X___,   SC_PREV_SEARCH, SC_NEXT_SEARCH, ___X___,

                           ___X___,  ___X___,  ___X___,  ___X___,  ___X___,    ___X___,
                           ___X___,  SC_NEW,   ___X___,  SC_OPEN,  SC_SAVE_AS, SC_QUIT,
        ___X___, ___X___,  ___X___, KC_RGUI,   KC_RALT,  KC_RCTL,  KC_RSFT,    ___X___,
        CU_WIPE, ___X___,  ___X___,  _______,  ___X___
        ),
};
// clang-format on

// Register a single key. Handles custom keycodes.
void register_custom_key(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    del_mods(MOD_MASK_SHIFT);
     if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        record->event.pressed = true;
        process_record_user_emit(keycode, record);
    } else {
        if (keycode == KC_CAPS) { // needs special treatment!??
            tap_code16(keycode);
        } else {
            register_code16(keycode);
        }
    }
    set_mods(mods);
}

// Unregister a single key. Handles custom keycodes.
void unregister_custom_key(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    del_mods(MOD_MASK_SHIFT);
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        record->event.pressed = false;
        process_record_user_emit(keycode, record);
    } else {
        unregister_code16(keycode);
    }
    set_mods(mods);
}

// Tap a single key. Handles custom keycodes.
void tap_custom_key(uint16_t keycode, keyrecord_t *record) {
    register_custom_key(keycode, record);
    unregister_custom_key(keycode, record);
}

/**
 * Process keys with a custom shift value. Shift codes are defined in shift_defs.h.
 * FIXME make it able to handle custom keycodes.
 */
// clang-format off
#undef DEFINE_SHIFT
#define DEFINE_SHIFT(name, normal, shifted) [name - SHIFT_ID_START] = {normal, shifted},

const uint16_t PROGMEM shift_keycodes[][2] = {
    DEFINE_SHIFT(SHIFT_ID_START, KC_NO, KC_NO)
#   include "shift_defs.h"
    DEFINE_SHIFT(SHIFT_ID_END, KC_NO, KC_NO)
};
#define READ_SHIFT_KEY(k, i) (pgm_read_word(&shift_keycodes[k - SHIFT_ID_START][i]))
// clang-format on

// Handle a single key based on passed values
void process_shift_key(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
    uint8_t mods = get_mods();
    if (record->event.pressed) {
        register_custom_key(mods & MOD_MASK_SHIFT ? shiftedkey : key, record);
    } else {
        unregister_custom_key(key, record);
        unregister_custom_key(shiftedkey, record);
    }
}

// Call this from the default case at the end of switch(keycode) in process_record_user
void process_custom_shift(uint16_t key, keyrecord_t *record) {
    if (key > SHIFT_ID_START && key < SHIFT_ID_END) {
        process_shift_key(READ_SHIFT_KEY(key, 0), READ_SHIFT_KEY(key, 1), record);
    }
}

/**
 * Cancel caps-lock automatically ("caps word").
 */
void process_caps_cancel(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods          = get_mods();

    if (host_keyboard_led_state().caps_lock && record->event.pressed) {
        if (mods & MOD_MASK_SHIFT) {
            switch (keycode) { // Keys that cancel caps lock only on shifted version
                case KC_1 ... KC_0:
                    tap_code(KC_CAPS);
            }
        }
        if (!(mods & MOD_MASK_SHIFT)) {
            switch (keycode) { // Keys that cancel caps lock only on UNshifted version
                case CU_0 ... CU_9:
                    tap_code(KC_CAPS);
            }
        }
        switch (keycode) { // Keycodes that cancel caps lock regardless of shift
            case KC_ENTER:
            case KC_ESCAPE:
            case KC_TAB:
            case KC_SPACE:

            case KC_EXCLAIM ... KC_RIGHT_PAREN:
            case KC_EQUAL ... KC_SLASH:
            case KC_PLUS ... KC_QUESTION:

            case CU_COMMA_PIPE:
            case CU_DOT_SLASH:
            case CU_EXCLAIM_QUESTION:
                // add any other custom keycodes as needed here
                tap_code(KC_CAPS);
        }
    }
}

/**
 * Handle layer switching
 */
#ifdef LAYER_TAP_TOGGLE
bool process_layer_switch(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CL_SYMS:
            return layer_tap_toggle(CU_QTQT, SYMS, record);
            break;

        case CL_SNAP:
            return layer_tap_toggle(KC_DQUO, SNAP, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(KC_BSPC, EDIT, record);
            break;

        case CL_META:
            return layer_tap_toggle(KC_K, META, record);
            break;

        case CL_FUNC:
            return layer_tap_toggle(KC_NO, FUNC, record);
            break;
    }
    return true;
}
#endif

/**
 * User-level processing of custom keycodes, for those that might output characters.
 * This is split out from process_record_user so that it can be called from other
 * places specifically custom shift and comboroll processing.
 */
bool process_record_user_emit(uint16_t keycode, keyrecord_t *record) {

    // Turn off caps lock at the end of a word
    process_caps_cancel(keycode, record);

    /* Layer switching
     */
#ifdef LAYER_TAP_TOGGLE
    if (!process_layer_switch(keycode, record)) {
        return false;
    }
#endif
    
    // Process custom shift keys
    process_custom_shift(keycode, record);

    // Process OS shortcut keycodes
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    process_record_shortcut(keycode, record);
#endif

    switch (keycode) {
            // Directory up
        case CU_DIRU: // directory up
            if (record->event.pressed) {
                tap_code(KC_DOT);
                tap_code(KC_DOT);
                tap_code(KC_SLASH);
            }
            break;

            /* Switch between applications (like Alt-Tab on Windows or Cmd-Tab on macOS) This must be triggered from
	     * a layer so the release event is called from layer_state_set_user() when the layer is released.
             */
        case CU_APPSWITCH_RIGHT:
        case CU_APPSWITCH_LEFT:
            app_switcher_record(keycode, record);
            break;

            /* Wipe the EEPROM. Handy if you get stuck when you have multiple
             * default layers.....  After doing this, power-cycle the
             * keyboard. There will be no visible indication...
             */
        case CU_WIPE:
            if (record->event.pressed) {
                eeconfig_init();
            }
            break;

            /* Save RGB state to EEPROM.
             */
#ifdef RGBLIGHT_ENABLE
        case CU_WRIT:
            if (record->event.pressed) {
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
            }
            break;
#endif

            // Process custom editing keycodes
#ifdef CUSTOM_EDIT
            CUSTOM_EDIT_PROCESS_RECORD(keycode, record);
#endif

            // Process custom mouse keycodes
#ifdef CUSTOM_MOUSE
            CUSTOM_MOUSE_PROCESS_RECORD(keycode, record);
#endif

            /* Select the OS used for shortcuts and write to EEPROM.
             */
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
        case CU_SELECT_MACOS:
        case CU_SELECT_WINDOWS:
        case CU_SELECT_LINUX:
            if (record->event.pressed) {
                os_set_from_keycode(keycode);
                user_config.os_selection = os_get_raw();
                eeconfig_update_user(user_config.raw);
            }
            break;
#endif

    }
    return true;
}

/**
 * User-level processing of custom keycodes.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef LAYER_TAP_TOGGLE
    // Check for interrupt to layer-tap-toggle
    ltt_interrupt(keycode, record);
#endif

#ifdef COMBOROLL_ENABLE
    // Check for and process comboroll keys
    if (!process_record_comboroll(keycode, record)) {
        return false;
    }
#endif

    // Process custom keycodes that output characters
    return process_record_user_emit(keycode, record);
}

/**
 * User-level matrix scan hook.
 */
void matrix_scan_user(void) {
    // App-switcher timeout
    app_switcher_tick();

    // Update ltt_timer
#ifdef LAYER_TAP_TOGGLE
    ltt_update_timer();
#endif

    // Editing repeat
#ifdef CUSTOM_EDIT
    custom_edit_tick();
#endif

    // Mouse repeat
#ifdef CUSTOM_MOUSE
    custom_mouse_tick();
#endif

    // Comboroll timing repeat
#ifdef COMBOROLL_ENABLE
    comboroll_tick();
#endif
}

/**
 * User-level layer change hook.
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    /* Release the appswitcher on every layer change.
     */
    app_switcher_release();
    return state;
}
