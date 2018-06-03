###############################################################################
#                                                                             #
# MAKEFILE for dbcounter - An input counter with debounce                     #
#                                                                             #
# Guy Wilson (c) 2018                                                         #
#                                                                             #
###############################################################################

PROJNAME=dbcounter

# Target device
DEVICE=atmega328p
BOARD=ARDUINO_AVR_NANO
ARCHITECTURE=ARDUINO_ARCH_AVR
CLOCK_FREQ=16000000L

# What is our target
ELF=$(PROJNAME).elf
TARGET=$(PROJNAME).hex

# Build output directory
BUILD=build

# Source directory
SRC=src

# Port we use to upload the tearget to the device
UPLOADPORT=/dev/cu.usbmodem1411

# C compiler
CC=avr-gcc

# Linker
LINKER=avr-gcc

# Hex file creator
OBJCOPY=avr-objcopy

# Assembly dump tool
OBJDUMP=avr-objdump

# Size tool
SIZETOOL=avr-size

# Upload tool
UPLOADTOOL=../upload.sh

# C compiler flags
CFLAGS=-c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=$(DEVICE) -DF_CPU=$(CLOCK_FREQ) -DARDUINO=10804 -D$(BOARD) -D$(ARCHITECTURE)

# Linker flags
LFLAGS=-fuse-linker-plugin -Wl,--gc-sections -mmcu=$(DEVICE)

# Hex file creator flags
OBJCOPYFLAGS=-O ihex -R .eeprom

#Obj dump flags
OBJDUMPFLAGS=-I $(SRC) -f -s -l -S

# Size tool flags
SFLAGS=-C --mcu=$(DEVICE)

# Scheduler object files
SCHEDOBJ=$(BUILD)/scheduler.o

# Object files
OBJFILES=$(SCHEDOBJ) $(BUILD)/led_utils.o $(BUILD)/heartbeat.o $(BUILD)/dbtask.o $(BUILD)/rtc_atmega328p.o $(BUILD)/int_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/main.o

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

$(BUILD)/heartbeat.o: $(SRC)/heartbeat.c $(SRC)/heartbeat.h $(SRC)/led_utils.h $(SRC)/scheduler.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/heartbeat.o $(SRC)/heartbeat.c

$(BUILD)/dbtask.o: $(SRC)/dbtask.c $(SRC)/dbtask.h $(SRC)/scheduler.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/dbtask.o $(SRC)/dbtask.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/int_atmega328p.o: $(SRC)/int_atmega328p.c $(SRC)/int_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/int_atmega328p.o $(SRC)/int_atmega328p.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/error.h $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/scheduler.h $(SRC)/heartbeat.h $(SRC)/dbtask.h $(SRC)/taskdef.h $(SRC)/led_utils.h $(SRC)/rtc_atmega328p.h $(SRC)/int_atmega328p.h $(SRC)/error.h
	$(CC) $(CFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

###############################################################################
#
# Link it all together into an ELF format file
#
###############################################################################
$(BUILD)/$(ELF): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) -lm
	$(OBJDUMP) $(OBJDUMPFLAGS) $(BUILD)/$(ELF) > $(PROJNAME).s

###############################################################################
#
# Create the target
#
###############################################################################
$(TARGET): $(BUILD)/$(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD)/$(ELF) $(TARGET)
	$(SIZETOOL) $(SFLAGS) $(BUILD)/$(ELF)

###############################################################################
#
# Upload to the device, use 'make install' to envoke
#
###############################################################################
install: $(TARGET)
	$(UPLOADTOOL) $(DEVICE) $(TARGET) $(UPLOADPORT)
	
clean: 
	rm $(BUILD)/*
	rm $(PROJNAME).s
	rm $(TARGET)
