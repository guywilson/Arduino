#include <stdint.h>

#ifndef _INCL_SERIAL_ATMEGA328P
#define _INCL_SERIAL_ATMEGA328P

#define STATE_START					0x01
#define STATE_PADDING				0x02
#define STATE_COMMAND				0x03
#define STATE_DATA					0x04
#define STATE_FINISH				0x05

#define RX_ERROR_OK					0x00
#define RX_ERROR_DATA_OVERRUN		0x01
#define RX_ERROR_DATALEN			0x02
#define RX_ERROR_PADDING			0x04

void setupSerial();

void processCommand(
			uint8_t		command,
			uint8_t * 	message, 
			uint8_t 	errorState);

uint8_t getNextTxByte(uint8_t isInit);
uint8_t getTxMessageLength();

void debug(uint32_t count);

void handleRxInterrupt();
void handleTxInterrupt();

#endif