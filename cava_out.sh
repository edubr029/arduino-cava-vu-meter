#!/bin/bash

stty -F /dev/ttyUSB0 1000000 cs8 -cstopb -parenb
sleep 5
cava -p config > /dev/ttyUSB0
