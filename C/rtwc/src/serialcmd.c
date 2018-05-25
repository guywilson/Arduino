#include <stdint.h>
#include <string.h>

#include "scheduler.h"
#include "serialcmd.h"
#include "rxtxmsgdef.h"
#include "led_utils.h"
#include "adctask.h"
#include "anonometer.h"
#include "rainguage.h"
#include "serial_atmega328p.h"
#include "utils.h"

void respond(RXTX_CMD * pParms)
{
	static char		buffer[64];
	int				i;
	
	buffer[0] = MSG_START;
	buffer[1] = pParms->messageID & 0x00FF;
	buffer[2] = (pParms->messageID >> 8) & 0x00FF;
	buffer[3] = pParms->cmd_resp;
	buffer[4] = pParms->dataLength;
	
	i = 5;
	
	if (pParms->dataLength > 0) {
		buffer[i] = pParms->data[i];
		i++;
	}
	
	buffer[i] = MSG_FINISH;
	
	txstr(buffer, pParms->dataLength + 6);
}

void RxCmdTask(PTASKPARM p)
{
	RXTX_CMD * 		cmd = (RXTX_CMD *)p;
	ADCRESULT		adcResult;
	int				strLength;

	switch (cmd->cmd_resp) {
		case COMMAND_PING:
			cmd->cmd_resp = RESPONSE_ACK;
			cmd->dataLength = 0;
			
			respond(cmd);
			break;
			
		case COMMAND_WEATHER:
			cmd->cmd_resp = RESPONSE_WEATHER;
			cmd->dataLength = 0;
			
			respond(cmd);
			break;
			
		case COMMAND_LEDON:
			turnOn(LED_PORT0);
			
			cmd->cmd_resp = RESPONSE_ACK;
			cmd->dataLength = 0;
			
			respond(cmd);
			break;
			
		case COMMAND_LEDOFF:
			turnOff(LED_PORT0);
			
			cmd->cmd_resp = RESPONSE_ACK;
			cmd->dataLength = 0;
			
			respond(cmd);
			break;
			
		case COMMAND_ADC:
			cmd->cmd_resp = RESPONSE_ADC;
			cmd->dataLength = sizeof(ADCRESULT);
			
			adcResult.channel   = cmd->data[0];
			adcResult.result	= getADCAverage(adcResult.channel);
			
			memcpy(&cmd->data, &adcResult, cmd->dataLength);
			
			respond(cmd);
			break;
			
		case COMMAND_AVG_WIND_SPEED:
			strLength = doubleToString(cmd->data, getAvgWindSpeed());
			
			cmd->cmd_resp = RESPONSE_AVG_WIND_SPEED;
			cmd->dataLength = strLength;
			
			respond(cmd);
			break;
			
		case COMMAND_MAX_WIND_SPEED:
			strLength = doubleToString(cmd->data, getMaxWindSpeed());
			
			cmd->cmd_resp = RESPONSE_MAX_WIND_SPEED;
			cmd->dataLength = strLength;
			
			respond(cmd);
			break;
			
		case COMMAND_AVG_RAINFALL:
			strLength = doubleToString(cmd->data, getAvgRainfall());
			
			cmd->cmd_resp = RESPONSE_AVG_RAINFALL;
			cmd->dataLength = strLength;
			
			respond(cmd);
			break;
			
		case COMMAND_MAX_RAINFALL:
			strLength = doubleToString(cmd->data, getMaxRainfall());
			
			cmd->cmd_resp = RESPONSE_MAX_RAINFALL;
			cmd->dataLength = strLength;
			
			respond(cmd);
			break;
	}
}
