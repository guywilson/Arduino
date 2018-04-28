#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"

static ADCRESULT			adcr;

void setupADC(void)
{
	ADMUX	= _BV(REFS0) | _BV(ADLAR) | ADC_CHANNEL0;
	ADCSRA	= _BV(ADEN) | _BV(ADIE) | ADC_PRESCALER_DIV16;
}

void triggerADC(void)
{
	/*
	** Trigger first conversion...
	*/
	ADCSRA |= _BV(ADSC);
}

/*
** ADC Conversion complete interrupt...
*/
ISR(ADC_vect, ISR_BLOCK)
{
	uint8_t				channel;
	uint16_t			low;
	uint16_t			high;
	
	/*
	** 10-bit result from ADC
	** Read LSB first then MSB
	*/
	channel	= ADMUX & 0x07;
	low		= ADCL;
	high	= ADCH & 0x03;

	adcr.channel = channel;
	adcr.result = (high << 8) | low;

	/*
	** Increment Channel for next conversion...
	*/
	ADMUX++;
	
	if ((ADMUX & 0x07) == ADC_USED_CHANNELS) {
		ADMUX &= 0xF8;
	}

	/*
	** Each channel will process a result every 125 ms
	** This will fill the moving average buffer for each 
	** channel every 2 seconds...
	*/
	scheduleTask(TASK_ADC, 125, (PTASKPARM)&adcr);
}