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

PROJNAME=rtw

ELF=$(PROJNAME).elf

# What is our target
TARGET=$(PROJNAME).hex

# C compiler
C=avr-gcc

# C++ compiler
CPP=avr-g++

# Linker
LINKER=avr-gcc

# C++ compiler flags
CPPFLAGS=-c -Os -Wall -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR

# C compiler flags
CFLAGS=-c -Os -Wall -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR

# Linker flags
LFLAGS=-w -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p

# Scheduler object files
SCHEDOBJ=$(BUILD)/scheduler.o $(BUILD)/task.o $(BUILD)/timer.o $(BUILD)/factory.o

# Object files
OBJFILES=$(SCHEDOBJ) $(BUILD)/led_utils.o $(BUILD)/ledtask.o $(BUILD)/rxcmdtask.o $(BUILD)/taskfactory.o $(BUILD)/rtc_atmega328p.o $(BUILD)/serial_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/main.o

# Target
all: $(TARGET)

###############################################################################
#
# Scheduler files
#
###############################################################################
$(BUILD)/timer.o: $(SRC)/timer.cpp $(SRC)/timer.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/timer.o $(SRC)/timer.cpp

$(BUILD)/task.o: $(SRC)/task.cpp $(SRC)/task.h $(SRC)/timer.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/task.o $(SRC)/task.cpp

$(BUILD)/scheduler.o: $(SRC)/scheduler.cpp $(SRC)/scheduler.h $(SRC)/task.h $(SRC)/timer.h $(SRC)/error.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/scheduler.o $(SRC)/scheduler.cpp

$(BUILD)/factory.o: $(SRC)/factory.cpp $(SRC)/factory.h $(SRC)/scheduler.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/factory.o $(SRC)/factory.cpp

###############################################################################
#
# Project files
#
###############################################################################
$(BUILD)/led_utils.o: $(SRC)/led_utils.c $(SRC)/led_utils.h
	$(C) $(CFLAGS) -o $(BUILD)/led_utils.o $(SRC)/led_utils.c

$(BUILD)/ledtask.o: $(SRC)/ledtask.cpp $(SRC)/ledtask.h $(SRC)/led_utils.h $(SRC)/task.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/ledtask.o $(SRC)/ledtask.cpp

$(BUILD)/rxcmdtask.o: $(SRC)/rxcmdtask.cpp $(SRC)/rxcmdtask.h $(SRC)/task.h $(SRC)/rtc_atmega328p.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/rxcmdtask.o $(SRC)/rxcmdtask.cpp

$(BUILD)/taskfactory.o: $(SRC)/taskfactory.c $(SRC)/taskfactory.h $(SRC)/task.h $(SRC)/ledtask.h $(SRC)/rxcmdtask.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/taskfactory.o $(SRC)/taskfactory.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(C) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/serial_atmega328p.o: $(SRC)/serial_atmega328p.c $(SRC)/serial_atmega328p.h $(SRC)/led_utils.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serial_atmega328p.o $(SRC)/serial_atmega328p.c

$(BUILD)/main.o: $(SRC)/main.c
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/error.h $(SRC)/led_utils.h
	$(C) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

$(BUILD)/$(ELF): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) -lm

$(TARGET): $(BUILD)/$(ELF)
	avr-objcopy -O ihex -R .eeprom $(BUILD)/$(ELF) $(TARGET)

install: $(TARGET)
	../upload.sh $(TARGET)