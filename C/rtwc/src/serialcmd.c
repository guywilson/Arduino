#include <stdint.h>

#include "scheduler.h"
#include "serialcmd.h"
#include "rxtxmsgdef.h"
#include "led_utils.h"
#include "adctask.h"
#include "anonometer.h"
#include "rainguage.h"
#include "serial_atmega328p.h"
#include "utils.h"

char 		buffer[64];
int			length;

void respondAck()
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = 'O';
	buffer[3] = 'K';
	buffer[4] = MSG_FINISH;
	
	txstr(buffer, 5);
}

void buildWeatherResponse()
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[3] = RESPONSE_ACK;
	buffer[4] = MSG_FINISH;
	
	txstr(buffer, 4);
}

void respondADC(uint8_t * data, uint8_t length)
{
	uint8_t			channel = data[0] - 0x30;
	
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_ADC;
	buffer[3] = data[0];
	
	length = uint32ToString(&buffer[4], getADCAverage(channel));
	
	buffer[length + 4] = MSG_FINISH;
	
	length = length + 5;
	
	txstr(buffer, length);
}

void respondAvgRPS(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_AVG_WIND_SPEED;

	length = uint16ToString(&buffer[3], getAvgRPS());

	buffer[length + 3] = MSG_FINISH;
	
	txstr(buffer, length + 4);
}

void respondMaxRPS(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_MAX_WIND_SPEED;
	
	length = uint16ToString(&buffer[3], getMaxRPS());
	
	buffer[length + 3] = MSG_FINISH;
	
	length = length + 4;
	
	txstr(buffer, length);
}

void respondAvgWindSpeed(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_AVG_WIND_SPEED;
	
	length = doubleToString(&buffer[3], getAvgWindSpeed());
	
	buffer[length + 3] = MSG_FINISH;
	
	length = length + 4;
	
	txstr(buffer, length);
}

void respondMaxWindSpeed(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_MAX_WIND_SPEED;
	
	length = doubleToString(&buffer[3], getMaxWindSpeed());
	
	buffer[length + 3] = MSG_FINISH;
	
	length = length + 4;
	
	txstr(buffer, length);
}

void respondAvgRainfall(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_AVG_RAINFALL;
	
	length = doubleToString(&buffer[3], getAvgRainfall());
	
	buffer[length + 3] = MSG_FINISH;
	
	length = length + 4;
	
	txstr(buffer, length);
}

void respondMaxRainfall(void)
{
	buffer[0] = MSG_START;
	buffer[1] = MSG_PADDING;
	buffer[2] = RESPONSE_MAX_RAINFALL;
	
	length = doubleToString(&buffer[3], getMaxRainfall());
	
	buffer[length + 3] = MSG_FINISH;
	
	length = length + 4;
	
	txstr(buffer, length);
}

void RxCmdTask(PTASKPARM p)
{
	RX_CMD * cmd = (RX_CMD *)p;

	switch (cmd->command) {
		case COMMAND_PING:
			respondAck();
			break;
			
		case COMMAND_WEATHER:
			buildWeatherResponse();
			break;
			
		case COMMAND_LEDON:
			turnOn(LED_PORT0);
			respondAck();
			break;
			
		case COMMAND_LEDOFF:
			turnOff(LED_PORT0);
			respondAck();
			break;
			
		case COMMAND_ADC:
			respondADC(cmd->message, COMMAND_ADC_LENGTH);
			break;
			
		case COMMAND_AVG_WIND_SPEED:
			respondAvgWindSpeed();
//			respondAvgRPS();
			break;
			
		case COMMAND_MAX_WIND_SPEED:
			respondMaxWindSpeed();
//			respondMaxRPS();
			break;
			
		case COMMAND_AVG_RAINFALL:
			respondAvgRainfall();
			break;
			
		case COMMAND_MAX_RAINFALL:
			respondMaxRainfall();
			break;
	}
}
