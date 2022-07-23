OLED_ENABLE = yes          # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
LEADER_ENABLE = no         # Enable the Leader Key feature
MOUSEKEY_ENABLE = no       # Enable the mousekey feature
 
SRC += shortcuts.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder.c
endif
