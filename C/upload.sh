#!/bin/bash

TARGET=$1
SERIALPORT=$2
BAUDRATE=57600

avrdude -v -patmega328p -carduino -P$SERIALPORT -b$BAUDRATE -D -Uflash:w:$TARGET:i