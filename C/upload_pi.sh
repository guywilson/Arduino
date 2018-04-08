#!/bin/bash

SERIALPORT=/dev/ttyUSB0
BAUDRATE=57600

avrdude -v -patmega328p -carduino -P$SERIALPORT -b$BAUDRATE -D -Uflash:w:$1:i
