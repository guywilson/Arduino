#include <iostream>
#include <termios.h>
#include <pthread.h>
#include <unistd.h>

#include "exception.h"
#include "rxtxmsgdef.h"
#include "serialstate.h"
#include "cmdthread.h"

using namespace std;

void * cmd_wind_speed_thread(void * arg)
{
	SerialState *	pState;
	bool			go = true;
	PRXTXCMD		pAvgWindSpeedCmd;
	PRXTXCMD		pMaxWindSpeedCmd;

	pState = (SerialState *)arg;

	try {
		while (go) {
			pAvgWindSpeedCmd = (PRXTXCMD)malloc(sizeof(RXTXCMD));

			if (pAvgWindSpeedCmd == NULL) {
				throw new Exception(
							ERR_MALLOC, 
							"Error allocating memory.", 
							__FILE__, 
							"-", 
							"cmd_wind_speed_thread", 
							__LINE__);
			}

			pAvgWindSpeedCmd->messageID = pState->getNextMsgID();
			pAvgWindSpeedCmd->cmd_resp = COMMAND_AVG_WIND_SPEED;
			pAvgWindSpeedCmd->dataLength = 0;

			pState->pushTxItem(pAvgWindSpeedCmd);

			pMaxWindSpeedCmd = (PRXTXCMD)malloc(sizeof(RXTXCMD));

			if (pMaxWindSpeedCmd == NULL) {
				throw new Exception(
							ERR_MALLOC, 
							"Error allocating memory.", 
							__FILE__, 
							"-", 
							"cmd_wind_speed_thread", 
							__LINE__);
			}

			pMaxWindSpeedCmd->messageID = pState->getNextMsgID();
			pMaxWindSpeedCmd->cmd_resp = COMMAND_MAX_WIND_SPEED;
			pMaxWindSpeedCmd->dataLength = 0;

			pState->pushTxItem(pMaxWindSpeedCmd);

			sleep(60); // Sleep for 1 minute
		}
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl;
	}

	return nullptr;
}

void * cmd_rainfall_thread(void * arg)
{
	SerialState *	pState;
	bool			go = true;
	PRXTXCMD		pAvgRainfallCmd;
	PRXTXCMD		pMaxRainfallCmd;

	pState = (SerialState *)arg;

	try {
		while (go) {
			pAvgRainfallCmd = (PRXTXCMD)malloc(sizeof(RXTXCMD));

			if (pAvgRainfallCmd == NULL) {
				throw new Exception(
							ERR_MALLOC, 
							"Error allocating memory.", 
							__FILE__, 
							"-", 
							"cmd_rainfall_thread", 
							__LINE__);
			}

			pAvgRainfallCmd->messageID = pState->getNextMsgID();
			pAvgRainfallCmd->cmd_resp = COMMAND_AVG_RAINFALL;
			pAvgRainfallCmd->dataLength = 0;

			pState->pushTxItem(pAvgRainfallCmd);

			pMaxRainfallCmd = (PRXTXCMD)malloc(sizeof(RXTXCMD));

			if (pMaxRainfallCmd == NULL) {
				throw new Exception(
							ERR_MALLOC, 
							"Error allocating memory.", 
							__FILE__, 
							"-", 
							"cmd_rainfall_thread", 
							__LINE__);
			}

			pMaxRainfallCmd->messageID = pState->getNextMsgID();
			pMaxRainfallCmd->cmd_resp = COMMAND_MAX_RAINFALL;
			pMaxRainfallCmd->dataLength = 0;

			pState->pushTxItem(pMaxRainfallCmd);

			sleep(3600); // Sleep for 1 hour
		}
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl;
	}

	return nullptr;
}

void * cmd_adc_thread(void * arg)
{
	SerialState *	pState;
	bool			go = true;
	PRXTXCMD		pADCCmd;
	uint8_t			channel = 0;

	pState = (SerialState *)arg;

	try {
		while (go) {
			pADCCmd = (PRXTXCMD)malloc(sizeof(RXTXCMD));

			if (pADCCmd == NULL) {
				throw new Exception(
							ERR_MALLOC, 
							"Error allocating memory.", 
							__FILE__, 
							"-", 
							"cmd_adc_thread", 
							__LINE__);
			}

			pADCCmd->messageID = pState->getNextMsgID();
			pADCCmd->cmd_resp = COMMAND_AVG_RAINFALL;
			pADCCmd->dataLength = 1;
			pADCCmd->data[0] = channel++;

			pState->pushTxItem(pADCCmd);

			if (channel == 3) {
				channel = 0;
			}

			sleep(1); // Sleep for 1 second
		}
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl;
	}

	return nullptr;
}
