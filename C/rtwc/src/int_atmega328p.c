#include <avr/io.h>
#include <avr/interrupt.h>

#include "int_atmega328p.h"
#include "led_utils.h"

volatile uint16_t counterINT0 = 0;
volatile uint16_t counterINT1 = 0;

void setupExternalInterrupts(void)
{
	/*
	** Set pin D2 (INT0) and D3 (INT1) as inputs...
	*/
	DDRD	&= ~(_BV(DDD2) | _BV(DDD3));
	
	/*
	** Activate the pull-up resistor on pins D2 and D3...
	*/
	PORTD	|= _BV(PORTD2) | _BV(PORTD3);
	
	/*
	** Trigger the interrupts on a rising edge...
	*/
	EICRA |= 0x0F;
	
	/*
	** Enable the INT0 and INT1 interrupts...
	*/
	EIMSK |= 0x03;
}

uint16_t getExternalInterruptCount(int intPin)
{
	uint16_t		count = 0;
	
	switch (intPin) {
		case INT_PIN_0:
			count = counterINT0;
			counterINT0 = 0;
			break;
			
		case INT_PIN_1:
			count = counterINT1;
			counterINT1 = 0;
			break;
	}
	
	return count;
}

ISR(INT0_vect, ISR_BLOCK)
{
	counterINT0++;
	//toggleLED(LED_ONBOARD);
}

ISR(INT1_vect, ISR_BLOCK)
{
	counterINT1++;
}
