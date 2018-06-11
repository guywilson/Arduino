#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "adctask.h"
#include "adc_atmega328p.h"
#include "hygrometer.h"
#include "humiditylookup.h"

float getHumidity()
{
	float		humidity;
	uint16_t	avgHumidityADC;
	
	avgHumidityADC = getADCAverage(ADC_CHANNEL3) - ADC_HUMIDITY_OFFSET;
	
	humidity = pgm_read_float(&(humidityLookup[avgHumidityADC]));
	
	return humidity;
}