# Kyria Build Notes

The Kyria is a great kit. Here are some things I thought worth writing down.

## v1 vs v3

The most obvious difference between v1 and v3 is that the latter has per-key RGB. This turned out to be less interesting than I expected, as I wasn't able to find interesting keycaps with shine-through legends. (By "interesting", I mean non-QWERTY.)

If only keyboardio made their [Model 100 Linear A keycaps](https://shop.keyboard.io/products/linear-a-keycaps-m100) in a version with standard MX size. (Yes they do have an XDA set, but they aren't shinethrough.)

However, there are a lot of other differences.

### v1 has that v3 doesn't

- Breakout pins for all rows and columns
- 8 columns in the key matrix (vs 7)
- 2U thumb keys as an option
- More backlight LEDs (10 vs 6)
- Flippable PCB
- Break-off outer pinky column 

### v3 has that v1 doesn't

- Per-key RGB
- Hot-swap sockets (option when buying, there are MX hotswap, Choc hotswap, and MX/Choc solder versions of the board)
- More encoder locations

## Case hardware

If you order a case using the Composer, you will have the [Aurora Low Profile Case Hardware Kit](https://splitkb.com/collections/keyboard-parts/products/aurora-low-profile-case-hardware-kit) added to your order. This feels kinda wasteful as it has the parts for any keyboard in the Aurora series, so you get a lot of parts that you don't actually need. Also, the standoffs for the OLED covers are not long enough if you socket the controllers.

This is what you actually need for a Kyria with acrylic base, FR4 plate, and MX switches:

- 10 x M2 8mm standoffs. These need to be fairly thin, about 3mm diameter.
- 4 x M2 18mm standoffs (\*). Diameter doesn't matter.
- 28 x M2 5mm screws.

(\*) this is what I measured as necessary with an OLED installed with the sockets and headers I use on the controller. YMMV.

I priced out an order on ebay: the parts for 1 keyboard worked out at about EUR8 shipped from China, about the same as from splitkb. On the plus side, you also get usable standoffs for the OLED covers and you won't have to use pan-head screws. On the down side, shipping takes a month.

For 5 keyboards it works out at about EUR12, so only really an advantage if building two or more.

## Soldering LEDs

The first time I soldered SMD LEDs, I really stuffed up one side (it was a Corne). I've since learned how to do it properly, so I can now build a Kyria with 100% success rate first time.

Here's the secret: flux.

Just get a little tub of rosin flux paste and a small brush to apply it. To clean it off, use 100% IPA and a small paintbrush cropped short (so the bristles are stiff). Then rinse with enough IPA to remove the dissolved flux residues off the board.

Even though solder has flux in it, using rosin flux paste makes the solder wet onto the parts much more quickly.

1. Place the LED on the board. 
2. Paint a little flux on the pad and terminal.
3. Put a small amount of solder on the iron tip. Use tweezers to hold the LED in place and touch the iron tip to the pad. The flux boils immediately. Move the tip to touch the terminal of the LED and remove the iron.
4. Do a few more LEDs this way. I typically do groups of six.
5. Paint flux on the other three pads/terminals of all LEDs.
6. Touch the iron to a pad, touch the solder to it and touch the terminal with the iron.
7. Solder the same pin on the other LEDs. Move to the next pin for all LEDs, then the last pin.

Note: set the iron to a reasonable temperature. I use 300. Any lower and the iron won't transfer heat quickly enough, which means you hold the iron on the part longer and are more likely to overheat it! If done right, you only touch the iron on the part for a second or two.

Note 2: don't use "no-clean" flux, they are designed for manufacturing with controlled temperatures and processes. Unless properly "activated", they are corrosive to the board! And they make rework/repair harder. For hand-soldering, use rosin flux and clean the board (both sides) with IPA.

## Tilt

Some keycap profiles are designed assuming the keyboard is tilted forwards. MT3 is an example, which needs 6 degrees of forward tilt for the home row to be horizontal.

You can do this with bumpons. Get some largish round ones, some largish flat ones, and some small round ones. Stack the large round ones on the large flat ones and stick them onto the base - I have one stack under the (QWERTY) H key and one under the O key. Then, right near the front of the keyboard, place two small bumpons. You will need to fiddle around a bit with the location of the last one to make sure all four bumpons sit evenly on the desk.
