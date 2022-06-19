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
 ** App switcher i.e. Alt-Tab on Windows, Cmd-Tab on macOS.
 **/
#ifndef APP_SWITCHER_TERM
#    define APP_SWITCHER_TERM 1000
#endif

static bool     app_switcher_active = false;
static bool     app_switcher_timing = false;
static uint16_t app_switcher_timer  = 0;



/**
 * Check if app switcher is active.
 */
bool app_switcher_isactive() {
    return app_switcher_active;
}

/**
 * Check if app switcher has timed out. Call this from matrix_scan_user()
 */
void app_switcher_tick() {
    if (app_switcher_timing) {
        if (timer_elapsed(app_switcher_timer) > APP_SWITCHER_TERM) {
            unregister_code16(SC(SC_APPSWITCH_START));
            app_switcher_active = false;
            app_switcher_timing = false;
        }
    }
}

/**
 * Record a keypress. Call this from process_record_user(). Note that
 * app_switcher_release() must be called later.
 */
void app_switcher_record(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (!app_switcher_active) {
            app_switcher_active = true;
            register_code16(SC(SC_APPSWITCH_START));
        }
        register_code16(keycode == CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
    } else {
        unregister_code16(keycode == CU_APPR ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
    }
}


/**
 * Trigger an app change. This starts the timer that will release the app
 * switcher when it times out. Typically called from encoder_update_user()
 */
void app_switcher_trigger(bool forward) {
    if (!app_switcher_active) {
        app_switcher_active = true;
        app_switcher_timing = true;
        register_code(SC(SC_APPSWITCH_START));
    }
    app_switcher_timer = timer_read();
    tap_code16(forward ? SC(SC_APPSWITCH_RIGHT) : SC(SC_APPSWITCH_LEFT));
}


/**
 * Release the app switcher. 
 */
void app_switcher_release() {
    if (app_switcher_active) {
        unregister_code16(SC(SC_APPSWITCH_START));
    }
    app_switcher_active = false;
    app_switcher_timing = false;
}
