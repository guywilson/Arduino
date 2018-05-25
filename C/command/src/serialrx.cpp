#include <iostream>
#include <stdint.h>

#include "serialport.h"
#include "serialrx.h"
#include "exception.h"
#include "serialstate.h"
#include "rxtxmsgdef.h"

using namespace std;

void * rx_thread_func(void * arg)
{
	SerialState	*	pState;
	SerialPort	*	pPort;
	int				messageIDIndex = 0;
	int				dataIndex = 0;
	byte			b;
	int				state = STATE_START;
	bool			go = true;
	uint16_t		thisMessageID;
	byte			response;
	byte			dataLength;
	byte			data[58];
	
	pState = (SerialState *)arg;
	
	pPort = pState->pSerialPort;
	
	try {
		while (go) {
			b = pPort->rx();

			switch (state) {
				case STATE_START:
					if (b != '<') {
						throw new Exception(
									ERR_INVALID_RX_CHAR, 
									"Invalid start char.", 
									__FILE__, 
									"SerialPort", 
									"tx()", 
									__LINE__);
					}

					state = STATE_MESSAGEID;
					messageIDIndex = 0;
					break;

				case STATE_MESSAGEID:
					if (messageIDIndex == 0) {
						thisMessageID = (uint16_t)(b & 0x00FF);
						messageIDIndex++;
					}
					else {
						thisMessageID += ((uint16_t)(b << 8)) & 0xFF00;

						if (thisMessageID != pState->getCurrentMessageID()) {
							throw new Exception(
										ERR_INVALID_RX_CHAR, 
										"Invalid MessageID.", 
										__FILE__, 
										"SerialPort", 
										"tx()", 
										__LINE__);
						}

						state = STATE_RESPONSE;
					}
					break;

				case STATE_RESPONSE:
					response = b;
					state = STATE_DATALENGTH;
					break;

				case STATE_DATALENGTH:
					dataLength = b;
					dataIndex = 0;
					state = STATE_DATA;
					break;

				case STATE_DATA:
					data[dataIndex++] = b;

					if (dataIndex == dataLength) {
						state = STATE_FINISH;
					}
					break;

				case STATE_FINISH:
					if (b != '>') {
						throw new Exception(
									ERR_INVALID_RX_CHAR, 
									"Invalid end char.", 
									__FILE__, 
									"SerialPort", 
									"tx()", 
									__LINE__);
					}

					state = STATE_START;

					processResponse(response, data, dataLength);
					break;
			}
		}
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl;
	}
	
	return NULL;
}

void processResponse(byte response, byte * data, byte dataLength)
{
	switch (response) {
		case RESPONSE_ACK:
			break;
			
		case RESPONSE_ADC:
			break;
			
		case RESPONSE_AVG_WIND_SPEED:
			break;
			
		case RESPONSE_MAX_WIND_SPEED:
			break;
			
		case RESPONSE_AVG_RAINFALL:
			break;
			
		case RESPONSE_MAX_RAINFALL:
			break;
	}
}
