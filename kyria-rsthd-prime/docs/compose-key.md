# Compose key - QMK notes

**THIS IS NOW IN THE [ATTIC](attic.md).**

A [Compose key](https://en.wikipedia.org/wiki/Compose_key) prefixes a sequence of keys that produce something completely different. This is a **preliminary** implementation in QMK.
<!--ts-->

   * [Compose key - QMK notes](#compose-key---qmk-notes)
      * [Description](#description)
      * [LIMITATIONS/TODO](#limitationstodo)
   * [Usage](#usage)
      * [How to add Compose Key to your keymap](#how-to-add-compose-key-to-your-keymap)
      * [OLED Support](#oled-support)
   * [Firmware size](#firmware-size)

<!--te-->

## Description

The Compose key initiates a keyboard mode in which no characters are output until one of a set of specified character sequences is typed. It's a "dead" key akin to the QMK Leader key, but this implementation is different in these ways:

1. There is no timeout. The Compose key sequence keeps waiting for you until you complete the sequence. Or, you can cancel by pressing the Compose key again.
2. The keys in the sequence can be in any layer. So you can use e.g. punctuation keys in different layers as part of the sequence.
3. There is no lag. That is, the key is output immediately the match is found. (While in practice this makes no real difference, the lag does prevent you from setting up Leader with a long delay to compensate for item 1.)
4. The sequence completes as soon as a match is found. You can't have both EG and EGG sequences, for example.
5. The sequence is defined as a tree. This is easier to define if you have a shallow, wide tree, whereas Leader tends to encourage completely arbitrary sequences. For example, with the Compose key I have sequences pc, pr, pt, pD, pd, pf. (The first character means "print" and the second indicates the specific symbol: copyright, registered, trademark, double dagger, dagger, and degrees.) With Leader, I have cp, reg, tm, ddag, dag, and deg.

   While either set of sequences could be used with either method, this is just how I've ended up doing it in each case. I suspect that the Compose key method works better for a large number of sequences as it naturally groups them into categories.

There are several ways of specifying the output produced when a sequence matches:

* Output a single keycode.
* Output an array of keycodes.
* Output a literal string ("This is a string").
* Execute a callback to output whatever you want.

The Compose key is more efficient than Leader in terms of firmware space if you have a lot of sequences. See the Firmware Size section below.

Finally, the OLED displays the sequence so far and the candidate next characters.

***This is a very preliminary implementation.***

## LIMITATIONS/TODO

The output codes in my Kyria implementation currently work for Mac only. If you use this code, presumably you will redefine the compose tree anyway.

The first three items in the following list of limitations are all tied together, and are a bit tricky to solve. It may be a while before I get to it. 

1. It doesn't work with custom keycodes.
2. The output codes used in compose_tree.c are for Mac only.
3. It doesn't work with Windows Alt key input method (because Alt needs to be held down while the following numbers are tapped).
4. Needs more work to make diacritics work better (Mac) or possible at all (Windows, this would require addressing the previous item + more).
5. I would like to come up with a "mod-tap" key that works with Compose. (Leader needs its own key, which is part of the reason I wrote this in the first place.)
6. (Maybe) Write a script to convert a human-readable set of strings into a compose tree.

# Usage

## How to add Compose Key to your keymap

Note: the following assumes that you have a keymap.h file which is included by keymap.c and contains the definition of the `custom_keycodes`  enum.

To add a Compose key to your keymap:

1. Drop the files compose_key.c, compose_key.h and compose_tree.c into your keymap folder. These can be obtained from my [Kyria keymap](../../../../keyboard-firmware/tree/master/kyria-rsthd-prime).

2. Include compose_key.h in your keymap.h:

   ```c
   #include "compose_key.h"
   ```

3. Add the following to your rules.mk:

   ```cmake
   COMPOSE_KEY = yes	# Enable the custom compose key feature
   ...
   ifeq ($(strip $(COMPOSE_KEY)), yes)
   	SRC += compose_key.c compose_tree.c
   	OPT_DEFS += -DCOMPOSE_KEY
   endif
   ```
   
6. Add the compose key to your `custom_keycode` enum:

   ```c
   #ifdef COMPOSE_KEY
     CU_COMPOSE,
   #endif
   ```
   
5. Add the above key to your keymap.

9. Add the following **before** the main switch in process_record_user():

   ```c
     // First check to see if we intercept for a compose sequence
   #ifdef COMPOSE_KEY
     if (compose_key_intercept(keycode, record)) {
       return false;
     }
   #endif
   ```

   This intercepts the normal processing sequence to capture keys in the compose sequence.

10. Add the following inside the main switch in process_record_user():

    ```c
       // Toggle compose mode on or off
     #ifdef COMPOSE_KEY
     case CU_COMPOSE:
       process_record_compose(keycode, record);
       break;
     #endif
    ```

    This turns the compose capture on and off.

9. Edit compose_tree.c to suit yourself. Hopefully my version is enough to demonstrate how to use the macros that define the tree. N.B. make **sure** that each node of the tree ends in COMPOSE_END.

## OLED Support

If you have an OLED, add this to config.h:

```c
#define COMPOSE_STATUS_ENABLE
```

Add this to your `oled_task_user` function: 

```c
...
#ifdef COMPOSE_STATUS_ENABLE
    compose_key_status();
#endif
...
```

Finally, add this to your `matrix_scan_user` function:

```c
 // Compose key status timer
#ifdef COMPOSE_STATUS_ENABLE
  compose_status_tick();
#endif
```


# Firmware size

With 22 sequences in a two-level tree, without OLED support enabled, and no callback nodes, Compose Key uses about 850 bytes. With OLED support turned on, it uses about 1250 bytes. Callbacks will use more space of course depending on how complex they are.

In comparison, Leader with 22 sequences uses 1800 bytes. A lot of the size usage is from the individual sequences, as Leader uses about 60 bytes per sequence. With only a few sequences, Leader will use less space. Compose Key uses only a few bytes for each node (with the exception of callback nodes), so is much more space-efficient with a large number of sequences.

