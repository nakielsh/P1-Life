#!/bin/sh

# Clear out the outputs dir
rm output/*

../build/life_ovk -file lifes/pulsar.life -n 3 -out output -png-overkill shaders/glossy.ovk