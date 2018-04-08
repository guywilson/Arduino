###############################################################################
#                                                                             #
# MAKEFILE for led                                                            #
#                                                                             #
# Guy Wilson 2018                                                             #
#                                                                             #
###############################################################################

# Build output directory
BUILD=build

# Source directory
SRC=src

# What is our target
TARGET=led.hex

# C compiler
C=avr-g++

# Linker
LINKER=avr-gcc

# C compiler flags
CFLAGS=-c -Wall -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR

# Linker flags
LFLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p

# Object files
OBJFILES=$(BUILD)/led.o

# Target
all: $(TARGET)

$(BUILD)/led.o: $(SRC)/led.c
	$(C) $(CFLAGS) -o $(BUILD)/led.o $(SRC)/led.c

$(BUILD)/led.elf: $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/led.elf $(BUILD)/led.o -lm

$(TARGET): $(BUILD)/led.elf
	avr-objcopy -O ihex -R .eeprom $(BUILD)/led.elf $(TARGET)
	../upload.sh $(TARGET)