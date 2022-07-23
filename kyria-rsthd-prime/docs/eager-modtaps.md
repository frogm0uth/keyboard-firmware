# Eager mod-taps

**THIS IS NOW IN THE [ATTIC](attic.md).**

This is a *thought experiment* and proof-of-concept implementation of a different mode of operation for mod-taps. I use the word "eager" to mean that mod-tap keys output their tap code as soon as possible. Activating the modifier requires a deliberate pause.

(This is the new version with graphical scenarios. For more detailed analysis with textual scenarios, see the [old version](eager-modtaps-long.md).) 

<!--ts-->
   * [Rationale/background](#rationalebackground)
   * [Operation](#operation)
      * [Waiting](#waiting)
      * [Deciding](#deciding)
      * [Tapping](#tapping)
      * [Holding](#holding)
      * [Discussion](#discussion)
   * [Key press-release scenarios](#key-press-release-scenarios)
   * [Proof-of-concept implementation](#proof-of-concept-implementation)
   * [Conclusion](#conclusion)
<!--te-->

## Rationale/background

I'm one of those unfortunates that can't use home-row mods. The timing throws me off and I accidentally trigger who-knows-what shortcuts. This is a fairly scary thing to happen, so I turned them off fairly quickly after trying them.

A recent discussion on the splitkb discord had me wondering about whether there might be a different timing of mod-taps that would enable me to use home-row mods. This note is the result.

## Operation

The keyboard is in one of four modes:

1. *Waiting*
2. *Deciding*
3. *Tapping*
4. *Holding*

There are two *terms* of interest: *tapping term*, which is by default 200 ms, and *combo term*, which is by default 50 ms. I'll use the abbreviation MT to mean "the time that is tapping term ms after the first mod-tap key press (or equivalently, the start of the *deciding* mode)", and similarly for CT.

Each mod-tap key has two codes: the tap code and the hold code (i.e. a modifier). To avoid ambiguous use of the word "hold", if an MT key has been pressed but it's not yet time to register either its tap code or hold code, it is "suspended".

### Waiting

While in this mode, nothing interesting is happening. From here, the keyboard can start tapping or deciding:

> 1. Stop *waiting* and start *deciding* when a mod-tap key is pressed.

> 2. Stop *waiting* and start *tapping* when a non-MT key is pressed.

### Deciding

A mod-tap key has been pressed, but we don't know yet whether to start tapping or holding. Suspend the first mod-tap key and subsequent mod-tap keys. There two ways to transition out of this mode:

> 3. Stop *deciding* and start *tapping* when:
>      - A non-MT key is pressed, or
>      - An MT key is pressed after CT, or
>      - An MT key is released.

> 4. Stop *deciding* and start *holding* when TT is reached.

### Tapping

Unsuspend any suspended mod-tap keys and register their *tap codes* in the order pressed. If we entered by releasing a mod-tap key, unregister its tap code. If we entered by pressing a non-MT key, then register it.

Process any subsequent keys as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys is a mod-tap, register/unregister its *tap code*.

> 5. Stop *tapping* and start *waiting* when tapping term has elapsed since the last key registration.

### Holding

Unsuspend any suspended mod-tap keys and register their *hold codes*.

Process any subsequent keys as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys is a mod-tap, register/unregister its *tap code* **unless** it's the release event of a held mod-tap key, in which case unregister its *hold code*.

> 6. Stop *holding* and start *waiting* when the last held MT key is released.

### Discussion

The resulting mod-tap behavior is very biased toward generating tap codes in preference to hold codes (modifiers). Registering modifiers requires a more deliberate action:

1. Wait a short time (tapping term) after pressing any key before pressing a mod-tap key
2. Wait a short time (tapping term) after pressing a mod-tap key before pressing another key

This will slow typing down when Shift is considered, but I'm thinking it would be no worse than say auto-shift. This idea of eager mod-taps could perhaps be thought of as adding modifiers to normal keys, rather than adding tap codes to modifier keys.

## Key press-release scenarios

The image below illustrates a number of key press-release scenarios. **A** and **N** are mod-tap keys, and **K** is a normal (non-MT) key. The light bars above the line indicate the period when a key is down and the darker bars below the line indicate when the key is registered and unregistered to the computer: red is a modifier, blue is the tap code of a mod-tap, green is a non-MT key.

![](images/eager-modtaps.png)

Here is a brief explanation of each scenario. For comparison to QMK, see the [old version](eager-modtaps-long.md#versus-qmk) of this note.

1. A mod-tap key is pressed and then released before TT. Start  *tapping* mode. The output is `a`.
2. A mod-tap key is pressed, then a non-MT key is pressed before TT. Start  *tapping* mode. The output is `ak`.
3. A mod-tap key is held until TT and no other keys are pressed. Start  *holding* and register the MT hold code. Then a non-MT key is pressed. The output is `K`.
4. Two MT keys are pressed before CT and held until TT, and no other keys are pressed. Start  *holding* and register both MT hold codes.  Then a normal key is pressed. The output is `Ctrl-K`.
5. Two MT keys are pressed before CT, then a non-MT key is pressed before TT. Start  *tapping* mode. The output is `ank`.
6.  Two MT keys are pressed before CT and the first is released before TT. Start  *tapping* mode. The output is `an`.
7.  Two MT keys are pressed before CT and the second is released before TT. Start  *tapping* mode. The output is `an`.
8. An MT key is pressed before CT and a second is pressed after CT but before TT. Start  *tapping* mode. The output is `an`.
9. A non-MT key is pressed. Start  *tapping* mode. An MT key is then pressed within a further tapping term. The output is `ka`. This is like ZMK's "global quicktap".

## Proof-of-concept implementation

I've implemented a userspace **proof-of-concept** in QMK. It seems to work with everything else, including (to my surprise) QMK combos. It does not work (unsurprisingly) with my userspace comborolls.

This is a "bolt-on" implementation, by which I mean that the mod-taps are not specified in the keymap but are intercepted in process_record_user().

- [`eager_modtap.c`](../eager_modtap.c) is the implementation.
- [`eager_modtap.h`](../eager_modtap.h) will need to be included in keymap.h.
- [`emt_defs.h`](../emt_defs.h) will need to be modified to define the bolt-on modifiers.

keymap.c will need to have two calls made to the eager mod-tap code. See my keymap.c for an example. Note that the keymap must use regular keycodes on the home row (e.g. `KC_N`). It will not work if it contains mod-tap keycodes (`SFT_T(KC_N)` etc).

## Conclusion

The lag on Shift is quite noticeable, which could be improved with:

- Disable rule 2. This removes the delay needed prior to pressing a mod-tap. DONE: disable by `#define EMT_DISABLE_RULE_2`.
- @precondition's next-sentence macro.
- Forced one-shot shift - shift is deactivated after the first key pressed (even if the mod is still held).
- Caps-word activated with both shift mod-taps.

For typing, this seems to works really well while testing things out. However, when I start to just type without thinking about mod-taps, I **still** have the problem of accidentally activating modifiers. At this point, I think I just have to accept that home-row mod-taps are not for me.
