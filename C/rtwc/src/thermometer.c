#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "adctask.h"
#include "adc_atmega328p.h"
#include "thermometer.h"
#include "templookup.h"

float getTemperature()
{
	float			temperature;
	int16_t			avgPositiveTempADC;
	int16_t			avgNegativeTempADC;
	int16_t			t;
	
	avgPositiveTempADC = getADCAverage(ADC_CHANNEL0);
	avgNegativeTempADC = getADCAverage(ADC_CHANNEL1);
	
	t = avgPositiveTempADC - avgNegativeTempADC;
	
	if (t < 0) {
		temperature = pgm_read_float(&(negTempLookup[t]));
	}
	else {
		temperature = pgm_read_float(&(posTempLookup[t]));
	}
	
	return temperature;
}
