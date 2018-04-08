#include <stdint.h>

#ifndef _INCL_SERIAL_ATMEGA328P
#define _INCL_SERIAL_ATMEGA328P

/******************************************************************************
*
* Message format. Max total message length is 64 bytes
* 
* Offset		Length		Description
* ------		------		--------------------------------------------------
*   0x00		     1		Start byte (0x80)
*   0x01			 1		Padding, set to 0
*   0x03			 1		Message ID
*	0x04		     1		Command
*   0x05			 1		Message length (max 58 bytes)
*   0x06	    max 58		Data
*   0x3F		     1		Finish byte (0x81)
*
******************************************************************************/
#define STATE_START					0x01
#define STATE_PADDING				0x02
#define STATE_MSGID					0x03
#define STATE_DATALEN				0x04
#define STATE_DATA					0x05
#define STATE_COMMAND				0x06
#define STATE_FINISH				0x07

#define COMMAND_PING				0x32
#define COMMAND_WEATHER				0x20
#define COMMAND_LEDON				0x31		// '1'
#define COMMAND_LEDOFF				0x30		// '0'

#define RESPONSE_ACK				0x41		// 'A'
#define RESPONSE_ACK_LENGTH			6

#define RESPONSE_WEATHER			0x02

//#define MSG_START					0x80
//#define MSG_FINISH					0x81
//#define MSG_PADDING					0x00

#define MSG_START					0x3C		// '<'
#define MSG_FINISH					0x3E		// '>'
#define MSG_PADDING					0x3F		// '?'

#define RX_ERROR_OK					0x00
#define RX_ERROR_DATA_OVERRUN		0x01
#define RX_ERROR_DATALEN			0x02
#define RX_ERROR_PADDING			0x04

#define MAX_MESSAGE_LENGTH			 58

void setupSerial();

void processCommand(
			uint8_t		messageID, 
			uint8_t		command,
			uint8_t * 	message, 
			uint8_t 	dataLength, 
			uint8_t 	errorState);

uint8_t getNextTxByte();
uint8_t getTxMessageLength();

void debug(uint32_t count);

void handleRxInterrupt();
void handleTxInterrupt();

#endif