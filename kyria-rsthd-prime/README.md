# Kyria RSTHD/Prime

This is the keymap for my Kyria keyboard from [splitkb.com](https://splitkb.com). The alpha layout was based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) but is now heavily modified. It's optimized for cross-platform portability and minimized usage of the inner index column.

<!--ts-->
* [Kyria RSTHD/Prime](#kyria-rsthdprime)
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
      * [How to build](#how-to-build)
      * [RSTHD variants and similar layouts](#rsthd-variants-and-similar-layouts)
      * [Relevant articles and resources](#relevant-articles-and-resources)
      * [Acknowledgments](#acknowledgments)

<!-- Created by https://github.com/ekalinin/github-markdown-toc -->
<!-- Added by: username, at: Wed 29 Jun 2022 12:45:29 AEST -->

<!--te-->

## Overview

The alphabetic layout in this keymap was originally based on [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/). I tried it, liked it, tweaked it, and tweaked some more...

When I originally started making changes to RSTHD, I called it RSTHD'. The `'`, pronounced "prime", is [used in maths](https://en.wikipedia.org/wiki/Prime_(symbol)#Use_in_mathematics,_statistics,_and_science) to indicate a derivative of the named thing. The layout still very much retains its RSTHD DNA despite all the changes. I figure calling it *RSTHD/Prime* acknowledges its origin while still indicating that it's different.

If you're interested in a standard implementation of RSTHD on the Kyria, see my [Kyria Refactored](https://github.com/frogm0uth/keyboard-firmware/tree/master/kyria-refactored) keymap. See also the links to other layouts at the bottom of the page.

### Keyboard configuration

My Kyria uses all 6 columns on each hand. The left side has an OLED, an encoder, and four thumb keys. The right side has no OLED or encoder, and four thumb keys. The top two thumb keys on each side are not on the board.

The controller is a Pro Micro and this keymap only just squeezes in.

### Goals

Coming from a "slab" QWERTY keyboard to a programmable ergo split, I wanted to optimize:

- Cross-platform portability. I need to switch between macOS and Windows frequently. The differences in shortcuts and location of Ctrl/Cmd keys was frustrating and programmable keyboards seemed to be the answer.
- Comfort. For me, that largely means de-emphasizing the inner index columns.
- Better support for ambidextrous use of the trackpad or mouses (I use two). That is, it should be possible to do things like cut-copy-paste from either hand alone.

Typing speed and reducing the number of keys on the keyboard are not important goals to me.

## Layers

There are a total of 6 layers. The first is the main alpha layer.

The other layers are activated with a thumb key. All are hold-to-activate &ndash; that is, no toggles or one-shots &ndash; and most are hold-taps. Layer switching is done with custom code, so that a. shifted and custom keys can be emitted on the tap and b. so that the layer activates immediately for faster use of layer keys. See `layer_tap_toggle.c/h`.

The layers have OS-specific shortcuts in various places. The platform (macOS, Windows, Linux) can be selected at run-time. For more info, see `os_shortcuts.h/c` and `os_shortcut_defs.h`. macOS shortcuts are pretty stable, Windows and Linux still need work.

### ALPHA

![kyria-rsthd-prime-alpha](docs/images/kyria-rsthd-prime-alpha.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/69cf0f771159d920a34d882d696af6aa)

The alpha layout aims to reduce lateral finger movement on the index finger. It performs very well in an [analyzer](docs/prime-on-the-analyzer.md), with low SFU (same finger utilization) stats and low travel distance.

Some of the punctuation keys use non-standard shift mappings. See `shift_defs.h`.

There are a number of combos on this layer, defined with a bunch of macros to reduce boilerplate. I have a userspace implementation called "comboroll" to avoid timing issues with overlapping combos. See `combos.c` for the QMK version, `comborolls.c/h` for the userspace version, and `combo_defs.h` for combo definitions (works with either implementation).

### SYMS

Activated by the left thumb (hold).

![kyria-rsthd-prime-syms](docs/images/kyria-rsthd-prime-syms.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/0b079c6153a029c55cc8b5b7fbe701f2)

Unshifted, this layer contains most of the punctuation keys. I've arranged them so that many common (in programming) two-letter sequences can be typed with an inward roll. For example: `{% %} <% %> </ /> <? ?> => -> ~/`.

The ten digits are accessed with Shift, akin to [Programmer Dvorak](https://www.kaufmann.no/roland/dvorak/), but arranged in a 3x3 numpad-like grid. The most frequent `0 1 2` can also be accessed as a chord with no shift on the left hand.

### EDIT

Activated by the right thumb (hold).

![kyria-rsthd-prime-edit](docs/images/kyria-rsthd-prime-edit.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/24a80f5840733d6384fd21e20e1f28a0)

This layer extends the idea of platform-independent shortcuts to a complete layer. The navigation keys on the left have the standard cursor keys, home, end and page up/down.

Modifiers are on the right hand. If one of the standard modifiers (Ctrl, Alt, Gui) is held, the emitted code is just the normal modifier + keycode. The special modifiers on the home row act as follows:

- **Delete** makes the action delete instead of moving.
- **More** makes the key do "more" : left and right move a word left or right; home and end move to the start and end of a paragraph; up and down move a physical page up and down (mostly for Word); page up/down move to the start and end of the document.
- **X5** makes the action repeat 5 times on every keypress or repeat.
- **Fast** removes the initial repeat delay and repeats at a faster interval.

All actions have auto-repeat. You can change the special modifiers while holding down a navigation key and the action changes accordingly.

Select all, cut, copy and paste are chorded on the right hand top row, and keys to switch applications, windows and tabs are on the inner column.

### SNAP

Activated by the left thumb (hold).

![kyria-rsthd-prime-snap](docs/images/kyria-rsthd-prime-snap.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/6aa3ef0fcb5c886dc105a94b62690fe0)

So called because of the keys for window snapping, which snap to one of the screen halves or quadrants. The center key sets the window to the full vertical height. This works on macOS if [Rectangle](https://rectangleapp.com) is running; not really working on Windows and Linux yet.

Three mouse buttons are available on the right thumb.

Select all, cut, copy and paste are chorded on the left hand top row, and keys to switch applications, windows and tabs on the inner column.

### FUNC
Activated by pressing the SNAP layer key while holding Alt.

![kyria-rsthd-prime-func](docs/images/kyria-rsthd-prime-func.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/e09a2e00f963d27b25cdaf5962b9cb7f)

This layer contains function keys on the right hand, arranged roughly the same as the numpad. It also contains the keys that switch between macOS, Windows and Linux shortcuts.

### META
Activated by the right thumb (hold).

![kyria-rsthd-prime-meta](docs/images/kyria-rsthd-prime-meta.png)

[KLE link](http://www.keyboard-layout-editor.com/#/gists/c3f3f925be48f9c67de27b1e3b21ee37)

This layer contains common shortcut keys. They are mostly arranged according to the letter used in the Mac/Windows shortcut. For example, the S key invokes Save (Cmd-S on Mac, Ctrl-S on Windows). However, the mapping is not always that straightforward (e.g. Cmd-Q on Mac and Alt-F4 on Windows), hence the need for a dedicated layer.

## Other

### How to build

If you'd like to try the keymap out, here's one way:

```
cd /path/to/workingdir
git clone https://github.com/frogm0uth/keyboard-firmware.git
```

Assuming you already have QMK set up using the documented method:

```
cd ~qmk_firmware/keyboards/splitkb/kyria/keymaps
ln -s /path/to/workingdir/keyboard-firmware/kyria-rsthd-prime .
qmk compile -kb splitkb/kyria/rev1 -km kyria-rsthd-prime
```

(My Kyria is a rev1, if you have a rev2 then change the compile command above. I don't know if code changes are needed.)

### RSTHD variants and similar layouts
- [T-34](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/) (swaps E and space)
- [New layout for lateral movement haters](https://www.reddit.com/r/KeyboardLayouts/comments/mnumbs/new_layout_for_lateral_movement_haters/) (Some similarities to this layout)
- [RSTHD today](https://xsznix.wordpress.com/2021/01/13/rsthd-today/) (Latest layout generated by keygen with revised scoring and different corpus)
- [andrewjrae/kyria-keymap](https://github.com/andrewjrae/kyria-keymap) (Swaps E and Space)
- [johnm/keymap.c](https://gist.github.com/johnm/e3c129b20bbcae97601e547a7dd9fa0a) (Mirrors the complete alpha block, and some other tweaks)
- [minidox RSTHD](https://github.com/qmk/qmk_firmware/tree/master/keyboards/maple_computing/minidox/keymaps/rsthd_combos) (Port of RSTHD to the MiniDox keyboard)

### Relevant articles and resources

- [Pressing E with the thumb‽](https://precondition.github.io/pressing-e-with-the-thumb) (Nice survey article of layouts with letters on a thumb key)
- [keymapDB](https://keymapdb.com) (Searchable site with summaries of a lot of neat keymaps)

### Acknowledgments

Table of contents created by [gh-md-toc](https://github.com/ekalinin/github-markdown-toc). To update, run

```
/path/to/gh-md-toc --insert README.md
```

Much inspiration came from the residents of the [splitkb discord server](https://splitkb.com/discord).

Thanks to the author of [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) for the great layout.

[QMK](https://qmk.fm) rocks!

