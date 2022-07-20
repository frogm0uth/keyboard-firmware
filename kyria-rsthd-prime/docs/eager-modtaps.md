# Eager mod-taps

**WORK IN PROGRESS**

This is a *thought experiment* on a different mode of operation for mod-taps. I use the word "eager" to mean that mod-tap keys output their tap code as soon as possible.


<!--ts-->
   * [Rationale/background](#rationalebackground)
   * [Basic operation](#basic-operation)
   * [Detailed rules](#detailed-rules)
   * [Scenarios (textual)](#scenarios-textual)
   * [Variants](#variants)
      * [Combo-like multiple mods](#combo-like-multiple-mods)
      * [One-shots](#one-shots)
      * ["Forced" one-shots](#forced-one-shots)
   * [Versus ZMK](#versus-zmk)
   * [Versus QMK](#versus-qmk)
   * [Scenarios (graphical)](#scenarios-graphical)
   * [Implementation and other thoughts](#implementation-and-other-thoughts)
<!--te-->

## Rationale/background

I'm one of those unfortunates that can't use home-row mods. The timing throws me off and I accidentally trigger who-knows-what shortcuts. This is a fairly scary thing to happen, so I turned them off fairly quickly after trying them. (Twice.)

However, I recently learnt in the splitkb discord about ZMK's "tap-preferred" flavor of mod-tap and the "global-quicktap" option. It turned out they weren't quite what I thought they were, so I decided to take a step back and think about what variant of these ideas might make home-row mods work for me.

As far as I know, the behavior described here is not currently available in either QMK or ZMK (the latter based only on reading the documentation).

## Basic operation

The keyboard is in one of three modes:

1. *Deciding*
2. *Tapping*
3. *Holding*

There are two *terms* of interest: *tapping term* (TT) which is by default 200 ms, and *combo term* (CT) which is by default 50 ms. For now, we use only TT; CT will be considered later.

Each mod-tap key has two codes: the tap code and the hold code (i.e. a modifier). To avoid ambiguous use of the word "hold", if an MT key has been pressed but it's not yet time to register either its tap code or hold code, it is "suspended".

Initially, the keyboard is *deciding* what to do. If a mod-tap key is pressed, it's suspended because we don't yet know which code to register. If the MT key is held down until TT elapses and no other keys are pressed, then *holding* mode starts and the hold code i.e. modifier is registered. Any subsequent key presses will therefore have that modifier active. The keyboard stays in *holding* mode until all mod-taps are released, when it switches back to *deciding*.

If, however, another key that is not a mod-tap is pressed before tapping term elapses, the keyboard shifts to *tapping* mode. The tap code of the MT is sent, as well as the new keycode. The keyboard stays in *tapping* mode until no keys are pressed for at least TT, when it switches back to *deciding*.

As a result, the mod-tap behavior is very oriented towards generating the tap codes in preference to hold codes (modifiers). So in normal typing, it should hopefully be very uncommon to accidentally register a modifier. That would requires a more deliberate action:

1. Wait a short time (TT) after pressing any key before pressing a mod-tap key
2. Wait a short time (TT) after pressing a mod-tap key before pressing another key

Granted, this might slow typing down when Shift is considered, but I'm thinking it would be no worse than say auto-shift.

## Detailed rules

The behavior in each state is as follows:

**deciding**

- No characters or modifiers are output to the computer. Pressed mod-tap keys will be suspended.

**tapping**

- When this state is entered, any suspended mod-tap keys are unsuspended and their *tap codes* are registered. Any keys pressed while in this mode are processed as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys is a mod-tap, its *tap code* is registered/unregistered.

**holding**

- When this state is entered, any suspended mod-tap keys are unsuspended and their *hold codes* are registered. Any keys pressed while in this mode are processed as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys is a mod-tap, its *tap code* is registered/unregistered **unless** it's a release event of a held mod-tap key, in which case its *hold code* is unregistered.

The rules to change modes are as follows. Starting from *deciding*:

1. Start *tapping* when:
    - A non-MT key is pressed, or
    - An MT key is released
2. Start *holding* when one or more MT keys are suspended and TT has elapsed since the first was pressed.

To go back to *deciding*, the rules are:

1. Stop *tapping* when TT has elapsed since the last key press or release. (Ideally, this rule would be to stop *tapping* when there are no keys currently pressed and TT has elapsed since the last key release. However I'm not sure if this can be implemented.)
2. Stop *holding* when the last held MT key is released.


## Scenarios (textual)

Below are a number of scenarios illustrating the behavior. See  [below](#scenarios-graphical) for a friendlier graphical version.

The notation is as follows: `A.` means the A key is pressed, `A^` means the A key is released, `||` means the end of tapping term, `(x.)` means `register_code(KC_X)`, `(x^) `means `unregister_code(KC_X)`. O is Shift mod-tap, N is Ctrl mod-tap, J is not a mod-tap. `->` indicates the characters that will be seen on screen.  

```
1.   O. O^ (o. o^)           ||                                                     -> o
2.   O.                      || (SFT.)       O^ (SFT^)                              -> 
3.   O. J. (o. j.)           ||              O^ (o^) J^ (j^)                        -> oj
4.   O. J. (o. j.) J^ (j^)   ||              O^ (o^)                                -> oj
5.   O. J. (o. j.) O^ (o^)   ||              J^ (j^)                                -> oj
6.   O.                      || (SFT.)       J. (j.) O^ (SFT^) J^ (j^)              -> J
7.   O.                      || (SFT.)       N. (n.) O^ (SFT^) N^ (n^)              -> N
8.   O. N.                   || (SFT. CTL.)  O^ (SFT^) N^ (CTL^)                    -> 
9.   O. N.                   || (SFT. CTL.)  J. (j.) O^ (SFT^) N^ (CTL^) J^ (j^)    -> Ctrl-J
10.  O. N. N^ (o. n. n^)     ||              O^ (o^)                                -> on
11.  O. N. O^ (o. n. o^)     ||              N^ (n^)                                -> on
12.  O. N. J. (o. n. j.)     ||              O^ (o^) N^ (n^) J^ (j^)                -> onj
13.  J. (j.) O. (o.)         ||              O^ (o^) J^ (j^)                        -> jo
13a. J. (j.) J^ (j^) O. (o.) ||              O^ (o^)                                -> jo
```

Notes:
1. Switch to *tapping* on release of MT key.
2. Switch to *holding* at TT. 
3. Non-MT key cause switch to *tapping*.
4. Same as (3).
5. Also same as (3).
6. Similarly to (2), already switched to *holding* at end of tapping term.
7. If *holding*, a different MT key is tapped.
8. Second MT key doesn't change mode, wait until TT to switch to *holding*.
9. Same as (8).
10. Releasing MT within TT switches to *tapping*
11. Same as (10).
12. Non-MT key switches to *tapping*.
13. This is ZMK "global quick tap".

## Variants

### Combo-like multiple mods

It might be desirable if activation of multiple modifiers occurs only if they are "pressed at the same time". Otherwise, typing OJ will produce output immediately, but typing ON will not produce output until one of them is released. This can be done if all mod-taps must be pressed within CT (instead of TT) to be able to switch to *holding*.

In this case, the rule to start *tapping* changes to:

1. Start *tapping* when:
    - A non-MT key is pressed, or
    - An MT key is released. or
    - An MT key is pressed and CT has elapsed.

Let `|` indicate expiration of CT, then (8) and (9) become two scenarios each:

```
8a. O. N. |               || (SFT. CTL.)  O^ (SFT^) N^ (CTL^)                    -> 
8b. O.    | N. (o. n.)    ||              O^ (o^) N^ (n^)                        -> on
9a. O. N. |               || (SFT. CTL.)  J. (j.) O^ (SFT^) N^ (CTL^) J^ (j^)    -> Ctrl-J
9b. O.    | N. (o. n.)    ||              J. (j.) O^ (o^) N^ (n^) J^ (j^)        -> onj
```
 

### One-shots

This could be changed a little so that modifiers act like one-shots. In that case, there would be additional scenarios like this:

```
14. O.                   || (SFT.)       O^ J. (j. SFT^) J^ (j^)                -> J
15. O. N.                || (SFT. CTL.)  O^  N^ J. (j. SFT^ CTL^) J^ (j^)       -> Ctrl-J
```

### "Forced" one-shots

I don't know if there's a name for this, but by "forced" I mean the modifier acts as a one-shot even if it's held down. This may help avoid errors like "THe". In that case, (6) and (7) would be:

```
6. O.                    || (SFT.)       J. (j. SFT^) O^ J^ (j^)               -> J
7. O.                    || (SFT.)       N. (n. SFT^) O^ N^ (n^)               -> N
```

Those have the same output as the earlier (6) and (7), so to emphasize the point:

```
16. O.                   || (SFT.)       J. (j. SFT^) K. (k.) J^ (j^) K^ (k^) O^ -> Jk
17. O.                   || (SFT.)       N. (n. SFT^) J. (j.) O^ N^ (n^) J^ (j^) -> Nj
``` 


## Versus ZMK

The [ZMK docs on hold-tap](https://zmk.dev/docs/behaviors/hold-tap) (see also [proposal PDF](https://github.com/zmkfirmware/zmk/files/5111053/zmk-modtap-proposal.pdf)) state that "The 'tap-preferred' flavor triggers the hold behavior when the `tapping-term-ms` has expired. *It triggers the tap behavior when another key is pressed.*" (My emphasis.) However, examining the tap-preferred diagrams that follow, here are those scenarios ("**z**N.x") using my notation:

```
z4.a O. J.                         || (SFT. j.)    J^ (j^) O^ (SFT^)                      -> J
z4.b O. J. J^                      || (SFT. j. j^) O^ (SFT^)                              -> J
z4.c O. J. J^ O^ (o. j. j^ o^)     ||                                                     -> oj
z4.d O. J. O^ (o. j. o^)           ||              J^ (j^)                                -> oj
```

Here are the equivalent scenarios for eager mod-taps:

```
3.   O. J. (o. j.)                 ||              J^ (j^) O^ (o^)                        -> oj
4.   O. J. (o. j.) J^ (j^)         ||              O^ (o^)                                -> oj
4a.  O. J. (o. j.) J^ (j^) O^ (o^) ||                                                     -> oj
5.   O. J. (o. j.) O^ (o^)         ||              J^ (j^)                                -> oj
```

As can be seen, ZMK will output the hold code (producing J) in cases where eager mod-taps will output the tap codes (oj). After doing the same exercise for QMK (next section), I realize now that the ZMK behavior is intended to mimic QMK.


## Versus QMK

In QMK, the nearest you can get to eager mod-taps is with IGNORE_MOD_TAP_INTERRUPTS defined and PERMISSIVE_HOLD **not** defined. Here are the scenarios for the key timings given earlier, with a few extras:

```
q1.   O. O^ (o. o^)               ||                                                       -> o
q2.   O.                          || (SFT.)         O^ (SFT^)                              -> 
q3.   O. J.                       || (SFT. j.)      O^ (SFT^) J^ (j^)                      -> J
q4.   O. J. J^                    || (SFT. j. j^)   O^ (SFT^)                              -> J
q4a.  O. J. J^ O^ (o. j. o^ j^)   ||                                                       -> oj
q5.   O. J. O^ (o. j. o^)         ||                J^ (j^)                                -> oj
q5a.  O. J. O^ (o. j. o^) J^ (j^) ||                                                       -> oj
q6.   O.                          || (SFT.)         J. (j.) O^ (SFT^) J^ (j^)              -> J
q7.   O.                          || (SFT.)         N. (n.) O^ (SFT^) N^ (n^)              -> N
q8.   O. N.                       || (SFT. CTL.)    O^ (SFT^) N^ (CTL^)                    -> 
q9.   O. N.                       || (SFT. CTL.)    J. (j.) O^ (SFT^) N^ (CTL^) J^ (j^)    -> Ctrl-J
q10.  O. N. N^                    || (SFT. n. n^)   O^ (SFT^)                              -> N
q10a. O. N. N^ O^ (o. o^ n. n^)   ||                                                       -> on
q11.  O. N. O^ (o. o^)            ||                N^                                     -> o
q11a. O. N. O^ (o. o^) N^ (n. n^) ||                                                       -> on
q12.  O. N. J.                    || (SFT. CTL. j.) O^ (SFT^) N^ (CTL^) J^ (j^)            -> Ctrl-J
```

For the sake of completeness, here are the new scenarios with eager mod-tap behavior:

```
4a.  O. J. (o. j.) J^ (j^) O^ (o^) ||                                                     -> oj
5a.  O. J. (o. j.) O^ (o^) J^ (j^) ||                                                     -> oj
10a. O. N. N^ (o. n. n^) O^ (o^)   ||                                                     -> on
11a. O. N. O^ (o. n. o^) N^ (n^)   ||                                                     -> on
```

In these cases, the output timing is a little different but the result is the same.

It's easy to see that QMK will register the hold codes in more cases than eager mod-taps (q3, q4, q10, q12). In order to register the tap codes while overlapping keypresses, the mod-tap key must be *released* before TT elapses. If the second key is a non-MT key, it makes no difference whether it is released before TT or not (q5, q5a). If it's an MT key, however, it's tap code is not output if it's not released before TT (q11).

This is the first time I've looked closely at QMK mod-taps to try and understand why HRMs don't work for me, and I think it's probably because whether to register the modifier is decided not just on the timing but also the **order** of key *releases*. For example, comparing q4 and q4a, the timing and ordering here is too tricky for me to get right consistently.

Considering that shortcuts (Cmd-, Ctrl-) have powerful and potentially disastrous actions, I would rather err on the side of accidentally typing some extra characters over accidentally invoking a shortcut.


## Scenarios (graphical)

The image below shows a number of scenarios in graphical form. These use the "combo-like" timing for multiple mod-taps. Note that the numbering is not the same as the textual scenarios given earlier.

The light bars above the line indicate key down. Brighter bars below the line indicate output: red is a modifier, blue is the tap code of a mod-tap, green is a non-MT key.

![](images/eager-tapmods.png)

1. Mod-tap key is released before TT: its tap code is output.
2. Non-MT key is pressed before TT: both keys have the tap code output.
3. MT key is held until TT: its hold code is output. 
4. A second MT key is pressed after CT but before TT: both tap codes are output.
5. Two MT keys are pressed before CT and both held until TT: both hold codes are output.
6.  Two MT keys are pressed before CT and one is released before TT: both tap codes are output.
7.  Two MT keys are pressed before CT and a non-MT key is pressed before TT: all tap codes are output.
8. A non-MT key is pressed and an MT key is then pressed within TT: both tap codes are output.

## Implementation and other thoughts

I'm wondering if I can implement this as a userspace proof-of-concept in QMK. If so, I'll see what it's like to use.

There will be no doubt be some interactions with combos. TBD. Initially, I will most likely have to disable them. 

This idea of eager mod-taps could be thought of as adding modifiers to normal keys, rather than adding tap codes to modifer keys (which is how I assume QMK mod-taps evolved).
