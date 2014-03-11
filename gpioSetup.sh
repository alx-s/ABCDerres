#!/bin/bash

#Input Pin
echo 9 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio9/direction

echo 10 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio10/direction

echo 11 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio11/direction

#Output pin
echo 2 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio2/direction

echo 3 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio3/direction

echo 4 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio4/direction

echo 7 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio7/direction

echo 8 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio8/direction

echo 14 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio14/direction

echo 15 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio15/direction

echo 17 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio17/direction

echo 18 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio18/direction

echo 22 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio22/direction

echo 23 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio23/direction

echo 24 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio24/direction

echo 25 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio25/direction

echo 27 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio27/direction

echo "setup done"
