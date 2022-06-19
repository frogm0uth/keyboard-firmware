This folder is only used if compiling os-dependent shortcuts into the keymap statically.

If os_shortcut_defs.h is updated **and** OS_SHORTCUTS_STATIC is defined in config.h,
the files in this directory will need to be updated by running the
os_shortcuts_update.sh script e.g.

cd os_shortcuts_static
bash ./os_shortcuts_update.sh

This could probably be done automatically with a makefile rule.
