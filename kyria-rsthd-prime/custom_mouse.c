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
 ** Custom mouse movement
 **/
static uint8_t mousekey_bits = 0;
static uint8_t mousekey_mods = 0;
static uint8_t mouse_buttons = 0;

#define IS_MOUSE_REPT (mousekey_mods & CM_MOD_BIT(CM_REPT))
#define IS_MOUSE_SLOW (mousekey_mods & CM_MOD_BIT(CM_SLOW))
#define IS_MOUSE_ACC1 (mousekey_mods & CM_MOD_BIT(CM_ACC1))
#define IS_MOUSE_ACC2 (mousekey_mods & CM_MOD_BIT(CM_ACC2))
#define IS_MOUSE_WHEE (mousekey_mods & CM_MOD_BIT(CM_WHEE))

#define IS_MOUSE_BTN1 (mouse_buttons & CM_BUTTON(CM_BTN1))
#define IS_MOUSE_BTN2 (mouse_buttons & CM_BUTTON(CM_BTN2))
#define IS_MOUSE_BTN3 (mouse_buttons & CM_BUTTON(CM_BTN3))

static uint16_t custom_mouse_timer = 0;
static uint16_t custom_wheel_timer = 0;
static uint16_t wheel_repeat_term = WHEEL_REPEAT_TERM;


void custom_mouse_action(void) {
  report_mouse_t currentReport = pointing_device_get_report();
  uint8_t delta = (IS_MOUSE_ACC1 ? 1 : 0) + (IS_MOUSE_ACC2 ? 2 : 0);
  uint8_t accel = IS_MOUSE_SLOW
    ? 3 - delta
    : 4 + delta;
  uint16_t increment = 1 << accel;

  if (increment > 127) increment = 127;

  if (mousekey_bits & CM_BIT(CM_MS_L)) {
    currentReport.x = -increment;
  } else if (mousekey_bits & CM_BIT(CM_MS_R)) {
    currentReport.x = increment;
  }
  if (mousekey_bits & CM_BIT(CM_MS_U)) {
    currentReport.y = -increment;
  } else if (mousekey_bits & CM_BIT(CM_MS_D)) {
    currentReport.y = increment;
  }
  pointing_device_set_report(currentReport);
  pointing_device_send();
  custom_mouse_timer = timer_read();
}

void custom_wheel_action(void) {
  report_mouse_t currentReport = pointing_device_get_report();
  uint8_t accel = 5 + (IS_MOUSE_ACC1 ? 1 : 0) + (IS_MOUSE_ACC2 ? 2 : 0);
  uint16_t increment = 1 << accel;

  if (increment > 127) increment = 127;

  wheel_repeat_term = IS_MOUSE_SLOW
    ? WHEEL_REPEAT_TERM * 2
    : (IS_MOUSE_ACC2
       ? WHEEL_REPEAT_TERM / 2
       : WHEEL_REPEAT_TERM);

  if (mousekey_bits & CM_BIT(CM_MS_L)) {
    currentReport.h = increment;
  } else if (mousekey_bits & CM_BIT(CM_MS_R)) {
    currentReport.h = -increment;
  }
  if (mousekey_bits & CM_BIT(CM_MS_U)) {
    currentReport.v = -increment;
  } else if (mousekey_bits & CM_BIT(CM_MS_D)) {
    currentReport.v = increment;
  }
  pointing_device_set_report(currentReport);
  pointing_device_send();
  custom_wheel_timer = timer_read();
}

void custom_mouse_tick (void) { // Call from matrix_scan_user()
  if (IS_MOUSE_REPT && mousekey_bits) {
    if (IS_MOUSE_WHEE) {
      if (timer_elapsed(custom_wheel_timer) > wheel_repeat_term) {
	custom_wheel_action();
      }
    } else {
      if (timer_elapsed(custom_mouse_timer) > MOUSE_REPEAT_TERM) {
	custom_mouse_action();
      }
    }
  }
}

void custom_mouse_button_record (uint16_t keycode, keyrecord_t *record) {
  custom_mouse_button_press(keycode, record->event.pressed);
}

void custom_mouse_button_press (uint16_t keycode, bool pressed) {
  report_mouse_t currentReport = pointing_device_get_report();
  if (pressed) {
    switch (keycode) {
    case CM_BTN1:
      if (IS_MOUSE_BTN1) { // ignore if already pressed
	return;
      }
      currentReport.buttons |= MOUSE_BTN1;
      break;
    case CM_BTN2:
      if (IS_MOUSE_BTN2) { // ignore if already pressed
	return;
      }
      currentReport.buttons |= MOUSE_BTN2;
      break;
    case CM_BTN3:
      if (IS_MOUSE_BTN3) { // ignore if already pressed
	return;
      }
      currentReport.buttons |= MOUSE_BTN3;
      break;
    }
    mouse_buttons |= CM_BUTTON(keycode);

  } else {
    switch (keycode) {
    case CM_BTN1:
      currentReport.buttons &= ~MOUSE_BTN1;
      break;
    case CM_BTN2:
      currentReport.buttons &= ~MOUSE_BTN2;
      break;
    case CM_BTN3:
      currentReport.buttons &= ~MOUSE_BTN3;
      break;
    }
    mouse_buttons &= ~CM_BUTTON(keycode);
  }
  pointing_device_set_report(currentReport);
  pointing_device_send();
}

void custom_mouse_mod(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    mousekey_mods |= CM_MOD_BIT(keycode);
    if (keycode==CM_REPT) {
      if (mousekey_mods & CM_MOD_BIT(CM_WHEE)) {
	custom_wheel_action();
      } else {
	custom_mouse_action();
      }
    }
  } else {
    mousekey_mods &= ~CM_MOD_BIT(keycode);
  }
}

void custom_mouse_record(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    mousekey_bits |= CM_BIT(keycode);
    if (IS_MOUSE_WHEE) {
      custom_wheel_action();
    } else {
      custom_mouse_action();
    }
  } else {
    mousekey_bits &= ~CM_BIT(keycode);
  }
}

#ifdef ENCODER_ENABLE
void custom_mouse_encoder(bool clockwise) {
  uint16_t keycode = (IS_MOUSE_REPT)
    ? (clockwise ? CM_MS_D : CM_MS_U)
    : (clockwise ? CM_MS_R : CM_MS_L);
  
  mousekey_bits |= CM_BIT(keycode);
  ;
  if (IS_MOUSE_WHEE) {
    custom_wheel_action();
  } else {
    custom_mouse_action();
  }
  mousekey_bits &= ~CM_BIT(keycode);
}


void custom_wheel_encoder(bool clockwise, bool rotate) {
  uint16_t keycode = rotate
    ? (clockwise ? CM_MS_D : CM_MS_U)
    : (clockwise ? CM_MS_R : CM_MS_L);
  
  mousekey_bits |= CM_BIT(keycode);
  custom_wheel_action();
  mousekey_bits &= ~CM_BIT(keycode);
}
#endif

#ifdef OLED_DRIVER_ENABLE
void custom_mouse_status () {
  if (IS_MOUSE_WHEE) {
    oled_write_P(PSTR("WHEEL "), false);
  }
  if (IS_MOUSE_REPT) {
    oled_write_P(PSTR("RPT "), false);
  }
  if (IS_MOUSE_BTN1) {
    oled_write_P(PSTR("(1) "), false);
  }
  if (IS_MOUSE_BTN2) {
    oled_write_P(PSTR("(2) "), false);
  }
  if (IS_MOUSE_BTN3) {
    oled_write_P(PSTR("(3) "), false);
  }
      
  uint8_t delta = (IS_MOUSE_SLOW ? 1 : 0) + (IS_MOUSE_ACC1 ? 1 : 0) + (IS_MOUSE_ACC2 ? 2 : 0);
  char delta_s[2];
  if (delta) {
    if (IS_MOUSE_SLOW) {
      oled_write_P(PSTR("-"), false);
    } else {
      oled_write_P(PSTR("+"), false);
    }
    itoa(delta, delta_s, 10);
    oled_write(delta_s, false);
  }
}
#endif
