OLED_ENABLE = yes           # Enables the use of OLED displays
ENCODER_ENABLE = yes        # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
LEADER_ENABLE = no          # Enable the Leader Key feature
MOUSEKEY_ENABLE = yes       # Enable the inbuilt mouse key feature
TAP_DANCE_ENABLE = no       # Enable tap-dance (NB also uncomment #define NO_ACTION_TAPPING in config.h)
WPM_ENABLE = no             # Enable simple WPM display
COMBO_ENABLE = no           # Enable combo (chording) functionality
CAPS_WORD_ENABLE = no       # Enable the caps-word feature. Doesn't work properly with combos.

LTO_ENABLE = yes            # Firmware size reduction - https://docs.qmk.fm/#/squeezing_avr
EXTRAKEY_ENABLE = yes       # Needed for volume control, system sleep/lock
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
MUSIC_ENABLE = no

# frogm0uth features
OS_SHORTCUTS = yes          # Enable OS shortcut mapping. If OS_SHORTCUTS_STATIC in config.h is
                            # defined, shortcuts will be statically compiled in. The script
                            # os_shortcuts_static/os_shortcuts_update.sh will need to be run to
                            # generate the static definitions files. Otherwise (and recommended)
                            # shortcuts will be selected at runtime. If this is turned off, the
                            # keymap will still compile but a bunch of things won't work. Note that
                            # this is forced on by CUSTOM_EDIT.

CUSTOM_MOUSE = no           # Enable custom mouse keys. If disabled and MOUSEKEY_ENABLED is defined,
                            # the key codes in custom_mouse.h are #defined to the QMK keycodes.

CUSTOM_EDIT = yes           # Enable custom editing keys. Turns on OS_SHORTCUTS.
LAYER_TAP_TOGGLE = yes      # Enable the layer-tap-toggle feature
COMBOROLL_ENABLE = yes      # Enable comborolls - not compatible with COMBO_ENABLE

# Uncomment one of the next lines to prevent unused variable/function errors
# from halting the compile
//EXTRAFLAGS += -Wno-unused-function -Wno-unused-variable
EXTRAFLAGS += -Wno-error=unused-variable -Wno-error=unused-function


# Don't edit from here down

SRC += appswitcher.c

ifeq ($(strip $(OLED_ENABLE)), yes)
        SRC += oled.c
        OPT_DEFS += -DOLED_ENABLE
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
        OPT_DEFS += -DCOMBO_ENABLE -DCOMBO_MUST_PRESS_IN_ORDER_PER_COMBO -DCOMBO_TERM_PER_COMBO
endif

ifeq ($(strip $(COMBOROLL_ENABLE)), yes)
        SRC += comboroll.c
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
