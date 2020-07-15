# Kyria RSTHD' ("RSTHD-prime")

This is the keymap I use on my Kyria keyboard from [splitkb.com](https://splitkb.com).

<!--ts-->
   * [Kyria RSTHD' ("RSTHD-prime")](#kyria-rsthd-rsthd-prime)
   * [Overview](#overview)
      * [Background/design principles](#backgrounddesign-principles)
      * [Main features](#main-features)
      * [Work in Progress/TODO](#work-in-progresstodo)
   * [Layers](#layers)
      * [RSTHD](#rsthd)
      * [Prime](#prime)
      * [Numpad](#numpad)
      * [Syntax](#syntax)
      * [Edit](#edit)
      * [Cursor](#cursor)
      * [Func](#func)
      * [Adjust](#adjust)
   * [Special keys](#special-keys)
   * [Acknowledgments](#acknowledgments)

<!--te-->

# Overview

The alphabetic layout is based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/). There are two default layers: one which preserves the alphabetic characters but does move Shift and punctuation, and one which is more extensively modified. The selection of default layer is stored in EEPROM.

This keymap is perhaps a bit more "traditional" than other QMK layouts that I see being designed for small keyboards, as I haven't used QMK features such as mod-tap, tap-dance, or combos. Instead, each modifier has its own dedicated key on each hand, most of them being on the pinky. The Kyria does have a few more keys than some — mine is configured with 44. I've done a number of other things a bit differently, but I hope the extensive/different customization doesn't put people off trying RSTHD itself, as it's an innovative and effective base layout.

I have tried to make the keymap work fluidly, both in the base alpha layer and with the interaction between layers. The Kyria has some nice features such as OLEDs and encoders, which I try to use to good effect.

*This is still a work in progress.* I'm refining it and polishing rough edges as I use it in my daily work more. 

## Background/design principles

My desires with this keyboard layout are:

1. Accuracy
2. Platform-independence
3. Comfort

Speed, reducing the number of keys, or coding keyboard firmware for fun are not important goals for me.

## Main features

* A modified RSTHD as the alpha layout.

* A custom layer switching code, which is like a merger or QMK's LT() and TG() functions. More information is [here](../../../../keyboard-notes/tree/master/qmk-layer-tap-toggle).

* The ability to select the OS in use (currently Mac and Windows supported) from the keyboard, which changes the shortcuts programmed into the keyboard. More information is [here](../../../../keyboard-notes/tree/master/qmk-os-shortcuts).

* A custom mouse feature to make mouse keys more controllable. More information is [here](../../../../keyboard-notes/tree/master/qmk-custom-mouse).

* A custom editing layer for platform-independent editing. More information is [here](../../../../keyboard-notes/tree/master/qmk-custom-edit).

* Matching use of the encoders on each layer.

* Informative info on the OLED. (Unfortunately, at the moment only the left OLED can be usefully used.) 

## Work in Progress/TODO

1. Windows functionality is barely tested / needs work
2. Custom Mouse needs more work on wheel speed.
5. OLED displays need some refinement.
7. Is it possible to make selection of the right-handed version of the Cursor layer dynamic?
5. This doc needs to be fleshed out. Keymap images in particular.


# Layers

There are a total of 8 layers. The first two are alternate base layers, which can be selected from the keyboard. The selection persists across reboots so once set there's no need to change it again.

The remaining 6 layers are alternately activated from the left or right thumb. On each layer, the opposite side to the layer key is considered "primary" and the side with the activation key is "auxiliary". Usually, I hold the layer key to keep the layer activated, but the layer can be toggled on by pressing the layer key with Shift down.

Many of these layers use the inner column for meta-operations like window navigation and screenshots. See Special keys [link] further below.

Most layers use one or both of the encoders. Where possible, the encoder function is appropriate for the function of that layer. If the encoder on the auxiliary side is used, the layer will need to be locked to use it.

For now, there are no images of the key layout, these will come later once the keymap fully stabilizes. For now, please refer to the ASCII art in keymap.c.

## RSTHD

This is RSTHD, modified a little to fit into a smaller keyboard (the author of RSTHD used an Ergodox). Most punctuation is moved to other layers. In addition, to reduce lateral movement on the pinkies, the Shift keys are moved to the location underneath pinky home. I've changed the three remaining punctuation keys to use the same pairs as the Prime layer (below) so that it still works well with the other layers in the keymap.

Left encoder is page up/down. With **Alt** held, move forward and back through search results. With **Cmd** held, move forward and back through browser history. Encoder push is screen lock.

Right encoder is the app switcher (Cmd-Tab on Mac, Alt-Tab on Windows). With **Cmd** held, cycle left and right through tabs of a window. With **Ctrl** held, cycle left and right through tabs of a window, for those applications that don't respond to the standard macOS shortcuts (applicable to macOS only). Encoder push is system sleep.

## Prime

This is my preferred base layer, using a layout I call RSTHD' ("RSTHD prime") [link].

Note that the link above points to a version that I developed for the Kinesis Advantage, which has a 3D keywell. I don't consider it quite optimal for the Kyria. It's very interesting how different actions are easier depending on the physical keyboard, particularly around the pinky keys and the inner column. However, I'm running with it until I find time to re-optimize for the Kyria.

Encoder use is the same as for the RSTHD layer.

## Numpad

Activation: left thumb. Primary keys on right, auxiliary keys on left.

The number keys 1 – 9 are on the right, arranged in a 3x3 grid. 1 – 3 are on the home row, as these are the most frequent digits. Arithmetic operators are on the left, along with 0 and ".". Note that it's assumed that all digits have their corresponding punctuation character available with Shift, but some of these are duplicated on the Syntax layer.

Left encoder (auxiliary side) is screen zoom in/out. Encoder push resets to default (macOS only).

Right encoder (primary side) is application window zoom in/out. Encoder push resets to default.

## Syntax

Activation: right thumb. Primary keys on left, auxiliary keys on right.

Named because I think of it as enabling the syntax of common programming languages. (I think a non-programmer will also find this layer easy to use, although the logic behind the key arrangement may not be so obvious.)

On the left are three pairs of pairing punctation: **[ ]**, **{ }**, and **< >**. Space and Enter are duplicated on the left thumb and Tab is duplicated on the right hand, making it easy to "roll" common sequences such as **}<Enter><Tab>**. Parentheses **) (** are on the right hand, ensuring there are no same-finger conflicts in common sequences such as **){**. Other punctuation on this layer is commonly used in a range of coding languages; where possible they are arranged for "rolls," such as **<?** and **/>**.

Left encoder (primary side) is mouse wheel up/down. With Shift pressed, it is wheel right/left.

## Edit

Activation: left thumb. Primary keys on right, auxiliary keys on left.

This is an editing layer based on my [Custom Edit](../../../../keyboard-notes/tree/master/qmk-custom-mouse) code.

Left encoder (auxiliary side) is history scrubbing i.e. undo and redo.

Right encoder (primary side) moves the cursor left and right by a character. With **Acc1** held, by words; with **Acc2** held, by paragraphs. If **DMod** is held, it deletes instead of moving. If **Rept** is held down, then movement or deletion is vertical.

## Cursor

Activation: right thumb. Primary keys on left, auxiliary keys on right.

This is a cursor movement layer based on my [Custom Mouse](../../../../keyboard-notes/tree/master/qmk-custom-mouse) code.

Left encoder (primary side) moves the mouse cursor right/left by the amount set by the accelerator keys. If **Rept** is held down, it moves down/up. Encoder push is mouse button 1. 

Right encoder (auxiliary side) is history scrubbing i.e. undo and redo.

These is also a "right-handed" version of this layer, which places the mouse keys on the right hand. Activation is still on the right thumb. To use the encoders on this layer, the layer will need to be locked. To enable it, uncomment `#define CURSOR_RIGHTHANDED` in config.h.

## Func

Activation: left thumb and pinky. Primary keys on right, auxiliary keys on left.

This layer contains function keys. Since I hardly ever use them, the activation sequence isn't important and requires a chord with pinky and thumb.

## Adjust

Activation: right thumb and pinky. Primary keys on left, auxiliary keys on right.

This layer contains a few keys for adjusting volume and screen brightness. It also contains the keys for switching persistent layers and OS selection. Since it's not frequently used, the activation sequence isn't important and requires a chord with pinky and thumb.

Left encoder (primary side) increases/decreases audio volume. With Shift held, it increases/decreases screen brightness. Encoder push is mute.

Right encoder (auxiliary side) changes backlight hue. With **Cmd** held, it increases/decreases backlight brightness. WIth **Ctrl** held, it increases/decreases backlight saturation. Encoder push saves the current backlight setting to EEPROM.

# Special keys

TBC

# Acknowledgments

Table of contents created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc). To update, run

```
/path/to/gh-md-toc --insert README.md
```

Much inspiration came from the residents of the [splitkb discord server](https://splitkb.com/discord).

Thanks to the author of [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) for the great layout.

[QMK](https://qmk.fm) rocks!

