#include <avr/io.h>
#include <avr/interrupt.h>

#include "int_atmega328p.h"
#include "led_utils.h"

uint8_t		debouncedCount[NUM_INPUT_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};

/******************************************************************************
**
**	Debounced inputs (8):		PC0 - PC5 | PD6 - PD7
**
**	Counter request lines (3):	PD3 - PD5
**
**	Request counter interrupt:	PD2 (INT0)
**
**	Counter output (LSB - MSB):	PB0
**
******************************************************************************/
void setupDebouncePorts(void)
{
	/*
	** Debounce inputs...
	*/
	DDRC &= ~(0x7F);
	DDRD &= ~(0xC0);
	
	/*
	** Counter request lines...
	*/
	DDRD &= ~(0x38);
	
	/*
	** Counter output pin...
	*/
	DDRB |= 0x01;
}

void setupExternalInterrupts(void)
{
	/*
	** Set pin D2 (INT0) as an input...
	*/
	DDRD	&= ~_BV(DDD2);
	
	/*
	** Activate the pull-up resistor on pin D2...
	*/
	PORTD	|= _BV(PORTD2);
	
	/*
	** Trigger the interrupts on a rising edge...
	*/
	EICRA |= 0x0F;
	
	/*
	** Enable the INT0 interrupt...
	*/
	EIMSK |= 0x01;
}

uint8_t getRequestedCounter(void)
{
	uint8_t		requestedCounter = 0x00;
	
	requestedCounter = (PORTD & 0x38) >> 3;
	
	return requestedCounter;
}

uint8_t getDebounceInputValue(void)
{
	return (PORTC & 0x7F) | (PORTD & 0xC0);
}

void incrementDebouncedCount(uint8_t channel)
{
	debouncedCount[channel]++;
}

/*
** Respond to pulse from client AVR...
*/
ISR(INT0_vect, ISR_BLOCK)
{
	static uint8_t		bitNum = 0;
	static uint8_t		counterNum;
	static uint8_t		counterValue;
	
	if (bitNum == 0) {
		/*
		** Read the requested counter (0 - 7)...
		*/
		counterNum = getRequestedCounter();
		counterValue = debouncedCount[counterNum];
	}

	/*
	** Bit by bit transmission of the counter value...
	*/
	PORTB |= (counterValue >> bitNum) & 0x01;
	
	bitNum++;
	
	if (bitNum == 8) {
		bitNum = 0;
	}
}
