#include <pthread.h>
#include <stdint.h>

#include "serialstate.h"
#include "exception.h"
#include "stack.h"

SerialState::SerialState()
{
	prxq = new Queue();
	ptxq = new Queue();
	
	rxqMutex 	= PTHREAD_MUTEX_INITIALIZER;
	txqMutex 	= PTHREAD_MUTEX_INITIALIZER;
	idMutex		= PTHREAD_MUTEX_INITIALIZER;
	
	currentMessageID = 0;
}

SerialState::~SerialState()
{
	delete prxq;
	delete ptxq;
}

uint16_t SerialState::getCurrentMessageID()
{
	return currentMessageID;
}

uint16_t SerialState::getNextMsgID()
{
	pthread_mutex_lock(&idMutex);

	currentMessageID++;
	
	pthread_mutex_unlock(&idMutex);
	
	return currentMessageID;
}

void SerialState::pushRxItem(PRXTXCMD cmd)
{
	pthread_mutex_lock(&rxqMutex);
	
	prxq->addItem(cmd);
	
	pthread_mutex_unlock(&rxqMutex);
}

void SerialState::pushTxItem(PRXTXCMD cmd)
{
	pthread_mutex_lock(&txqMutex);
	
	ptxq->addItem(cmd);
	
	pthread_mutex_unlock(&txqMutex);
}

PRXTXCMD SerialState::pullRxItem()
{
	PRXTXCMD		cmd;
	
	pthread_mutex_lock(&rxqMutex);
	
	cmd = (PRXTXCMD)prxq->getItem();
	
	pthread_mutex_unlock(&rxqMutex);
	
	return cmd;
}

PRXTXCMD SerialState::pullTxItem()
{
	PRXTXCMD		cmd;
	
	pthread_mutex_lock(&txqMutex);
	
	cmd = (PRXTXCMD)ptxq->getItem();
	
	pthread_mutex_unlock(&txqMutex);
	
	return cmd;
}

bool SerialState::hasRxItem()
{
	bool		hasItem;
	
	pthread_mutex_lock(&rxqMutex);
	
	hasItem = prxq->getItemCount() > 0 ? true : false;
	
	pthread_mutex_unlock(&rxqMutex);

	return hasItem;
}

bool SerialState::hasTxItem()
{
	bool		hasItem;
	
	pthread_mutex_lock(&txqMutex);
	
	hasItem = ptxq->getItemCount() > 0 ? true : false;
	
	pthread_mutex_unlock(&txqMutex);

	return hasItem;
}
