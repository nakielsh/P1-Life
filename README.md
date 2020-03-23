![Game of Life logo](images/logo.svg "Game of Life")

This repository contains our implementation of the first JIMP2 project - John Conway's Game of Life in C.

## Let's start with a pretty animation designed to lure you in

![A Game of Life pulsar](images/pulsar.gif)

Isn't the above image pretty? The GIF was created using some random website, but the PNGs used to create that GIF came from our **Wonderful Piece of Software**.

## Running the Game of Life

Getting GoL up and running is easy! Here's all you will need:

* A C compiler, GCC recommended
* `libpng`
* Patience
* A bottle of purified water
* Scissors
* Red string, anywhere between 1m - 5m
* A frying pan

### Build instructions

Assuming you have GCC and libpng set up, all you need to do is `make` and we're done! The compiler will spit out the `life` executable in the `build` folder. Neat!

#### Building with Overkill - an advanced guide

If you're running Linux x64, then you can just run `./build_all.sh` and both the non-Overkill and Overkill versions of GoL will compile.

If you end up in an unfortunate situation of not running Linux x64, **DON'T PANIC!** Here's what you need to do:

1. Clone yourself a copy of [the Overkill repo](https://github.com/JIMP-HNKS/Overkill)
2. Run make in the `clibrary` folder of the Overkill repo
3. Grab the `liboverkill.a` from  `clibrary/lib` and put it in the `overkill` folder here in the GoL repo.
4. Profit! Now it should compile as planned™

### I built the thing - now what?

Start with the Examples™ in the `examples` folder! The ones with `ovk_` will require you to build GoL with Overkill.
If you want to try it yourself without the helping hand of the provided Examples™, just run `life` or `life_ovk` and you will get a help doc in return. ***NeAt!***

## Overkill this, Overkill that - what is Overkill

Overkill is a little shader language we made for this wonderful project.

Overkill shaders use a simple stack machine to do their job. The shader language is based on assembly language, how cute.

```
// A night vision-style shader

// Interlace pattern
pushv global_coords_y
pushc 100
mul
int
pushc 2
mod
pushc 0.3
mul

// Cells
pushv cell_state
pushc 0.6
mul
add

// Out!
setv out_pixel_green
setv0 out_pixel_red
setv0 out_pixel_blue
```

check out overkill => [overkill](https://github.com/JIMP-HNKS/Overkill) <=

## Authors
* [Hubert Nakielski](https://github.com/nakielsh)
* [Kacper Seredyn](https://github.com/scintilla4evr)

![Game of Life gliders](images/gliders.gif)

All animations in this readme have been generated using GoL with Overkill. The exported PNGs were then forcefully shoved into a third-party GIF generator.
