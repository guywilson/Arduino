#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "adctask.h"
#include "adc_atmega328p.h"
#include "barometer.h"
#include "mbarlookup.h"

float getPressure()
{
	float		pressure;
	uint16_t	adcPressure;
	
	
}