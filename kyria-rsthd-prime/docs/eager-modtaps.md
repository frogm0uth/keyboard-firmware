# Eager mod-taps

**WORK IN PROGRESS**

This is a *thought experiment* on tapping early and holding later. (So it could also be called early tapping, late mod-taps, delayed mod-taps, lazy holds, ...) It sort of depends on which half of "mod-tap" you are applying the adjective to. Anyway, I use the word "eager" to mean that it outputs a tap code as soon as there's any indication that you don't want to hold.


<!--ts-->
   * [Rationale/background](#rationalebackground)
   * [Principles](#principles)
   * [Resulting behavior](#resulting-behavior)
   * [Scenarios (textual)](#scenarios-textual)
   * [Variants](#variants)
      * [Combo-like mod-taps](#combo-like-mod-taps)
      * [One-shots](#one-shots)
      * ["Forced" one-shots](#forced-one-shots)
   * [Scenarios (graphical)](#scenarios-graphical)
   * [Versus QMK](#versus-qmk)
   * [Versus ZMK](#versus-zmk)
   * [Implementation](#implementation)

<!-- Created by https://github.com/ekalinin/github-markdown-toc -->
<!-- Added by: username, at: Wed 20 Jul 2022 06:13:25 AEST -->

<!--te-->

## Rationale/background

I'm one of those unfortunates that can't use home-row mods. The timing throws me off and I instantly make errors. However, I recently learnt in the splitkb discord about ZMK's "tap-preferred" flavor of mod-tap and the "global-quicktap" option. It turned out they weren't quite what I thought they were, so I decided to take a step back and think about what variant of these ideas might make home-row mods work for me.

As far as I know, this behavior is not currently available in either QMK or ZMK (the latter based only on reading the documentation).

## Principles
The keyboard is always in one of three modes:
1. *Deciding*
2. *Tapping*
3. *Holding*

There are two *terms* of interest: *tapping term* (TT) which is by default 200 ms, and *combo term* (CT) which is by default 50 ms. For now, we use only TT, CT will be considered later.

Each mod-tap key has two codes: the tap code and the hold code (i.e. a modifier). To avoid ambiguous use of the word "hold", if an MT key has been pressed but it's not yet time to register either its tap code or hold code, it is "suspended".

Initially, the keyboard is *deciding* what to do. If a mod-tap key is pressed, it's suspended because we don't yet know which code to register. If the MT key is held down and no other keys are pressed, then *holding* starts when tapping term elapses. Any subsequent key presses will have that modifier active.

If, however, another key that is not a mod-tap is pressed before tapping term elapses, the keyboard shifts to *tapping*. The tap code of the MT key is sent, as well as the new key. Any other keys after that including mod-taps are just tapped.

Once the keyboard starts *holding* or *tapping*, it stays there until things are "quiet," when it goes back to the *deciding* state. Exact details are in the next section.

## Detailed rules
The behavior in each state is as follows:

**deciding**

- No characters or modifiers are output to the computer. Pressed mod-tap keys will be suspended.

**tapping**

- When entered, any suspended mod-tap keys are unsuspended and their *tap codes* are registered. Subsequent keys are then processed as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys are mod-taps, its *tap code* is registered/unregistered.

**holding**

- When entered, any suspended mod-tap keys are unsuspended and their *hold codes* are registered. Any subsequent keys are then processed as normal &ndash; key presses cause a register event, key releases cause an unregister event. If any of these keys are mod-taps, its *tap code* is registered/unregistered unless it's a release event of a held mod-tap key, in which case its *hold code* is unregistered.

The rules to change modes are as follows. The mode only changes between *deciding* and *tapping* or *deciding* and *holding*, never directly from *tapping* to *holding* or vice versa. Starting from *deciding*:

1. Start *tapping* when:
    - A non-MT key is pressed, or
    - An MT key is released; or
2. Start *holding* when one or more MT keys are suspended and TT has elapsed since the first was pressed.

To go back to *deciding*, the rules are:

1. Stop *tapping* when TT has elapsed since the last key press or release. (Ideally, this rule would be to stop *tapping* when there are no keys currently pressed and TT has elapsed since the last key release. However this probably can't be implemented.)
2. Stop *holding* when the last held MT key is released.


## Resulting behavior

The result of the above is that the mod-tap behavior is very oriented towards generating the tap codes. So in normal typing, even I wouldn't accidentally register modifiers. To do so is a more deliberate action that requires:

1. Waiting a short time after pressing any key before pressing a mod-tap key
2. Waiting a short time after pressing a mod-tap key or keys before pressing another key

The "short time" here is of course the tapping term, or 200 ms &ndash; more a slight pause than a wait. For some people, this might slow things down for regular typing (using shift), but I'm thinking probably not any more than say auto-shift.

## Scenarios (textual)

Below are a number of scenarios illustrating the behavior. See further below for a graphical version.

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


## Scenarios (graphical)

The image below shows a number of scenarios that should result from following *Principles* above. I'm assuming now that the "combo-like" multiple mod-taps are implemented.

![](images/eager-tapmods.png)

1. Mod-tap key is released before TT: its tap code is output.
2. Non-MT key is pressed before TT: both keys have the tap code output.
3. MT key is held until TT: its hold code is output. 
4. A second MT key is pressed after CT but before TT: both tap codes are output.
5. Two MT keys are pressed before CT and both held until TT: both hold codes are output.
6.  Two MT keys are pressed before CT and one is released before TT: both tap codes are output.
7.  Two MT keys are pressed before CT and a non-MT key is pressed before TT: all tap codes are output.
8. A non-MT key is pressed and an MT key is then pressed within TT: both tap codes are output.

## Versus QMK

In QMK, the nearest you can get to eager mod-taps is with IGNORE_MOD_TAP_INTERRUPTS defined and PERMISSIVE_HOLD **not** defined. Here are the scenarios for the key timing given earlier, with a few extras:

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

In general, it's easy to see that QMK will register the hold codes in more cases than eager mod-taps. But there are a number of inconsistencies. Why would q4 and q5 produce a different result? Same for q10 and q11.  In fact, q11 seems like it must be a bug. 

This is the first time I've looked closely at QMK mod-taps to try and understand why HRMs don't work for me, but I think mostly it's the fact that whether to choose the modifier is decided not just on the timing but also the **order** of key *releases*. For example, comparing q4 and q4a, I think the timing and ordering here is too tricky to get right consistently.

Considering that shortcuts (Cmd-, Ctrl-) have powerful and potentially disastrous actions, I think it would be better to err on the side of accidentally typing some extra characters over accidentally invoking a shortcut. QMK mod-taps were originally modifiers with tap codes added on; eager mod-taps is more the other way around: tap codes with modifiers added on.

## Versus ZMK

The [ZMK docs on hold-tap](https://zmk.dev/docs/behaviors/hold-tap) (see also [proposal PDF](https://github.com/zmkfirmware/zmk/files/5111053/zmk-modtap-proposal.pdf)) state that "The 'tap-preferred' flavor triggers the hold behavior when the `tapping-term-ms` has expired. *It triggers the tap behavior when another key is pressed.*" (My emphasis.) However, examining the tap-preferred diagrams that follow, here are those scenarios ("**z**N.x") using my notation, followed by the scenario with the same key press/release/timing for eager mod-taps:

```
z4.a O. J.                         || (SFT. j.)    J^ (j^) O^ (SFT^)                      -> J
3a.  O. J. (o. j.)                 ||              J^ (j^) O^ (o^)                        -> oj
z4.b O. J. J^                      || (SFT. j. j^) O^ (SFT^)                              -> J
4.   O. J. (o. j.) J^ (j^)         ||              O^ (o^)                                -> oj
z4.c O. J. J^ O^ (o. j. j^ o^)     ||                                                     -> oj
4.   O. J. (o. j.) J^ (j^) O^ (o^) ||                                                     -> oj
z4.d O. J. O^ (o. j. o^)           ||              J^ (j^)                                -> oj
5.   O. J. (o. j.) O^ (o^)         ||              J^ (j^)                                -> oj
```

As can be seen, eager mod-taps prefers taps more than ZMK tap-preferred, as it will output the tap codes (oj) in cases where ZMK will output the hold code (producing J). I was initially mystified by this behavior considering the "tap-preferred" designation, until I analyzed QMK (previous section). It's the same.

## Implementation
I'm wondering if I can implement this as a userspace proof-of-concept in QMK. If so, I'll see what it's like to use...
