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
#if defined(OLED_ENABLE)
    oled_set_brightness(MAX( user_config.oled_brightness, 0x10 )); // set a minimum, to avoid blank display
#endif

    // Other functions init
#if defined(COMBOROLL_ENABLE)
    comboroll_post_init();
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
 |                    | Mute |  Tab |   "  |      | SYMS |  |      |      |   '  |  Tab |      |
 |                    |      |  Cmd | SNAP |      |      |  |      |      | EDIT | META |      |
 |                    `----------------------------------'  `----------------------------------'
                                    Alt=FUNC 
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
 |   `  |   \  |   (  |   *  |   )  |   !  |                              |   ;  | >  1 | /  2 | <  3 | =  0 |   ~  |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab |      |   2  |   0  |   1  |   @  |      |      |  |      |      |   +  | ]  4 | ?  5 | [  6 | -  , |      |
 |      | Shift| Ctrl |  Alt |  Cmd |      |      | (**) |  | Enter| Space|      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+---------------------------'
 |                    |      |      |      |      |      |  |      |      |   .  |      |      |
 |                    |      |      |      |      |      |  |      |      |      |CmdCtl|      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [SYMS] = LAYOUT(
        _______, KC_HASH, CU_QTQT, KC_COLN, KC_DQUO, KC_AMPR,                                           KC_CIRC, CU_7,       CU_8,    CU_9,    CU_DLUN, _______,
        KC_GRV,  KC_BSLS, KC_LPRN, KC_ASTR, KC_RPRN, KC_EXLM,                                           CU_SCSC, CU_1,       CU_2,    CU_3,    CU_0,    KC_TILD,
        _______, CU_SSFT, CU_SCTL, CU_SALT, CU_SGUI, KC_AT,   ___X___, ___X___, /* */ ___X___, ___X___, KC_PLUS, CU_4,       CU_5,    CU_6,    CU_MNCM, ___X___,
        /* */                      ___X___, ___X___, ___X___, ___X___, _______, /* */ _______, _______, CU_DTDT, SC_CMD_CTRL, ___X___
        ),

/* EDIT

 ,-----------------------------------------.                              ,-----------------------------------------.
 |Expose|FulScr| Home |  Up  |  End | WinR |                              | WinR | Paste| Copy |  Cut |  All | BkSp |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 | ScrL | PgUp | Left | Down | Right| AppR |                              | AppR |      |      |      |      | ScrR |
 |      |      |      |      |      |      |                              |      | Fast |  x5  | More |Delete|      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |  Tab | PgDn | Undo |  Del | Redo | TabR |      |      |  |      |      | TabR |      |      |      |      |AppWin|
 |      |      |      |      |      |      | BkSp | Enter|  |      |      |      |  Cmd |  Alt | Ctrl | Shift|      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |      |      | Space|      |      |  |      |      |      |      |      |
 |                    |      |CmdCtl|      |      |      |  |      |      | (**) |      |      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [EDIT] = LAYOUT_stack(
        SC_EXPOSE_ALL,   SC_FULLSCREEN, CE_HOME,         CE_UP,             CE_END,          CU_NEXT_WINDOW,
        SC_PREV_SCREEN,  CE_PAGE_UP,    CE_LEFT,         CE_DOWN,           CE_RIGHT,        CU_APPSWITCH_RIGHT,
        KC_TAB,          CE_PAGE_DOWN,  SC_UNDO_ACTION,  KC_DEL,            SC_REDO_ACTION,  CU_TAB_RIGHT,        ___X___, ___X___,
                                                         SC_APP_ZOOM_RESET, SC_CMD_CTRL,     KC_SPC,              KC_BSPC,  KC_ENT,

                          CU_NEXT_WINDOW,     SC_PASTE_CLIPBOARD, SC_COPY_SELECTION, SC_CUT_SELECTION,  SC_SELECT_ALL, _______,
                          CU_APPSWITCH_RIGHT, CE_FAST,            CE_X5,             CE_MORE,           CE_DELETE,     SC_NEXT_SCREEN,
        ___X___, ___X___, CU_TAB_RIGHT,       KC_RGUI,            KC_RALT,           KC_RCTL,           KC_RSFT,       SC_EXPOSE_WINDOWS,
        ___X___, ___X___, _______,            ___X___,            ___X___
    ),

/* SNAP

 ,-----------------------------------------.                              ,-----------------------------------------.
 |  Esc |  All |  Cut | Copy | Paste| WinR |                              | WinL |SnapTL| SnapT|SnapTR|FulScr|Expose|
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 | ScrL |      | SSScr| SSRgn| SSApp| AppR |                              | AppL | SnapL| SnapV| SnapR| Back | ScrR |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |      |      |      | TabR |      |      |  |      |      | TabL |SnapBL| SnapB|SnapBR|  Fwd |DskTop|
 |      | Shift| Ctrl |  Alt |  Cmd |      |      |      |  | Btn3 | Btn1 |      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
                      |      |      |      |      |      |  |      |      | Btn2 |      |      |
                      |      |      | (**) |      |      |  |      |      |      |      |      |
                      `----------------------------------'  `----------------------------------'
*/
    [SNAP] = LAYOUT_stack(
        _______,        SC_SELECT_ALL,    SC_CUT_SELECTION,     SC_COPY_SELECTION,    SC_PASTE_CLIPBOARD, CU_NEXT_WINDOW,
        SC_PREV_SCREEN, ___X___,          SC_SCREENSHOT_SCREEN, SC_SCREENSHOT_REGION, SC_SCREENSHOT_APP,  CU_APPSWITCH_RIGHT,
        ___X___,        KC_LSFT,          KC_LCTL,              KC_LALT,              KC_LGUI,            CU_TAB_RIGHT,        ___X___, ___X___,
                                                                ___X___,              ___X___,            _______,             ___X___, ___X___,

                          CU_PREV_WINDOW,    SC_SNAP_TOPLEFT,    SC_SNAP_TOP,      SC_SNAP_TOPRIGHT,    SC_FULLSCREEN,   SC_EXPOSE_ALL,
                          CU_APPSWITCH_LEFT, SC_SNAP_LEFT,       SC_SNAP_VERTICAL, SC_SNAP_RIGHT,       SC_BROWSER_BACK, SC_NEXT_SCREEN,
        ___X___, ___X___, CU_TAB_LEFT,       SC_SNAP_BOTTOMLEFT, SC_SNAP_BOTTOM,   SC_SNAP_BOTTOMRIGHT, SC_BROWSER_FWD,  SC_REVEAL_DESKTOP,
        CM_BTN3, CM_BTN1, CM_BTN2,           ___X___,            ___X___
    ),

/* FUNC

 ,-----------------------------------------.                              ,-----------------------------------------.
 |      |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |      |
 |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 |      |      | !MAC | !WIN |!LINUX|      |                              |      |  F1  |  F2  |  F3  |  F11 |      |
 |      |      |      |      |      |      |                              |      |      |      |      |      |      |
 |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |  |      |      |      |  F4  |  F5  |  F6  |  F12 |      |
 |      | Shift| Ctrl |  Alt |  Cmd |      |      |      |  |      |      |      |      |      |      |      |      |
 `--------------------+------+------+------|      |      |  |      |      |------+------+------+--------------------'
 |                    |      |      |      |      |      |  |      |      |      |      |      |
 |                    |      | (**) | (**) |      |      |  |      |      |      |CmdCtl|      |
 |                    `----------------------------------'  `----------------------------------'
*/
    [FUNC] = LAYOUT_stack(
        ___X___, ___X___, ___X___,         ___X___,           ___X___,         ___X___,
        ___X___, ___X___, CU_SELECT_MACOS, CU_SELECT_WINDOWS, CU_SELECT_LINUX, ___X___,
        _______, KC_LSFT, KC_LCTL,         KC_LALT,           KC_LGUI,         ___X___, ___X___, ___X___,
                                           ___X___,           _______,         _______, ___X___, ___X___,

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
    record->event.pressed = true; // force it on
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        process_record_user_emit(keycode, record);
    } else {
        if (keycode == KC_CAPS) { // needs special treatment
            tap_code16(KC_CAPS);
        } else {
#ifdef CUSTOM_CAPSWORD
            // Check for capsword cancel 
            process_caps_cancel(keycode, record);
#endif
            register_code16(keycode);
        }
    }
}

// Unregister a single key. Handles custom keycodes.
void unregister_custom_key(uint16_t keycode, keyrecord_t *record) {
    record->event.pressed = false; // force it off
    if (keycode > SAFE_RANGE) { // handle custom keycodes, a bit iffy but seems to work...
        process_record_user_emit(keycode, record);
    } else {
        unregister_code16(keycode);
    }
}

// Tap a single key. Handles custom keycodes.
void tap_custom_key(uint16_t keycode, keyrecord_t *record) {
    register_custom_key(keycode, record);
    unregister_custom_key(keycode, record);
}


/**
 * Process keys with a custom shift value. Shift codes are defined in shift_defs.h.
 */
// clang-format off
#undef  DEFINE_SHIFT
#define DEFINE_SHIFT(name, normal, shifted) [name - SHIFT_ID_START] = {normal, shifted},

const uint16_t PROGMEM shift_keycodes[][2] = {
    DEFINE_SHIFT(SHIFT_ID_START, KC_NO, KC_NO)
#   include "shift_defs.h"
    DEFINE_SHIFT(SHIFT_ID_END, KC_NO, KC_NO)
};
#define READ_SHIFT_KEY(k, i) (pgm_read_word(&shift_keycodes[k - SHIFT_ID_START][i]))
// clang-format on


// Process a single custom shift key based on passed values
void process_shift_key(uint16_t key, uint16_t shiftedkey, keyrecord_t *record) {
    uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
    uint8_t ossmods = get_oneshot_mods();
#else
    uint8_t ossmods = mods;
#endif

    del_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
    del_oneshot_mods(MOD_MASK_SHIFT);
#endif

    if (record->event.pressed) {
        register_custom_key((mods | ossmods) & MOD_MASK_SHIFT ? shiftedkey : key, record);
    } else {
        unregister_custom_key(key, record);
        unregister_custom_key(shiftedkey, record);
    }
    set_mods(mods);
#ifndef NO_ACTION_ONESHOT
    set_oneshot_mods(ossmods);
    if (ossmods & MOD_MASK_SHIFT) {
        del_oneshot_mods(MOD_MASK_SHIFT);
    }
#endif
}


// Process a single custom shift key based on the keycode
void process_custom_shift(uint16_t key, keyrecord_t *record) {
    if (key > SHIFT_ID_START && key < SHIFT_ID_END) {
        process_shift_key(READ_SHIFT_KEY(key, 0), READ_SHIFT_KEY(key, 1), record);
    }
}


/**
 * User-level processing of custom keycodes, for those that might output characters.
 * This is split out from process_record_user so that it can be called from other
 * places (via tap_custom_key()).
 */
bool process_record_user_emit(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_CAPSWORD
    // Check for capsword cancel 
    process_caps_cancel(keycode, record);
#endif

    // Process custom shift keys
    process_custom_shift(keycode, record);

    // Process OS shortcut keycodes
#if defined(OS_SHORTCUTS) && !defined(OS_SHORTCUTS_STATIC)
    process_record_shortcut(keycode, record);
#endif

    // Process custom editing keycodes
#ifdef CUSTOM_EDIT
    if (!custom_edit_process_record(keycode, record)) {
        return false;
    }
#endif

    // Process custom mouse keycodes
#ifdef CUSTOM_MOUSE
    if (!custom_mouse_process_record(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {

#ifdef LAYER_TAP_TOGGLE
            // layer switching using layer-tap-toggle custom code
        case CL_SYMS:
            return layer_tap_toggle(CU_QTQT, SYMS, record);
            break;

        case CL_SNAP:
            return layer_tap_toggle2(KC_DQUO, SNAP, FUNC, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(CU_QTQT, EDIT, record);
            break;

        case CL_META:
            return layer_tap_toggle(KC_TAB, META, record);
            break;
#else
            // layer switching using QMK layer-tap: handle cases where tap code is 16-bit or has custom shift
        case CL_SNAP:
            if (record->tap.count) {
                process_shift_key(KC_DQUO, KC_DQUO, record);
                return false; // Return false to ignore further processing
            }
            break;

        case CL_SYMS:
        case CL_EDIT:
            if (record->tap.count) {
                process_shift_key(KC_QUOT, KC_QUOT, record);
                return false;
            }
            break;
#endif

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
        case CU_WRIT:
            if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
                rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
#endif
#ifdef OLED_ENABLE
                user_config.oled_brightness = oled_get_brightness();
                eeconfig_update_user(user_config.raw);
#endif
            }
            break;

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

#ifdef EAGER_MODTAP
    // Check for and process eager mod-taps
    if (!process_record_emt(keycode, record)) {
        return false;
    }
#endif
	
#ifdef COMBOROLL_ENABLE
    // Check for and process comboroll keys
    if (!process_record_comboroll(keycode, record)) {
        return false;
    }
#endif
    
#ifdef CUSTOM_CAPSWORD
    // Toggle caps word and caps lock
    if (!process_record_capsword(keycode, record)) {
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
    ltt_tick();
#endif

    // Comboroll timing repeat
#ifdef COMBOROLL_ENABLE
    comboroll_tick();
#endif

    // Editing repeat
#ifdef CUSTOM_EDIT
    custom_edit_tick();
#endif

    // Eager modtap timing
#ifdef EAGER_MODTAP
    emt_tick();
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
