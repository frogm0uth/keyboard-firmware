OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
LEADER_ENABLE = no         # Enable the Leader Key feature
MOUSEKEY_ENABLE = no       # Enable the inbuilt mouse key feature
TAP_DANCE_ENABLE = no      # Enable tap-dance (NB also uncomment #define NO_ACTION_TAPPING in config.h)
WPM_ENABLE = no		       # Enable simple WPM display

# COMMAND_ENABLE = no
# EXTRAKEY_ENABLE = no
# CONSOLE_ENABLE = yes

# frogm0uth features
OS_SHORTCUTS = yes	    # Enable OS shortcut mapping
CUSTOM_EDIT = yes	    # Enable custom editing keys
CUSTOM_MOUSE = yes	    # Enable custom mouse keys
LAYER_TAP_TOGGLE = yes	# Enable the layer-tap-toggle feature
COMPOSE_KEY = yes	    # Enable the custom compose key feature

# Uncomment one of the next lines to prevent unused variable/function errors
# in qmk_firmware/quantum/process_keycode/process_rgb.c from halting the compile
#EXTRAFLAGS += -Wno-unused-function -Wno-unused-variable
EXTRAFLAGS += -Wno-error=unused-variable -Wno-error=unused-function

# Don't edit from here down

SRC += appswitcher.c

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
	SRC += oled.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgblight.c
endif

ifeq ($(strip $(LEADER_ENABLE)), yes)
	SRC += leader.c
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
	POINTING_DEVICE_ENABLE := yes
	SRC += custom_mouse.c
	OPT_DEFS += -DCUSTOM_MOUSE
endif

ifeq ($(strip $(LAYER_TAP_TOGGLE)), yes)
	SRC += layer_tap_toggle.c
	OPT_DEFS += -DLAYER_TAP_TOGGLE
endif

ifeq ($(strip $(COMPOSE_KEY)), yes)
	SRC += compose_key.c compose_tree.c
	OPT_DEFS += -DCOMPOSE_KEY
endif
