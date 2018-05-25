#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serialtx.h"
#include "serialport.h"
#include "serialstate.h"
#include "rxtxmsgdef.h"
#include "exception.h"

using namespace std;

void * tx_thread_func(void * arg)
{
	SerialState		*	pState;
	SerialPort		*	pPort;
	uint8_t				packetLength = 0;
	uint8_t				packet[64];
	bool				go = true;
	
	pState = (SerialState *)arg;
	
	pPort = pState->pSerialPort;
	
	try {
		while (go) {
			if (pState->hasTxItem()) {
				/*
				** Get the next msg off the queue and build the tx packet...
				*/
				PRXTXCMD pCmd = pState->pullTxItem();

				packet[0] = '<';
				packet[1] = (uint8_t)(pCmd->messageID & 0x00FF);
				packet[2] = (uint8_t)(pCmd->messageID & 0xFF00) >> 8;
				packet[3] = pCmd->cmd_resp;
				packet[4] = pCmd->dataLength;

				memcpy(&packet[5], pCmd->data, pCmd->dataLength);

				packet[pCmd->dataLength + 5] = '>';

				packetLength = pCmd->dataLength + 6;

				free(pCmd);

				pPort->tx(packet, packetLength);
			}

			/*
			** Sleep 10ms...
			*/
			usleep(10000L);
		}
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl;
	}
	
	return NULL;
}
