#ifndef _INCL_SERIALRX
#define _INCL_SERIALRX

#define STATE_START					0x01
#define STATE_MESSAGEID				0x02
#define STATE_RESPONSE				0x03
#define STATE_DATALENGTH			0x04
#define STATE_DATA					0x05
#define STATE_FINISH				0x06

void * rx_thread_func(void * arg);
void processResponse(byte response, byte * data, byte dataLength);

#endif