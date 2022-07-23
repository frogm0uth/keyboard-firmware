# Kyria Refactored

This is a refactored version of the [thomasbaart](https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/thomasbaart) keymap for the Kyria keyboard from [splitkb.com](https://splitkb.com). It also has eight alpha layers, which can be selected from the keyboard, and support for different shortcuts for macOS and Windows.

## Refactoring

The original keymap.c has been split up into several files. If you are thinking of doing a lot of customization to your keymap, you may find this an easier starting point.

The rules.mk file has been modified so that the new source files are compiled and linked only if the corresponding feature is enabled. The main effect of this is that you can remove features in rules.mk by setting them to **no** without getting compile errors. This applies to the following: OLED_DRIVER_ENABLE, ENCODER_ENABLE.

## Default alpha layers

There are eight default alpha layers. This might be useful for anyone interested in trying out different key layouts on their Kyria. The keys to switch between them are on the left home row on the Navigation layer.

**Important**: if you plan to flash a different firmware, set the default layer back to QWERTY first. This will ensure that you aren't stuck in the wrong layer when you boot the other firmware.

The layers are:

1. [QWERTY](https://en.wikipedia.org/wiki/QWERTY)
2. [Colemak-DHm](https://colemakmods.github.io/mod-dh/)
3. [Workman](https://workmanlayout.org)
4. [Dvorak](https://en.wikipedia.org/wiki/Dvorak_keyboard_layout)
5. [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/)
6. [Maltron](https://www.maltron.com/the-maltron-letter-layout-advantage.html) (There seem to be variants of the layout with regard to where punctuation characters are placed. I've used the one on the Maltron website which is presumably definitive.)
7. [BEAKL](https://ieants.cc/code/keyboard/beakl/). (This is version 15. Currently the punctuation pairs do not conform to that page.)
8. [MTGAP](https://keyboard-design.com/best-keyboard-layouts.html). (Scroll down to MTGap TS ErgoLinear 2. I am unsure of what version of MTGAP this is, as there have been quite a number. Currently the punctuation pairs do not conform to that page.)

In order that all layers work similarly, I have changed the thumb key layout a little. The left innermost thumb key is mod-tap Alt+Backspace, and the right innermost thumb key is a layer-tap Nav+Enter. (The Nav was previously on the Space, but I have moved it to Enter.)

The last two layers use the left thumb for the E key, so the Shift that was there in the other layers has been moved to the right pinky.

To change default layer, press the right inner thumb to activate the Nav layer, and use the left home row and top row. The Nav layer will deactivate so the OLED displays the new default layer.

## OS selection and shortcuts

There are three places in the thomasbaart keymap where Windows-specific shortcuts are used. In this refactored version, you can press a key on the keyboard to select Windows or macOS. Then the correct shortcuts for the selected OS will be output.

To change default layer, press the right inner thumb to activate the Nav layer, and use the index and middle fingers of the left side bottom row.

The OS selection is displayed on the OLED.

If you need more shortcuts, add them to shortcuts.c. You will also need to add entries to the `shortcut_codes` enum in keymap.h.  Use the `SC()` macro to invoke them. If you need a more complex version of this (automatic generation of keycodes, optional static compile), see my [OS Shortcuts](../../../../keyboard-notes/tree/master/qmk-os-shortcuts) code.

## RGB animation

Just for fun, I've enabled the encoders on the Nav layer to control RGB animation. While in the Nav layer:

* Rotate the left encoder to change to a different animation
* Push the left encoder to change back to steady (no animation)
* Push the right encoder to turn RGB LEDs on and off.

## Issues?

This is not my daily driver, so there could be issues in the code. If you do find an problem, please ping @frogmouth on the [splitkb discord](https://splitkb.com/discord).

