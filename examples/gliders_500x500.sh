#!/bin/sh

# Clear out the outputs dir
rm output/*

../build/life -file lifes/gliders500.life -n 20 -out output -png-size 1 -wrap