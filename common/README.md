# Common code

This is my folder for code shared between my keyboards. I have a number of custom features that I've implemented to make them work "just right" for *me*.

<!--ts-->
* [Platform-independent shortcuts](#platform-independent-shortcuts)
* [Comborolls](#comborolls)
* [Custom shift keys](#custom-shift-keys)
* [Custom layer switching](#custom-layer-switching)
* [Custom edit modifiers](#custom-edit-modifiers)
* [Caps word](#caps-word)
* [Acknowledgments](#acknowledgments)

<!--te-->



## Platform-independent shortcuts

A set of shortcuts which can be switched at run-time for macOS, Windows, or Linux. macOS shortcuts are pretty stable, Windows and Linux still need work. For more info, see `os_shortcut_defs.h` for definitions and `os_shortcuts.h/c` for implementation.

## Comborolls

I have a userspace implementation of combos called "[comboroll](../kyria-rsthd-prime/docs/comborolls.md)" to avoid timing issues with QMK's overlapping combos. See `combo_defs.h` for combo definitions and `comboroll.h/c` for the implementation.

## Custom shift keys

I generalized the notion of having a non-standard character output on shift so that any unshifted/shifted pair can be defined with a macro. See `shift_defs.h` for definitions and `process.h/c` for the implementation.

## Custom layer switching

Layer switching is done with custom code, so that a. shifted and custom keys can be emitted on the tap and b. so that the layer activates immediately for faster access to the keys in the layer. See `layer_tap_toggle.h/c`.

## Custom edit modifiers

This is platform independent shortcuts taken to the max. I can never reliably remember which modifiers do what to the arrow keys on which platform so I've defined a set of custom modifiers. See the EDIT layer below and `custom_edit.h/c` for the implementation.

## Caps word

This is my particular implementation. In addition to working with my custom keycodes, I've added some tweaks like toggling caps-word if both shift keys are pressed and "auto unshift". See `custom_capsword.h/c`.



## Acknowledgments

Table of contents created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc). To update, run

```
/path/to/gh-md-toc --insert README.md
```


