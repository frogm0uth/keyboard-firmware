# Kyria RSTHD/Prime

**Under development.** This is a keymap I'm working on for my Kyria keyboard from [splitkb.com](https://splitkb.com). The alpha layouts are based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/). There are two default layers, one a lightly modified RSTHD and one heavily modified. For a more standard implementation of RSTHD on the Kyria, see my [Kyria Refactored](https://github.com/frogm0uth/keyboard-firmware/tree/master/kyria-refactored) keymap.

<!--ts-->
   * [Kyria RSTHD/Prime](#kyria-rsthdprime)
   * [Overview](#overview)
      * [Background/design principles](#backgrounddesign-principles)
      * [Main features](#main-features)
      * [Work in Progress/TODO](#work-in-progresstodo)
   * [Layers](#layers)
      * [RSTHD-s](#rsthd-s)
      * [Prime](#prime)
      * [Numpad](#numpad)
      * [Syntax](#syntax)
      * [Edit](#edit)
      * [Cursor](#cursor)
      * [Func](#func)
   * [Acknowledgments](#acknowledgments)

<!--te-->

# Overview

The alphabetic layouts in this keymap are based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/), one lightly modified ("RSTHD-s") and one heavily modified ("Prime").

The first default layer is a lightly modified version of RSTHD that moves the Shift keys underneath pinky home. The second is a further development of my RSTHD' ("RSTHD prime") layout that I developed for the Kinesis Advantage keyboard but which aims to reduce finger travel distance even more.

The two default layers can be selected with keys on the Function layer, and the selection is stored in EEPROM.

This keymap is perhaps a bit more "traditional" than other QMK layouts that I see being designed for small keyboards, as I haven't used the QMK features tap-dance, one-shot keys or combos. I've used mod-tap on just one key (Alt) – the other modifiers have dedicated keys on each hand.

I have tried to make the keymap work fluidly, both in the base layers and with the interaction between layers. The Kyria has some nice features such as OLEDs and encoders, which I try to use to good effect.

***This is currently under development.***

## Background/design principles

My desires with this keyboard layout are:

1. Accuracy
2. Platform-independence
3. Comfort

Speed and reducing the number of keys in use are not important goals for me.

## Main features

* Two different alpha layers derived from RSTHD.
* A custom layer switching code, which is like a merger or QMK's LT() and TG() functions. More information (*now out of date*) is [here](../../../../keyboard-notes/tree/master/qmk-layer-tap-toggle).
* The ability to select the OS in use (currently Mac and Windows supported) from the keyboard, which changes the shortcuts programmed into the keyboard. More information is [here](../../../../keyboard-notes/tree/master/qmk-os-shortcuts).
* A custom mouse feature to make mouse keys more controllable. More information is [here](../../../../keyboard-notes/tree/master/qmk-custom-mouse).
* A custom editing layer for platform-independent editing. More information is [here](../../../../keyboard-notes/tree/master/qmk-custom-edit).
* A *Compose* key. In this keymap, it replaces the Leader key. More information (*now out of date*) is [here](../../../../keyboard-notes/tree/master/qmk-compose-key).
* Matching use of the encoders on each layer.
* Informative info on the OLED. (Unfortunately, at the moment only the left OLED can be usefully used.) 

## Work in Progress/TODO

1. Windows shortcuts are barely tested / need work.
2. Linux shortcuts are non-existent.
3. Custom Mouse needs work on acceleration and wheel speed.
4. OLED displays need some refinement.
5. This doc needs to be fleshed out.


# Layers

There are a total of 7 layers. The first two are alternate base layers, which can be selected from the keyboard. The selection persists across reboots so once set there's no need to change it again.

The remaining 5 layers are activated from the left or right thumb. On each layer, the opposite side to the layer key is considered "primary" and the side with the activation key is "auxiliary". Usually, I hold the layer key to keep the layer activated, but the layer can be locked on by pressing the layer key with Cmd down.

Some of these layers use the inner column for window navigation.

Most layers use one or both of the encoders. Where possible, the encoder function is appropriate for the function of that layer. If the encoder on the auxiliary side is used, the layer will need to be locked to use it.

Click on the KLE links to see images of each layer. You can also refer to the ASCII art in keymap.c.

## RSTHD-s

This layer is fairly close to the original RSTHD, but a) modified to fit the smaller keyboard and b) the Shift keys are moved underneath pinky home to reduce lateral movement. The punctuation has also been changed a bit.

[KLE link](http://www.keyboard-layout-editor.com/#/gists/8e10a6af1d87573d14b4e6fdcc52b9dd)

## Prime

This layer is my "daily driver". It is originally based on RSTHD but is now so heavily modified that I'm not sure it's proper to use RSTHD in the name. But all credit to the original author of RSTHD. The name comes from a little mathematical wordplay from an earlier version that I called RSTHD' ("RSTHD-prime"), meaning a derivative of RSTHD. Since it's changed so much, I now just call it Prime. (In other words, the name is a combination of a joke and evolution, I'm not being self-aggrandizing :) )

[KLE link](http://www.keyboard-layout-editor.com/#/gists/0048853ae7914074816beda3d796558c)

The optimizations that resulted in this layout aimed to reduce lateral finger movement and improve comfort. The layout does perform very well in an analyzer, with very low SFU (same finger utilization) stats and lower travel distance than most other layouts.

## Numpad

Activation: left thumb. Primary keys on right, auxiliary keys on left.

[KLE link](http://www.keyboard-layout-editor.com/#/gists/8a97196759bd98f7ef9a4e974423e145)

The number keys 1 – 9 are on the right, arranged in a 3x3 grid. 1 – 3 are on the home row, as these are the most frequent digits. Arithmetic operators are on the left, along with 0 and ".". Note that it's assumed that all digits have their corresponding punctuation character available with Shift, but some of these are also duplicated on the Syntax layer.

It's assumed that there will be times when this layer is locked on for an extended period, for numeric entry or spreadsheets. Therefore all the keys to access higher layers are here, which isn't the case for other layers.

Select all, cut, copy and paste are chorded on the left hand.

## Syntax

Activation: left thumb. Primary keys on right, auxiliary keys on left.

Named because I think of it as enabling the syntax of common programming languages. (I think a non-programmer will also find this layer easy to use, although the logic behind the key arrangement may not be so obvious.)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/0b079c6153a029c55cc8b5b7fbe701f2)

On the right are three pairs of pairing punctation: **] [**, **} {**, and **> <**. Parentheses **( )** are on the left hand to avoid same-finger conflicts in common sequences such as **)}**. Other punctuation on this layer is commonly used in a range of coding languages; where possible they are arranged for "rolls," such as **->**, **<?** and **/>**. Various other characters on the layer are there to avoid switching layers for digrams that commonly occur in coding/scripting such as **${**, **=>**, **<!**, and so on.

## Edit

Activation: right thumb. Primary keys on left, auxiliary keys on right.

[KLE link](http://www.keyboard-layout-editor.com/#/gists/380d4d3d2a51e2a0e125e939fe2eb56f)

This is an editing layer based on my [Custom Edit](../../../../keyboard-notes/tree/master/qmk-custom-edit) code. The navigation keys on the left have the standard four cursor keys, word left/right, and page up/down. Below the navigation keys are "hyper-back" and "hyper-forward" keys. Depending on modifiers pressed, these are undo/redo, browser back/forward, or next/previous search result.

Various special modifier keys on the right home row (see the above link). Select all, cut, copy and paste are chorded on the right hand. The inner columns are used for moving between windows, apps and tabs, which is fairly common to do when editing and copy/pasting.

## Cursor

Activation: Ctrl + right thumb. Primary keys on left, auxiliary keys on right.

[KLE link](http://www.keyboard-layout-editor.com/#/gists/8a2089637ad2a82eecfd5262a5ea9d1f)

This is a cursor movement layer based on my [Custom Mouse](../../../../keyboard-notes/tree/master/qmk-custom-mouse) code. Overall, the layout mimics the Edit layer except that the cursor keys move the mouse and the left thumb is used for mouse buttons. This layer also has keys to trigger various types of screenshot (some of which need moving the mouse before or after).

## Func

Activation: Ctrl + left thumb. Primary keys on right, auxiliary keys on left.

[KLE link](http://www.keyboard-layout-editor.com/#/gists/e09a2e00f963d27b25cdaf5962b9cb7f)

This layer contains function keys. It also contains the keys that change settings stored in EEPROM.

# Acknowledgments

Table of contents created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc). To update, run

```
/path/to/gh-md-toc --insert README.md
```

Much inspiration came from the residents of the [splitkb discord server](https://splitkb.com/discord).

Thanks to the author of [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) for the great layout.

[QMK](https://qmk.fm) rocks!

