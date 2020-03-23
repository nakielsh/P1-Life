#!/bin/sh

# Clear out the outputs dir
rm output/*

../build/life -file lifes/gosper_gun.life -n 200 -out output -png-size 8