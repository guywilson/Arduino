#include <stddef.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"
#include "spi_atmega328p.h"

#define NUM_CHANNELS		2

#define REQ_LOW_BYTE		0x10
#define REQ_HIGH_BYTE		0x20

#define DDR_SPI				DDRB
#define DD_MOSI				DDB3
#define DD_MISO				DDB4
#define DD_SCK				DDB5

uint16_t	debouncedCount[NUM_INPUT_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};

void setupSPI()
{
	/*
	** Set MISO as output, all others as input...
	*/
	DDR_SPI = _BV(DD_MISO);
	
	/*
	** Enable the SPI, configure as Slave...
	*/
	SPCR |= _BV(SPE);
}

void setupDebouncePorts(void)
{
	/*
	** Debounce inputs...
	*/
	DDRC &= ~(0x7F);
	DDRD &= ~(0xC0);
}

uint8_t getDebounceInputValue(void)
{
	return (PORTC & 0x7F) | (PORTD & 0xC0);
}

void incrementDebouncedCount(uint8_t channel)
{
	debouncedCount[channel]++;
}

void SpiTask(PTASKPARM p)
{
	uint8_t			channel;
	uint8_t			lo_hi;
	uint8_t			b;
	static uint16_t	count;
	
	if (SPSR & _BV(SPIF)) {
		b = SPDR;
		
		lo_hi = b & 0xF0;
		channel = b & 0x0F;
		
		if (lo_hi == REQ_LOW_BYTE) {
			count = debouncedCount[channel];
			
			SPDR = (uint8_t)(count & 0x00FF);
		}
		else {
			SPDR = (uint8_t)((count >> 8) & 0x00FF); 
		}
	}
	
	rescheduleTask(TASK_SPI, NULL);
}
