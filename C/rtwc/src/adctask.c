#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"

uint16_t		adcResults[NUM_ADC_CHANNELS][ADC_RESULT_ARRAY_SIZE];

uint8_t			resultPtr[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};

uint8_t			conversionCount = 0;

void ADCTask(PTASKPARM p)
{
	PADCRESULT	r =		(PADCRESULT)p;
	uint8_t		c;
	uint8_t		ptr;

	c	= r->channel;
	ptr = resultPtr[c];
	
	/*
	** Recommended that the first conversion result for each channel
	** is ignored as it is likely to be innacurate...
	*/
	if (conversionCount < ADC_USED_CHANNELS) {
		conversionCount++;
	}
	else {
		adcResults[c][ptr] = r->result;
		
		resultPtr[c]++;
		
		if (resultPtr[c] == ADC_RESULT_ARRAY_SIZE) {
			resultPtr[c] = 0;
		}
	}
	
	/*
	** Trigger next conversion...
	*/
	ADCSRA |= _BV(ADSC);
}

uint16_t getADCAverage(uint8_t channel)
{
	int			i;
	uint16_t	average = 0;

	for (i = 0;i < ADC_RESULT_ARRAY_SIZE;i++) {
		average += adcResults[channel][i];
	}
	
	average = average >> ADC_RESULT_AVG_SHIFT;
	
	return average;
}
