#!/bin/bash

DEVICE=$1
TARGET=$2
SERIALPORT=$3
BAUDRATE=115200

avrdude -C../avrdude.conf -v -p$DEVICE -carduino -P$SERIALPORT -b$BAUDRATE -D -Uflash:w:$TARGET:i
#avrdude -v -p$DEVICE -carduino -P$SERIALPORT -b$BAUDRATE -D -Uflash:w:$TARGET:i
