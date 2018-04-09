#include <stdint.h>

#ifndef _INCL_SERIAL_ATMEGA328P
#define _INCL_SERIAL_ATMEGA328P

/******************************************************************************
*
* Message format. Max total message length is 64 bytes
* 
* Offset (HEX)	Offset (DEC)	Length		Description
* ------------	------------	------		-----------------------------------
*   0x00		  0				  1			Start byte (0x3C) '<'
*   0x01		  1				  1			Padding, set to 0x20 (32) - space
*	0x02		  2				  1			Command
*   0x03		  3				 60 (max)	Data - Length defined by command/response
*   0x3F		 63				  1			Finish byte (0x3E) '>'
*
******************************************************************************/
#define STATE_START					0x01
#define STATE_PADDING				0x02
#define STATE_COMMAND				0x03
#define STATE_DATA					0x04
#define STATE_FINISH				0x05


#define COMMAND_PING				0x32		// '2'
#define COMMAND_PING_LENGTH			0

#define COMMAND_WEATHER				0x20
#define COMMAND_WEATHER_LENGTH		0

#define COMMAND_LEDON				0x31		// '1'
#define COMMAND_LEDON_LENGTH		0

#define COMMAND_LEDOFF				0x30		// '0'
#define COMMAND_LEDOFF_LENGTH		0

#define COMMAND_ADC					0x33		// '3'
#define COMMAND_ADC_LENGTH			1


#define RESPONSE_ACK				0x41		// 'A'
#define RESPONSE_ACK_LENGTH			0

#define RESPONSE_WEATHER			0x57		// 'W'
#define RESPONSE_WEATHER_LENGTH		32			// ? Not defined yet

#define RESPONSE_ADC				0x43		// 'C'
#define RESPONSE_ADC_LENGTH			11			// 10-bit result + channel num 


#define MSG_START					0x3C		// '<'
#define MSG_FINISH					0x3E		// '>'
#define MSG_PADDING					0x20		// ' '


#define RX_ERROR_OK					0x00
#define RX_ERROR_DATA_OVERRUN		0x01
#define RX_ERROR_DATALEN			0x02
#define RX_ERROR_PADDING			0x04

#define MAX_MESSAGE_LENGTH			 60

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