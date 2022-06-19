OLED_DRIVER_ENABLE = yes    # Enables the use of OLED displays
ENCODER_ENABLE = yes        # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
LEADER_ENABLE = no          # Enable the Leader Key feature
MOUSEKEY_ENABLE = no        # Enable the inbuilt mouse key feature
TAP_DANCE_ENABLE = no       # Enable tap-dance (NB also uncomment #define NO_ACTION_TAPPING in config.h)
WPM_ENABLE = no		    # Enable simple WPM display
COMBO_ENABLE = no	    # Enable combo (chording) functionality
CAPS_WORD_ENABLE = no	    # Enable the caps-word feature. Doesn't work properly with combos.
# COMMAND_ENABLE = no
# EXTRAKEY_ENABLE = no
# CONSOLE_ENABLE = yes

CONSOLE_ENABLE = no

# frogm0uth features
OS_SHORTCUTS = yes	    # Enable OS shortcut mapping. If this is turned off, the keymap
			    # will still compile but a bunch of things won't work. Check the
			    # definition of OS_SHORTCUTS_STATIC in config.h.

CUSTOM_EDIT = yes	    # Enable custom editing keys
LAYER_TAP_TOGGLE = yes      # Enable the layer-tap-toggle feature
CUSTOM_MOUSE = yes	    # Enable custom mouse keys
COMBOROLL_ENABLE = yes	    # Enable comborolls

# Uncomment one of the next lines to prevent unused variable/function errors
# in qmk_firmware/quantum/process_keycode/process_rgb.c from halting the compile
EXTRAFLAGS += -Wno-unused-function -Wno-unused-variable
EXTRAFLAGS += -Wno-error=unused-variable -Wno-error=unused-function

### FIXME no longer needed?
EXTRAFLAGS += -flto

# Don't edit from here down

SRC += appswitcher.c

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
	SRC += oled.c
	OPT_DEFS += -DOLED_DRIVER_ENABLE
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder.c
	OPT_DEFS += -DENCODER_ENABLE
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgblight.c
	OPT_DEFS += -DRGBLIGHT_ENABLE
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combos.c
	OPT_DEFS += -DCOMBO_ENABLE
endif

ifeq ($(strip $(COMBOROLL_ENABLE)), yes)
	SRC += combos.c
	OPT_DEFS += -DCOMBOROLL_ENABLE
endif

ifeq ($(strip $(OS_SHORTCUTS)), yes)
	SRC += os_shortcuts.c
	OPT_DEFS += -DOS_SHORTCUTS
endif

ifeq ($(strip $(CUSTOM_EDIT)), yes)
	SRC += custom_edit.c
	SRC += os_shortcuts.c
	OPT_DEFS += -DCUSTOM_EDIT -DOS_SHORTCUTS
endif

ifeq ($(strip $(CUSTOM_MOUSE)), yes)
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = custom
	SRC += custom_mouse.c
	OPT_DEFS += -DCUSTOM_MOUSE
endif

ifeq ($(strip $(LAYER_TAP_TOGGLE)), yes)
	SRC += layer_tap_toggle.c
	OPT_DEFS += -DLAYER_TAP_TOGGLE
endif
