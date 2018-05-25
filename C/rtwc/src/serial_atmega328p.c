#ifndef BAUD
#define BAUD		57600
#endif

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "scheduler.h"
#include "taskdef.h"
#include "rxtxmsgdef.h"
#include "serial_atmega328p.h"

uint8_t			txBuffer[64];
uint8_t			txLength = 0;

RXTX_CMD 		rxtxCmd;

void setupSerial()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	/*
	** Set data byte size to 8-bit, 1 stop bit
	*/
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00) | _BV(USBS0);
	
	/*
	** Enable Rx & Tx
	** Enable Rx & Tx interrupts
	*/
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);
}

void enableTxInterrupt()
{
	/*
	** Enable the data register empty interrupt...
	*/
	UCSR0B |= _BV(UDRIE0);
}

void disableTxInterrupt()
{
	/*
	** Mask the data register empty interrupt...
	*/
	UCSR0B &= ~_BV(UDRIE0);
}

uint8_t getNextTxByte(uint8_t isInit)
{
	static uint8_t		i = 0;
	uint8_t				rtn;
	
	if (isInit) {
		i = 0;
	}
	
	if (i < txLength) {
		rtn = txBuffer[i];
		i++;
	}
	else {
		rtn = 0;
		disableTxInterrupt();
	}
	
	return rtn;
}

void txstr(char * pszData, uint8_t dataLength)
{
	int			i;
	
	if (dataLength > 64) {
		dataLength = 64;
	}
	
	for (i = 0;i < dataLength;i++) {
		txBuffer[i] = pszData[i];
	}
	
	txLength = dataLength;
	
	UDR0 = getNextTxByte(1);
	
	enableTxInterrupt();
}

/*
** Rx Complete Interrupt Handler
*/
ISR(USART_RX_vect, ISR_BLOCK)
{
	static uint8_t		state = STATE_START;
	static uint8_t		idData[2];
	static uint8_t		idIndex = 0;
	static uint8_t		dataIndex = 0;
	
	uint8_t	b = UDR0;
	
	switch (state) {
		case STATE_START:
			if (b == MSG_START) {
				state = STATE_MESSAGEID;
				idIndex = 0;
			}
			break;
		
		case STATE_MESSAGEID:
			idData[idIndex++] = b;
			
			if (idIndex == 2) {
				memcpy(&rxtxCmd.messageID, &idData[0], 2);
				state = STATE_COMMAND;
			}
			break;
		
		case STATE_COMMAND:
			rxtxCmd.cmd_resp = b;
			state = STATE_DATALENGTH;
			break;

		case STATE_DATALENGTH:
			rxtxCmd.dataLength = b;
			
			if (rxtxCmd.dataLength > 0) {
				state = STATE_DATA;
				dataIndex = 0;
			}
			else {
				state = STATE_FINISH;
			}
			break;
			
		case STATE_DATA:
			rxtxCmd.data[dataIndex++] = b;
			
			if (dataIndex == rxtxCmd.dataLength) {
				state = STATE_FINISH;
			}
			break;
		
		case STATE_FINISH:
			if (b == MSG_FINISH) {
				state = STATE_START;
			}
			else {
				rxtxCmd.errorState = RX_ERROR_DATA_OVERRUN;
			}
			
			scheduleTask(TASK_RXCMD, 1, &rxtxCmd);
			break;
	}
}

/*
** Tx Complete (Data Register Empty) Interrupt Handler
*/
ISR(USART_UDRE_vect, ISR_BLOCK)
{
	uint8_t		b;
	
	b = getNextTxByte(0);
	
	if (b != 0) {
		UDR0 = b;
	}
}
