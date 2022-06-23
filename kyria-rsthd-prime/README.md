# Kyria RSTHD/Prime

**Under development.** This is a keymap I'm working on for my Kyria keyboard from [splitkb.com](https://splitkb.com). The alpha layout was based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) but is now heavily modified. For a standard implementation of RSTHD on the Kyria, see my [Kyria Refactored](https://github.com/frogm0uth/keyboard-firmware/tree/master/kyria-refactored) keymap.

<!--ts-->
   * [Overview](#overview)
      * [Keyboard configuration](#keyboard-configuration)
      * [Goals](#goals)
   * [Layers](#layers)
      * [ALPHA](#alpha)
      * [SYMS](#syms)
      * [EDIT](#edit)
      * [SNAP](#snap)
      * [FUNC](#func)
      * [META](#meta)
   * [Other](#other)
      * [RSTHD variants and similar layouts](#rsthd-variants-and-similar-layouts)
      * [Acknowledgments](#acknowledgments)

<!-- Created by https://github.com/ekalinin/github-markdown-toc -->
<!-- Added by: username, at: Fri 24 Jun 2022 04:38:53 AEST -->

<!--te-->

## Overview

The alphabetic layout in this keymap was originally based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/). I tried it, liked it, tweaked it, and tweaked some more. For better or worse, this is the result...

When I originally started making changes to RSTHD, I called it RSTHD'. The `'`, pronounced "prime", is [used in maths](https://en.wikipedia.org/wiki/Prime_(symbol)#Use_in_mathematics,_statistics,_and_science) to indicate a derivative of the named thing. The layout still very much retains its RSTHD DNA despite all the changes. I figure calling it *RSTHD/Prime* acknowledges its origin while still indicating that it's different.

### Keyboard configuration

My Kyria uses all 6 columns on each hand, four thumb keys on each hand, one encoder on each hand. The top two thumb keys on each side are not on the board.

The controller is a Pro Micro and this keymap only just squeezes in.

### Goals

Coming from a "slab" QWERTY keyboard to a programmable ergo split, I wanted to optimize:

- Cross-platform portability. I need to switch between macOS and Windows frequently. The differences in shortcuts and location of Ctrl/Cmd keys was frustrating and programmable keyboards seemed to be the answer.
- Comfort. For me, that largely means de-emphasizing the inner index columns.
- Better support for ambidextrous use of the trackpad or mouses (I use two). That is, it should be possible to do things like cut-copy-paste from either hand alone.

Typing speed and reducing the number of keys on the keyboard are not important goals to me.

## Layers

There are a total of 6 layers. The first is the main alpha layer.

The other layers are activated with a thumb key. All are hold-to-activate &ndash; that is, no toggles or one-shots.

All layers have the OS-specific shortcuts in various places. These can be selected at run-time. For more info, see `os_shortcuts.h/c` and `os_shortcut_defs.h`.

### ALPHA

[KLE link](http://www.keyboard-layout-editor.com/#/gists/69cf0f771159d920a34d882d696af6aa)

The alpha layout aims to reduce lateral finger movement on the index finger. It performs very well in an analyzer, with low SFU (same finger utilization) stats and low travel distance.

Some of the punctuation keys use non-standard shift mappings. The SYMs layer does this for the numbers also. See `shift_defs.h`.

### SYMS

Activated by the left thumb (hold).

[KLE link](http://www.keyboard-layout-editor.com/#/gists/0b079c6153a029c55cc8b5b7fbe701f2)

Unshifted, this layer contains most of the punctuation keys. I've arranged them so that many common (in programming) two-letter sequences can be typed with an inward roll: `{% %} <% %> </ /> <? ?> <! => -> ~/`. Since most are on the right hand, they become an easy three-key roll with Space and Enter. 

Semicolon is, surprisingly enough, not in this layer: instead there is a combo for `);`.

The ten digits are accessed with Shift, akin to [Programmer Dvorak](https://www.kaufmann.no/roland/dvorak/), arranged in a 3x3 numpad-like grid. However the most frequent `0 1 2` can also be accessed as a single chord with no shift on the left hand.

### EDIT

Activated by the right thumb (hold).

[KLE link](http://www.keyboard-layout-editor.com/#/gists/24a80f5840733d6384fd21e20e1f28a0)

This is an editing layer that extends the idea of platform-independent shortcuts to a complete editing layer. The navigation keys on the left have the standard cursor keys, home/end and page up/down. There are various other window keys on this side. 

On the right side are various special modifier keys on the right home row to speed up editing. These will be documented one day... Select all, cut, copy and paste are chorded on the  top row, and keys to switch applications, windows and tabs on the inner column.

### SNAP

Activated by the left thumb (hold).

[KLE link](http://www.keyboard-layout-editor.com/#/gists/6aa3ef0fcb5c886dc105a94b62690fe0)

So called because of the keys for window snapping. (For macOS, these require that [Rectangle](https://rectangleapp.com) is installed.)

Select all, cut, copy and paste are chorded on the left hand top row, and keys to switch applications, windows and tabs on the inner column.

### FUNC
Activated by the pinky from the SNAP layer (hold).

[KLE link](http://www.keyboard-layout-editor.com/#/gists/e09a2e00f963d27b25cdaf5962b9cb7f)

This layer contains function keys on the right hand, arranged roughly the same as the numpad. It also contains the keys that switch between macOS, Windows and Linux shortcuts.

### META
Activated by the right thumb (hold).

[KLE link](http://www.keyboard-layout-editor.com/#/gists/c3f3f925be48f9c67de27b1e3b21ee37)

This layer contains common shortcut keys. They are mostly arranged according to the letter used in the Mac/Windows shortcut. For example, the S key invokes Save (Cmd-S on Mac, Ctrl-S on Windows). However, the mapping is not always that straightforward (e.g. Cmd-Q on Mac and Alt-F4 on Windows), hence the need for a dedicated layer.

## Other

### RSTHD variants and similar layouts
- [T-34](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/) (swaps E and space)
- [New layout for lateral movement haters](https://www.reddit.com/r/KeyboardLayouts/comments/mnumbs/new_layout_for_lateral_movement_haters/) (Some similarities to this layout)
- [RSTHD today](https://xsznix.wordpress.com/2021/01/13/rsthd-today/) (Latest layout generated by keygen with revised scoring and different corpus)
- [andrewjrae/kyria-keymap](https://github.com/andrewjrae/kyria-keymap) (Swaps E and Space)
- [johnm/keymap.c](https://gist.github.com/johnm/e3c129b20bbcae97601e547a7dd9fa0a) (Mirrors the complete alpha block, and some other tweaks)
- [Pressing E with the thumb‽](https://precondition.github.io/pressing-e-with-the-thumb) (Nice survey article of layouts with letters on a thumb key)

### Acknowledgments

Table of contents created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc). To update, run

```
/path/to/gh-md-toc --insert README.md
```

Much inspiration came from the residents of the [splitkb discord server](https://splitkb.com/discord).

Thanks to the author of [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) for the great layout.

[QMK](https://qmk.fm) rocks!

