#ifndef BAUD
#define BAUD		57600
#endif

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "scheduler.h"
#include "taskdef.h"
#include "rxtxmsgdef.h"
#include "serial_atmega328p.h"

uint8_t			txBuffer[64];
uint8_t			txLength = 0;

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
	static uint8_t 		message[MAX_MESSAGE_LENGTH];
	static uint8_t		state = STATE_START;
	static uint8_t		messageIndex = 0;
	static uint8_t		dataLength = 0;
	static uint8_t		errorState = RX_ERROR_OK;
	static uint8_t		command = 0;
	static RX_CMD 		rxParms;
	
	uint8_t	b = UDR0;
	
	switch (state) {
		case STATE_START:
			if (b == MSG_START) {
				state = STATE_PADDING;
			}
			break;
		
		case STATE_PADDING:
			if (b == MSG_PADDING) {
				state = STATE_COMMAND;
			}
			else {
				errorState = RX_ERROR_PADDING;
			}
			break;
		
		case STATE_COMMAND:
			command = b;
			
			/*
			** Set data length explicitly if appropriate for the
			** command, default is 0 data length...
			*/
			switch (command) {
				case COMMAND_WEATHER:
					dataLength = COMMAND_WEATHER_LENGTH;
					state = STATE_DATA;
					break;
			
				case COMMAND_ADC:
					dataLength = COMMAND_ADC_LENGTH;
					state = STATE_DATA;
					break;
					
				default:
					dataLength = 0;
					state = STATE_FINISH;
					break;
			}
			break;
		
		case STATE_DATA:
			message[messageIndex++] = b;
			
			if (messageIndex == dataLength) {
				state = STATE_FINISH;
				messageIndex = 0;
			}
			break;
		
		case STATE_FINISH:
			if (b == MSG_FINISH) {
				state = STATE_START;
			}
			else {
				errorState = RX_ERROR_DATA_OVERRUN;
			}
			
			rxParms.command 	= command;
			rxParms.message		= message;
			rxParms.errorState	= errorState;

			scheduleTask(TASK_RXCMD, 1, &rxParms);
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
