###############################################################################
#                                                                             #
# MAKEFILE for rtwc - A weather station with a real-time scheduler            #
#                                                                             #
# Guy Wilson (c) 2018                                                         #
#                                                                             #
###############################################################################

PROJNAME=rtwc

# Target device
DEVICE=atmega328p

# What is our target
ELF=$(PROJNAME).elf
TARGET=$(PROJNAME).hex

# Build output directory
BUILD=build

# Source directory
SRC=src

# Port we use to upload the tearget to the device
UPLOADPORT=/dev/cu.wchusbserial1420

# C compiler
CC=avr-gcc

# Linker
LINKER=avr-gcc

# Hex file creator
ELFTOHEX=avr-objcopy

# Size tool
SIZETOOL=avr-size

# Upload tool
UPLOADTOOL=../upload.sh

# C compiler flags
CFLAGS=-c -Os -Wall -w -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=$(DEVICE) -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR

# Linker flags
LFLAGS=-w -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(DEVICE)

# Hex file creator flags
HFLAGS=-O ihex -R .eeprom

# Size tool flags
SFLAGS=-C --mcu=$(DEVICE)

# Scheduler object files
SCHEDOBJ=$(BUILD)/scheduler.o

# Object files
OBJFILES=$(SCHEDOBJ) $(BUILD)/led_utils.o $(BUILD)/ledtask.o $(BUILD)/rxcmdtask.o $(BUILD)/adctask.o $(BUILD)/rtc_atmega328p.o $(BUILD)/serial_atmega328p.o $(BUILD)/adc_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/main.o

# Target
all: $(TARGET)

###############################################################################
#
# Scheduler files
#
###############################################################################
$(BUILD)/scheduler.o: $(SRC)/scheduler.c $(SRC)/scheduler.h $(SRC)/error.h
	$(CC) $(CFLAGS) -o $(BUILD)/scheduler.o $(SRC)/scheduler.c

###############################################################################
#
# Project files
#
###############################################################################
$(BUILD)/led_utils.o: $(SRC)/led_utils.c $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/led_utils.o $(SRC)/led_utils.c

$(BUILD)/ledtask.o: $(SRC)/ledtask.c $(SRC)/ledtask.h $(SRC)/led_utils.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/ledtask.o $(SRC)/ledtask.c

$(BUILD)/rxcmdtask.o: $(SRC)/rxcmdtask.c $(SRC)/rxcmdtask.h $(SRC)/led_utils.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/rxcmdtask.o $(SRC)/rxcmdtask.c

$(BUILD)/adctask.o: $(SRC)/adctask.c $(SRC)/adctask.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/adctask.o $(SRC)/adctask.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/adc_atmega328p.o: $(SRC)/adc_atmega328p.c $(SRC)/adc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/adc_atmega328p.o $(SRC)/adc_atmega328p.c

$(BUILD)/serial_atmega328p.o: $(SRC)/serial_atmega328p.c $(SRC)/serial_atmega328p.h $(SRC)/rxtxmsgdef.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/serial_atmega328p.o $(SRC)/serial_atmega328p.c

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/scheduler.h $(SRC)/ledtask.h $(SRC)/rxcmdtask.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/error.h $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

###############################################################################
#
# Link it all together into an ELF format file
#
###############################################################################
$(BUILD)/$(ELF): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) -lm

###############################################################################
#
# Create the target
#
###############################################################################
$(TARGET): $(BUILD)/$(ELF)
	$(ELFTOHEX) $(HFLAGS) $(BUILD)/$(ELF) $(TARGET)
	$(SIZETOOL) $(SFLAGS) $(BUILD)/$(ELF)

###############################################################################
#
# Upload to the device, use 'make install' to envoke
#
###############################################################################
install: $(TARGET)
	$(UPLOADTOOL) $(TARGET) $(UPLOADPORT)