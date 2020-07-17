# Kyria Refactored

This is a refactored version of the [thomasbaart](https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/thomasbaart) keymap for the Kyria keyboard from [splitkb.com](https://splitkb.com). It also has four base layers, which can be selected from the keyboard, and support for different shortcuts for macOS and Windows.

## Refactoring

The original keymap.c has been split up into several files. If you are thinking of doing a lot of customization to your keymap, you may find this an easier starting point.

The rules.mk file has been modified that the new source files are compiled and linked only if the corresponding feature is enabled. The main effect of this is that you can remove features in rules.mk by setting them to **no** without getting compile errors. This applies to the following: OLED_DRIVER_ENABLE, ENCODER_ENABLE, LEADER_ENABLE.

## Default layers

There are four default layers. This might be useful for anyone who wants to try out a different key layout on their Kyria. The keys to switch between them are on the left home row on the Navigation layer.

**Important**: if you plan to flash a different firmware, set the default layer back to QWERTY first. This will ensure that you don't boot up stuck in the wrong layer on the other firmware.

The layers are:

1. QWERTY
2. [Colemak-DHm](https://colemakmods.github.io/mod-dh/)
3. [Workman](https://workmanlayout.org)
4. [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/)

The last uses the left thumb for the E key, so the Space that was previously there has been removed. (Space is also on the right thumb anyway.) I removed the Shift as well and put it on the right pinky.

## OS selection and shortcuts

There are three places in the thomasbaart keymap where Windows-specific shortcuts are used. In this refactored version, you can press a key on the keyboard to select Windows or macOS. Then the correct shortcuts for the selected OS will be output. These keys are above the left home row (index and middle fingers) on the Navigation layer.

The OS selection is displayed on the OLED.

If you need more shortcuts, add them to shortcuts.c. You will also need to add entries to the `shortcut_codes` enum in keymap.h.  Use the `SC()` macro to invoke them. If you need a more complex version of this (automatic generation of keycodes, optional static compile), see my [OS Shortcuts](../../../../keyboard-notes/tree/master/qmk-os-shortcuts) code.

## Issues?

This is not fully tested yet, especially on Windows.

If you try this keymap and run into issues, please ping @frogmouth on the [splitkb discord](https://splitkb.com/discord).

