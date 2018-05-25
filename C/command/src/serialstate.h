#include <pthread.h>

#include "serialport.h"
#include "stack.h"
#include "rxtxmsgdef.h"

#ifndef _INCL_SERIALSTATE
#define _INCL_SERIALSTATE

typedef struct
{
	uint16_t		messageID;
	uint8_t			cmd_resp;
	uint8_t			dataLength;
	uint8_t			data[MAX_DATA_LENGTH];
}
RXTXCMD;

typedef RXTXCMD	*	PRXTXCMD;


class SerialState
{
	private:
		uint16_t				currentMessageID;

		Queue				*	prxq;
		Queue				*	ptxq;
		
		pthread_mutex_t			rxqMutex;
		pthread_mutex_t			txqMutex;
		pthread_mutex_t			idMutex;
		
	public:
		SerialState();
		~SerialState();
		
		uint16_t	getCurrentMessageID();
		uint16_t	getNextMsgID();
		
		void		pushRxItem(PRXTXCMD cmd);
		void		pushTxItem(PRXTXCMD cmd);
		
		PRXTXCMD	pullRxItem();
		PRXTXCMD	pullTxItem();
		
		bool		hasRxItem();
		bool		hasTxItem();

		SerialPort			*	pSerialPort;
};

#endif