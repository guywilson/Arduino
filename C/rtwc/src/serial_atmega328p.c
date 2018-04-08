#ifndef BAUD
#define BAUD		38400
#endif

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "scheduler.h"
#include "taskdef.h"
#include "serial_atmega328p.h"
#include "rxcmdtask.h"

#include "led_utils.h"

volatile uint8_t			txBuffer[64];
volatile uint8_t			txLength = 0;

volatile uint8_t			currentMessageID = 0;

void setupSerial()
{
    //stop interrupts
    cli();

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
    
    // enable interrupts
    sei();
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
	static uint8_t		index = 0;
	uint8_t				rtn;
	
	if (isInit) {
		index = 0;
	}
	
	if (index < txLength) {
		rtn = txBuffer[index++];
	}
	else {
		rtn = 0;
		disableTxInterrupt();
	}
	
	return rtn;
}

uint8_t getTxMessageLength()
{
	return txLength;
}

void respondAck(uint8_t messageID)
{
	txBuffer[0] = MSG_START;
	txBuffer[1] = MSG_PADDING;
//	txBuffer[2] = messageID;
	txBuffer[2] = RESPONSE_ACK;
//	txBuffer[4] = 0;
	txBuffer[3] = MSG_FINISH;
	
	txLength = 4;
	
	// Start transmission by setting tx register...
	UDR0 = getNextTxByte(1);
	
	enableTxInterrupt();
}

void buildWeatherResponse(uint8_t messageID)
{
	txBuffer[0] = MSG_START;
	txBuffer[1] = MSG_PADDING;
	txBuffer[2] = messageID;
	txBuffer[3] = RESPONSE_ACK;
	txBuffer[4] = 0;
	txBuffer[5] = MSG_FINISH;
	
	txLength = RESPONSE_ACK_LENGTH;
	
	// Start transmission by setting tx register...
	UDR0 = getNextTxByte(1);
}

void debug(uint32_t count)
{
	char		out[16];
	int			i;
	uint32_t	j = 10;
	int			k = 0;
	
	txBuffer[0] = MSG_START;
	
	for (i = 10;i > 0;i--) {
		txBuffer[i] = count % j;
		count = count / j;
		
		j = j * 10;
	}
	
	txBuffer[11] = MSG_FINISH;
	
	UDR0 = getNextTxByte(1);
}

void handleRxInterrupt()
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
				//state = STATE_MSGID;
				state = STATE_COMMAND;
			}
			else {
				errorState = RX_ERROR_PADDING;
			}
			break;

		/*
		** Skip this step for now whilst we're
		** getting the handler routine working...
		*/
		case STATE_MSGID:
			currentMessageID = b;
			state = STATE_COMMAND;
			break;
		
		case STATE_COMMAND:
			command = b;
			
			state = STATE_FINISH;
			break;
		
		/*
		** Skip the next two steps for now whilst we're
		** getting the handler routine working...
		*/
		case STATE_DATALEN:
			if (b <= MAX_MESSAGE_LENGTH) {
				dataLength = b;

				if (dataLength == 0) {
					state = STATE_FINISH;
				}
				else {
					state = STATE_DATA;
				}
			}
			else {
				errorState = RX_ERROR_DATALEN;
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
			
			rxParms.messageID	= currentMessageID;
			rxParms.command 	= command;
			rxParms.message		= message;
			rxParms.dataLength	= dataLength;
			rxParms.errorState	= errorState;

			scheduleTask(TASK_RXCMD, 10, &rxParms);
			break;
	}
}

void handleTxInterrupt()
{
	uint8_t		b;
	
	b = getNextTxByte(0);
	
	if (b != 0) {
		UDR0 = b;
	}
}

void processCommand(
		uint8_t		messageID,
		uint8_t		command,
		uint8_t * 	message, 
		uint8_t 	dataLength, 
		uint8_t 	errorState)
{
	switch (command) {
		case COMMAND_PING:
			respondAck(messageID);
			break;
			
		case COMMAND_WEATHER:
			buildWeatherResponse(messageID);
			break;
			
		case COMMAND_LEDON:
			turnOn(LED_PORT0);
			respondAck(messageID);
			break;
			
		case COMMAND_LEDOFF:
			turnOff(LED_PORT0);
			respondAck(messageID);
			break;
	}
}

/*
** Rx Complete Interrupt Handler
*/
ISR(USART_RX_vect, ISR_BLOCK)
{
	handleRxInterrupt();
}

/*
** Tx Complete (Data Register Empty) Interrupt Handler
*/
ISR(USART_UDRE_vect, ISR_BLOCK)
{
	handleTxInterrupt();
}
