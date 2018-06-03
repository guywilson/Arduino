#include <avr/io.h>

#include "readcounter.h"

void setupCounterRead(void)
{
	/*
	** Port D outputs
	** bit 4		= interrupt request line
	** bits 5 - 7 	= counter channel select
	*/
	DDRD |= 0xF0;
	
	/*
	** Port D input bit 3 = counter bitstream read...
	*/
	DDRD &= ~(0x08);
}

void setCounterChannel(uint8_t channel)
{
	PORTD &= ~(0xE0);
	PORTD |= (channel << 5) & 0xE0;
}

void toggleCounterInterruptLine(uint8_t state)
{
	if (state) {
		PORTD |= 0x10;
	}
	else {
		PORTD &= ~(0x10);
	}
}

uint8_t getNextCounterBit(void)
{
	uint8_t		bit;
	
	bit = (PORTD & 0x08) >> 3;
	
	return (bit & 0x01);
}
