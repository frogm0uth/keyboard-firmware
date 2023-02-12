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
    oled_set_brightness(MAX(user_config.oled_brightness, 0x10)); // set a minimum, to avoid blank display
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

/* ALPHA v35
 
 ,-----------------------------------------.                        ,-----------------------------------------.
 |  Esc |   V  |   C  |   W  |   F  |   K  |                        |   J  |   M  |   U  | .  ! |   '  | BkSp |
 |------+------+------+------+---Z--+------|                        |------+------+------+------+------+------|
 |   X  |   R  |   S  |   T  |   H  |   B  |                        | ;  : |   N  |   I  |   O  |   A  |   Q  |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |   P  |   G  |   D  |                                      |   L  |   Y  | ,  ? |      |      |
 | META | Shift|      |      |      |                                      |      |      |      | Shift| META |
 `----------------------------------'                                      `----------------------------------'
 .                                                            Search
 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |ScrLck|      |   "  |   E  | -  _ |  | Enter| Space|  Tab |
 .                 |      |      | SYMS |      |      |  |      |      | EDIT |
 .                 `------'      `--------------------'  `--------------------'
*/
    [ALPHA] = KEY_LAYOUT_stack(
        /* Left hand */
        KC_ESC,   KC_V,     KC_C,  KC_W,  KC_F,  KC_K,
        KC_X,     KC_R,     KC_S,  KC_T,  KC_H,  KC_B,
        CL_META,  KC_LSFT,  KC_P,  KC_G,  KC_D,

        /* Right hand */
                  KC_J,     KC_M,  KC_U,  CU_DOT,  CU_QTQT, KC_BSPC,
                  KC_SCLN,  KC_N,  KC_I,  KC_O,    KC_A,    KC_Q,
                            KC_L,  KC_Y,  CU_COMM, KC_RSFT, CL_META,

        /* Encoder & Thumbs */
        SC_SCREEN_LOCK, CL_SYMS, KC_E, KC_MINS, KC_ENT, KC_SPC, CL_EDIT
    ),


/* SYMS

 ,-----------------------------------------.                        ,----------- ?> --- <? -------------------.
 | LOCK |      |  Cut | Copy | Paste|      |                        |   ^  | ]  7 | #  8 | [  9 |   $  | LOCK |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |   \  |   |  |   (  |   *  |   )  |  Tab |                        | &  @ | >  1 | /  2 | <  3 | =  0 | ~  ` |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |FulScr|      |      |      |      |                                      | }  4 | %  5 | {  6 | -  + |DskTop|
 |      | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      |      |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |      |      |      |  | Enter| Space|   .  |
 .                 |      |      | (**) |      |      |  |      |      |      |
 .                 `------'      `--------------------'  `--------------------'
 */

    [SYMS] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_LOCK,        ___X___,  SC_CUT,   SC_COPY,  SC_PASTE,  ___X___,
        KC_BSLS,        KC_PIPE,  KC_LPRN,  KC_ASTR,  KC_RPRN,   KC_TAB,
        SC_FULLSCREEN,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI,

        /* Right hand */
                  KC_CIRC,    CU_7,  CU_8,  CU_9,  KC_DLR,        CU_LOCK,
                  CU_AMP_AT,  CU_1,  CU_2,  CU_3,  CU_0,          CU_TILDE_GRAVE,
                              CU_4,  CU_5,  CU_6,  CU_MINS_PLUS,  SC_REVEAL_DESKTOP,

        /* Encoder & Thumbs */
        ___X___, _______, ___X___, ___X___, KC_ENT, KC_SPC, CU_DOT_DOT
    ),


/* EDIT

 ,-----------------------------------------.                        ,-----------------------------------------.
 | LOCK | PgUp | Home |  Up  |  End | WinL |                        | WinR | Paste| Copy |  Cut |AppWin| LOCK |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | TabL | PgDn | Left | Down | Right| AppL |                        | AppR |      |      |      |      | TabR |
 |      |      |      |      |      |      |                        |      | Fast |  x4  | More |Delete|      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 | ScrL |      | Undo |  Tab | Redo |                                      |      |      |      |      | ScrR |
 |      | Shift|      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift|      |
 `----------------------------------'                                      `----------------------------------'
 .                                          Expose
 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |  Del | BkSp | Enter|  |      |      |      |
 .                 |      |      |      |      |      |  |      |      | (**) |
 .                 `------'      `--------------------'  `--------------------'
 */

    [EDIT] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_LOCK,         CE_PAGE_UP,   CE_HOME,  CE_UP,    CE_END,    CU_PREV_WINDOW,
        CU_TAB_LEFT,     CE_PAGE_DOWN, CE_LEFT,  CE_DOWN,  CE_RIGHT,  CU_APPSWITCH_LEFT,
        SC_PREV_SCREEN,  _______,      SC_UNDO,  KC_TAB,   SC_REDO,


        /* Right hand */
                     CU_NEXT_WINDOW,     SC_PASTE,  SC_COPY,  SC_CUT,   SC_EXPOSE_WINDOWS,  CU_LOCK,
                     CU_APPSWITCH_RIGHT, CE_FAST,   CE_X4,    CE_MORE,  CE_DELETE,          CU_TAB_RIGHT,
                                         KC_RGUI,   KC_RALT,  KC_RCTL,  KC_RSFT,            SC_NEXT_SCREEN,

        /* Encoder & Thumbs */
        SC_APP_ZOOM_RESET, KC_DEL, KC_BSPC, KC_ENT, ___X___, ___X___, _______
    ),


/* META

 ,-----------------------------------------.                        ,-----------------------------------------.
 | LOCK |saveAs| Close|      | Find |      |                        |      |PrvTrk| Play |NxtTrk| Mute | LOCK |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 | eXit |Reload| Save |newTab|      |  Bin |                        |      |  New |      | Open |  All | Quit |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      | Print| Prev | Next |                                      | Back |  Fwd |      |      |      |
 | (**) | Shift|      |      |      |                                      |      |      |      | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 | Mute |      |      | AppR | WinR |  | WinR | AppR |      |
 .                 |      |      | FUNC |      |      |  |      |      | SNAP |
 .                 `------'      `--------------------'  `--------------------'
 */

    [META] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_LOCK, SC_SAVE_AS,  SC_CLOSE_TAB, ___X___,        SC_FIND,        ___X___,
        SC_QUIT, SC_RELOAD,   SC_SAVE,      SC_NEW_TAB,     ___X___,        SC_BIN,
        _______, _______,     SC_PRINT,     SC_PREV_SEARCH, SC_NEXT_SEARCH,

        /* Right hand */
                 ___X___,  KC_MPRV,         KC_MPLY,        KC_MNXT,  KC_MUTE,       CU_LOCK,
                 ___X___,  SC_NEW,          ___X___,        SC_OPEN,  SC_SELECT_ALL, SC_QUIT,
                           SC_BROWSER_BACK, SC_BROWSER_FWD, ___X___,  _______,       _______,

        /* Encoder & Thumbs */
        KC_MUTE, CL_FUNC, CU_APPSWITCH_RIGHT, CU_NEXT_WINDOW, CU_NEXT_WINDOW, CU_APPSWITCH_RIGHT, CL_SNAP
    ),


/* FUNC

 ,-----------------------------------------.                        ,-----------------------------------------.
 | LOCK |      |      |      |      |      |                        |      |  F7  |  F8  |  F9  |  F10 | LOCK |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |      |      | !MAC | !WIN |!LINUX|      |                        |      |  F1  |  F2  |  F3  |  F11 |      |
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |      |      |      |                                      |  F4  |  F5  |  F6  |  F12 |      |
 | (**) | Shift| Ctrl |  Alt |  Cmd |                                      |      |      |      |      | (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |      |      |      |      |      |  | Btn3 | Btn1 | Btn2 |
 .                 |      |      | (**) |      |      |  |      |      |      |
 .                 `------'      `--------------------'  `--------------------'
 */

    [FUNC] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_LOCK, ___X___, ___X___,         ___X___,           ___X___,         ___X___,
        ___X___, ___X___, CU_SELECT_MACOS, CU_SELECT_WINDOWS, CU_SELECT_LINUX, ___X___,
        _______, KC_LSFT, KC_LCTL,         KC_LALT,           KC_LGUI,

         /* Right hand */
                 ___X___, KC_F7,   KC_F8,   KC_F9,   KC_F10,  CU_LOCK,
                 ___X___, KC_F1,   KC_F2,   KC_F3,   KC_F11,  ___X___,
                          KC_F4,   KC_F5,   KC_F6,   KC_F12,  _______,

        /* Encoder & Thumbs */
        ___X___, _______, ___X___, ___X___, CM_BTN3, CM_BTN1, CM_BTN2
    ),


/* SNAP

 ,-----------------------------------------.                        ,-----------------------------------------.
 | LOCK |      |SnapTL| SnapT|SnapTR|      |                        |      |      |      |      |      | LOCK |
 |------+------+------+------+------+------|                        |------+------+------+------+------+------|
 |      |      | SnapL| SnapV| SnapR|      |                        |      | SSRgn| SSWin| SSScr| SSApp|!WRITE|
 |------+------+------+------+------+------'                        `------+------+------+------+------+------|
 |      |      |SnapBL| SnapB|SnapBR|                                      |      |      |      |      |      |
 | (**) |      |      |      |      |                                      |  Cmd |  Alt | Ctrl | Shift| (**) |
 `----------------------------------'                                      `----------------------------------'

 .                 ,------.      ,--------------------.  ,--------------------.
 .                 |  Z0  |      | Btn3 | Btn1 | Btn2 |  |      | !WIPE|      |
 .                 |      |      |      |      |      |  |      |      | (**) |
 .                 `------'      `--------------------'  `--------------------'
 */

    [SNAP] = KEY_LAYOUT_stack(
        /* Left hand */
        CU_LOCK, ___X___,  SC_SNAP_TOPLEFT,    SC_SNAP_TOP,      SC_SNAP_TOPRIGHT,    ___X___,
        ___X___, ___X___,  SC_SNAP_LEFT,       SC_SNAP_VERTICAL, SC_SNAP_RIGHT,       ___X___,
        _______, ___X___,  SC_SNAP_BOTTOMLEFT, SC_SNAP_BOTTOM,   SC_SNAP_BOTTOMRIGHT,

         /* Right hand */
                 ___X___, ___X___,         ___X___,         ___X___,              ___X___,           CU_LOCK,
                 ___X___, CU_SCRSHOT_RGN,  CU_SCRSHOT_WIN,  SC_SCREENSHOT_SCREEN, SC_SCREENSHOT_APP, CU_WRITE,
                          KC_RGUI,         KC_RALT,         KC_RCTL,              KC_RSFT,           _______,

        /* Encoder & Thumbs */
        SC_APP_ZOOM_RESET, CM_BTN3, CM_BTN1, CM_BTN2, ___X___, CU_WIPE, _______
    ),

};
// clang-format on

// Register a single key. Handles custom keycodes.
void register_custom_key(uint16_t keycode, keyrecord_t *record) {
    record->event.pressed = true; // force it on
    if (keycode > SAFE_RANGE) {   // handle custom keycodes, a bit iffy but seems to work...
        process_record_user_emit(keycode, record);
    } else {
        if (keycode == KC_CAPS) { // needs special treatment
            tap_code(KC_CAPS);
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
    if (keycode > SAFE_RANGE) {    // handle custom keycodes, a bit iffy but seems to work...
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
    if (record->event.pressed) {
#ifndef NO_ACTION_ONESHOT
        uint8_t mods    = get_mods();
        uint8_t ossmods = get_oneshot_mods();

        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);

        register_custom_key((mods | ossmods) & MOD_MASK_SHIFT ? shiftedkey : key, record);

        set_mods(mods);
        set_oneshot_mods(ossmods);
        if (ossmods & MOD_MASK_SHIFT) {
            del_oneshot_mods(MOD_MASK_SHIFT);
        }
#else
        uint8_t mods = get_mods();
        del_mods(MOD_MASK_SHIFT);
        register_custom_key(mods & MOD_MASK_SHIFT ? shiftedkey : key, record);
        set_mods(mods);
#endif
    } else {
        unregister_custom_key(key, record);
        unregister_custom_key(shiftedkey, record);
    }
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

    switch (keycode) {
            // Toggle caps word
        case CU_CAPSWORD:
            if (record->event.pressed) {
                toggle_caps_word();
                return false;
            }
            break;

#ifdef LAYER_TAP_TOGGLE
            // layer switching using layer-tap-toggle custom code
        case CL_SYMS:
            return layer_tap_toggle(KC_DQUO, SYMS, record);
            break;

        case CL_EDIT:
            return layer_tap_toggle(KC_TAB, EDIT, record);
            break;

        case CL_META:
            return layer_tap_toggle(KC_NO, META, record);
            break;

        case CL_FUNC:
            return layer_tap_toggle(KC_NO, FUNC, record);
            break;

        case CL_SNAP:
            return layer_tap_toggle(KC_NO, SNAP, record);
            break;
#else
            // layer switching using QMK layer-tap: handle cases where tap code is 16-bit or has custom shift
        case CL_SYMS:
            if (record->tap.count) {
                process_shift_key(KC_DQUO, KC_DQUO, record);
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

            /* Take a screenshot of the window under the cursor. Currently works on macOS only.
             */
        case CU_SCRSHOT_WIN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREENSHOT_REGION));
                wait_ms(100);
                tap_code(KC_SPC);
#ifdef MOUSEKEY_ENABLE
                tap_code16(CM_BTN1);
#endif
            }
            break;

            /* Take screenshot of a region. This does the initial mouse press,
             * so press and hold the key, drag with the mouse keys then release the key.
             * Currently works on macOS only.
             */
        case CU_SCRSHOT_RGN:
            if (record->event.pressed) {
                tap_code16(SC(SC_SCREENSHOT_REGION));
#ifdef MOUSEKEY_ENABLE
                wait_ms(100);
                register_code16(CM_BTN1);
#endif
            } else {
#ifdef MOUSEKEY_ENABLE
                unregister_code16(CM_BTN1);
#endif
            }
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
        case CU_WRITE:
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

#ifdef COMBOROLL_ENABLE
    // Check for and process comboroll keys
    if (!process_record_comboroll(keycode, record)) {
        return false;
    }
#endif

#ifdef CUSTOM_CAPSWORD
    // Toggle caps lock
    if (!process_record_capslock(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        // Lock/unlock current layer 
        case CU_LOCK:
            ltt_lock(record);
            return false;
            break;
    }
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
