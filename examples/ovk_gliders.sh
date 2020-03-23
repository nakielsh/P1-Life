#!/bin/sh

# Clear out the outputs dir
rm output/*

../build/life_ovk -file lifes/gliders.life -n 10 -out output -png-overkill shaders/nightvision.ovk -png-size 16