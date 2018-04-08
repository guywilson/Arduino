###############################################################################
#                                                                             #
# MAKEFILE for sched_blink                                                    #
#                                                                             #
# Guy Wilson 2018                                                             #
#                                                                             #
###############################################################################

# Build output directory
BUILD=build

# Source directory
SRC=src

PROJNAME=rtwc

ELF=$(PROJNAME).elf

# What is our target
TARGET=$(PROJNAME).hex

# C compiler
C=avr-gcc

# Linker
LINKER=avr-gcc

# C compiler flags
#CFLAGS=-c -Os -Wall -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR
CFLAGS=-c -Os -Wall -w -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR

# Linker flags
LFLAGS=-w -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p

# Scheduler object files
SCHEDOBJ=$(BUILD)/scheduler.o

# Object files
OBJFILES=$(SCHEDOBJ) $(BUILD)/led_utils.o $(BUILD)/ledtask.o $(BUILD)/rxcmdtask.o $(BUILD)/rtc_atmega328p.o $(BUILD)/serial_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/main.o

# Target
all: $(TARGET)

###############################################################################
#
# Scheduler files
#
###############################################################################
$(BUILD)/scheduler.o: $(SRC)/scheduler.c $(SRC)/scheduler.h $(SRC)/error.h
	$(C) $(CFLAGS) -o $(BUILD)/scheduler.o $(SRC)/scheduler.c

###############################################################################
#
# Project files
#
###############################################################################
$(BUILD)/led_utils.o: $(SRC)/led_utils.c $(SRC)/led_utils.h
	$(C) $(CFLAGS) -o $(BUILD)/led_utils.o $(SRC)/led_utils.c

$(BUILD)/ledtask.o: $(SRC)/ledtask.c $(SRC)/ledtask.h $(SRC)/led_utils.h $(SRC)/scheduler.h
	$(C) $(CFLAGS) -o $(BUILD)/ledtask.o $(SRC)/ledtask.c

$(BUILD)/rxcmdtask.o: $(SRC)/rxcmdtask.c $(SRC)/rxcmdtask.h $(SRC)/led_utils.h $(SRC)/scheduler.h
	$(C) $(CFLAGS) -o $(BUILD)/rxcmdtask.o $(SRC)/rxcmdtask.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(C) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/serial_atmega328p.o: $(SRC)/serial_atmega328p.c $(SRC)/serial_atmega328p.h $(SRC)/scheduler.h
	$(C) $(CFLAGS) -o $(BUILD)/serial_atmega328p.o $(SRC)/serial_atmega328p.c

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/scheduler.h $(SRC)/ledtask.h $(SRC)/rxcmdtask.h $(SRC)/taskdef.h
	$(C) $(CFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/error.h $(SRC)/led_utils.h
	$(C) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

$(BUILD)/$(ELF): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) -lm

$(TARGET): $(BUILD)/$(ELF)
	avr-objcopy -O ihex -R .eeprom $(BUILD)/$(ELF) $(TARGET)

install: $(TARGET)
	../upload.sh $(TARGET)