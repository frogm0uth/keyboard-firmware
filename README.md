# frogmouth keyboard firmware

This is the firmware for my keyboards.

## Key layout

The layout I use is an idiosyncratic modification of RSTHD. While the documentation is now out of date with respect to the code, the general idea is described more in the [Kyria readme](./kyria-rsthd-prime/README.md).

With that said, I think there is too much emphasis on the alpha key layout in the various forums and discord servers. The larger part of the battle is the layers, modifiers and thumb keys!

## Custom features

While I use QMK, I've also added a fair of custom code to make things work exactly the way I want it to. In some cases, since I spent a couple of years trying to squeeze the firmware into a Pro Micro, this also saved "a lot" of firmware space.

Arguably, QMK now includes some of the things I've added. Still, you may find some things of interest here, in the [common code directory](./common/).

## Keyboards

I started with a Kyria, which is a brilliant design, and almost perfect (for a flat board). More recently I've started using some other boards for various reasons. The Kyria directory still has most of the documentation. Each board has its own key layout and layers, although they are all very similar.

- [Kyria v1 and v3](./kyria-rsthd-prime/)
- [Cherry Corne](./cherry-corne/)

Coming soon&trade;:

- Dactyl manuform custom 4x6
