#ifndef _INCL_RXTXMSGDEF
#define _INCL_RXTXMSGDEF

/******************************************************************************
*
* Message format. Max total message length is 64 bytes
* 
* Offset (HEX)	Offset (DEC)	Length		Description
* ------------	------------	------		-----------------------------------
*   0x00		  0				  1			Start byte (0x3C) '<'
*   0x01		  1				  1			Padding, set to 0x24 (36) '$'
*	0x02		  2				  1			Command
*   0x03		  3				 60 (max)	Data - Length defined by command/response
*   0x3F		 63				  1			Finish byte (0x3E) '>'
*
******************************************************************************/
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

#define COMMAND_AVG_WIND_SPEED		0x34		// '4'
#define COMMAND_AVG_WIND_SPEED_LEN	0

#define COMMAND_MAX_WIND_SPEED		0x35		// '5'
#define COMMAND_MAX_WIND_SPEED_LEN	0


#define RESPONSE_ACK				0x41		// 'A'
#define RESPONSE_ACK_LENGTH			0

#define RESPONSE_WEATHER			0x57		// 'W'
#define RESPONSE_WEATHER_LENGTH		32			// ? Not defined yet

#define RESPONSE_ADC				0x43		// 'C'
#define RESPONSE_ADC_LENGTH			11			// 10-bit result + channel num 

#define RESPONSE_AVG_WIND_SPEED		0x44		// 'D'

#define MSG_START					0x3C		// '<'
#define MSG_FINISH					0x3E		// '>'
#define MSG_PADDING					0x24		// '$'

#define MAX_MESSAGE_LENGTH			 60
#define MAX_PACKET_LENGTH			MAX_MESSAGE_LENGTH + 4

#endif