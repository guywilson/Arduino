#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"

uint16_t		adcResultsCH0[ADC_RESULT_ARRAY_SIZE];
uint16_t		adcResultsCH1[ADC_RESULT_ARRAY_SIZE];

uint8_t			resultPtrCH0 = 0;
uint8_t			resultPtrCH1 = 0;


void ADCTask(PTASKPARM p)
{
	PADCRESULT r = (PADCRESULT)p;
	
	if (r->channel == ADC_CHANNEL0) {
		adcResultsCH0[resultPtrCH0] = r->result;
		
		resultPtrCH0++;
		
		if (resultPtrCH0 == ADC_RESULT_ARRAY_SIZE) {
			resultPtrCH0 = 0;
		}
	}
	else if (r->channel == ADC_CHANNEL1) {
		adcResultsCH1[resultPtrCH1] = r->result;
		
		resultPtrCH1++;
		
		if (resultPtrCH1 == ADC_RESULT_ARRAY_SIZE) {
			resultPtrCH1 = 0;
		}
	}
}

uint16_t getADCAverage(uint8_t channel)
{
	int			i;
	uint16_t	average = 0;
	
	if (channel == 0) {
		for (i = 0;i < ADC_RESULT_ARRAY_SIZE;i++) {
			average += adcResultsCH0[i];
		}
	}
	else {
		for (i = 0;i < ADC_RESULT_ARRAY_SIZE;i++) {
			average += adcResultsCH1[i];
		}
	}
	
	average = average >> ADC_RESULT_AVG_SHIFT;
	
	return average;
}
