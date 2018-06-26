#include <stddef.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"
#include "mbarlookup.h"
#include "humiditylookup.h"
//#include "templookup.h"

uint16_t		adcResults[NUM_ADC_CHANNELS][ADC_RESULT_ARRAY_SIZE];
uint8_t			resultPtr[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t			conversionCount = 0;
uint16_t		MAV[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};

void ADCTask(PTASKPARM p)
{
	PADCRESULT			r =		(PADCRESULT)p;
	uint8_t				c;
	uint8_t				ptr;
	uint8_t				oldestPtr;

	c	= r->channel;
	ptr = resultPtr[c];
	oldestPtr = ptr + 1;

	if (oldestPtr == ADC_RESULT_ARRAY_SIZE) {
		oldestPtr = 0;
	}
	
	/*
	** Recommended that the first conversion result for each channel
	** is ignored as it is likely to be innacurate...
	*/
	if (conversionCount < ADC_USED_CHANNELS) {
		conversionCount++;
	}
	else {
		/*
		 * Calculate the moving average...
		 */
		MAV[c] = MAV[c] + (r->result >> ADC_RESULT_AVG_SHIFT) - (adcResults[c][oldestPtr] >> ADC_RESULT_AVG_SHIFT);

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
	return MAV[channel];
}

int getPressure(char * pszDest)
{
	PGM_P		pressure;
	uint16_t	avgPressureADC;
	
	avgPressureADC = getADCAverage(ADC_CHANNEL2);
	
	memcpy_P(&pressure, &mbarLookup[avgPressureADC], sizeof(PGM_P));
	strcpy_P(pszDest, pressure);
	
	return strlen(pszDest);
}

int getHumidity(char * pszDest)
{
	PGM_P		humidity;
	uint16_t	avgHumidityADC;
	
	avgHumidityADC = getADCAverage(ADC_CHANNEL3) - ADC_HUMIDITY_OFFSET;
	
	memcpy_P(&humidity, &humidityLookup[avgHumidityADC], sizeof(PGM_P));
	strcpy_P(pszDest, humidity);
	
	return strlen(pszDest);
}

int getTemperature(char * pszDest)
{
	PGM_P			temperature;
	int16_t			avgPositiveTempADC;
	int16_t			avgNegativeTempADC;
	int16_t			t;
	
	avgPositiveTempADC = getADCAverage(ADC_CHANNEL0);
	avgNegativeTempADC = getADCAverage(ADC_CHANNEL1);
	
	//t = (avgPositiveTempADC - avgNegativeTempADC) + TEMP_INDEX_OFFSET;
	
	//memcpy_P(&temperature, &tempLookup[t], sizeof(PGM_P));
	//strcpy_P(pszDest, temperature);
	strcpy(pszDest, "25.53");
	
	return strlen(pszDest);
}
