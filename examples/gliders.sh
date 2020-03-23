#!/bin/sh

# Clear out the outputs dir
rm output/*

../build/life -file lifes/gliders.life -n 10 -out output