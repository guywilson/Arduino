###############################################################################
#                                                                             #
# MAKEFILE for weather station command                                        #
#                                                                             #
# Guy Wilson 2018                                                             #
#                                                                             #
###############################################################################

# Source directory
SOURCE=src

# Build output directory
BUILD=build

# What is our target
TARGET=wsc

# C compiler
CPP=g++

# Linker
LINKER=g++

# CPP compiler flags (Release)
CPPFLAGS=-c -Wall -fpermissive -pthread -std=c++11

# Object files 
OBJFILES=$(BUILD)/main.o $(BUILD)/serialport.o $(BUILD)/serialstate.o $(BUILD)/serialrx.o $(BUILD)/serialtx.o $(BUILD)/cmdthread.o $(BUILD)/exception.o $(BUILD)/stack.o

# Target
all: $(TARGET)

# Compile CPP source files
#
$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/exception.h $(SOURCE)/serialtx.h $(SOURCE)/serialrx.h $(SOURCE)/serialport.h $(SOURCE)/serialstate.h $(SOURCE)/cmdthread.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(BUILD)/stack.o: $(SOURCE)/stack.cpp $(SOURCE)/stack.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/stack.o $(SOURCE)/stack.cpp

$(BUILD)/serialport.o: $(SOURCE)/serialport.cpp $(SOURCE)/serialport.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serialport.o $(SOURCE)/serialport.cpp

$(BUILD)/serialstate.o: $(SOURCE)/serialstate.cpp $(SOURCE)/serialstate.h $(SOURCE)/serialport.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serialstate.o $(SOURCE)/serialstate.cpp

$(BUILD)/serialrx.o: $(SOURCE)/serialrx.cpp $(SOURCE)/serialrx.h $(SOURCE)/serialport.h $(SOURCE)/exception.h $(SOURCE)/stack.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serialrx.o $(SOURCE)/serialrx.cpp

$(BUILD)/serialtx.o: $(SOURCE)/serialtx.cpp $(SOURCE)/serialtx.h $(SOURCE)/serialport.h $(SOURCE)/exception.h $(SOURCE)/stack.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serialtx.o $(SOURCE)/serialtx.cpp

$(BUILD)/cmdthread.o: $(SOURCE)/cmdthread.cpp $(SOURCE)/cmdthread.h $(SOURCE)/rxtxmsgdef.h $(SOURCE)/serialstate.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/cmdthread.o $(SOURCE)/cmdthread.cpp
	
$(TARGET): $(OBJFILES)
	$(LINKER) -lstdc++ -pthread -o $(TARGET) $(OBJFILES)
