#include <stddef.h>
#include <stdint.h>

#include "scheduler.h"
#include "int_atmega328p.h"
#include "rainguage.h"
#include "rainfall.h"
#include "taskdef.h"

uint16_t		avgTPH = 0;
uint16_t		maxTPH = 0;
uint32_t		totalTPH = 0;

void rainGuageTask(PTASKPARM p)
{
	static uint16_t		index = 0;
	static uint16_t		max = 0;
	static uint16_t		avg = 0;
	uint16_t			tipsPerHour;
	
	/*
	** Get number of interrupts (tips) since the last
	** envocation of the task (runs once every hour), from this 
	** we can calculate the rainfall in mm/hour. This value is 
	** accumulated to calculate the average every 24 hours...
	*/
	tipsPerHour = getExternalInterruptCount(RAINGUAGE_EXTINT_PIN);
	
	/*
	** Keep track of the maximum value...
	*/
	if (tipsPerHour > max) {
		max = tipsPerHour;
	}
	
	avg += tipsPerHour;
	
	index++;
	
	if (index == RAINGUAGE_AVG_COUNT) {
		totalTPH += avg;
		
		/*
		** Divide by 24...
		*/
		avgTPH = (avg / RAINGUAGE_AVG_COUNT);
		maxTPH = max;
		
		/*
		** Reset values...
		*/
		avg		= 0;
		max		= 0;
		index	= 0;
	}
	
	rescheduleTask(TASK_RAINGUAGE, NULL);
}

float getAvgRainfall(void)
{
	float avgRainfall;

	if (avgTPH >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		avgTPH = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	avgRainfall = rainfallLookup[avgTPH];
	
	return avgRainfall;
}

float getMaxRainfall(void)
{
	float maxRainfall;

	if (maxTPH >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		maxTPH = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	maxRainfall = rainfallLookup[maxTPH];
	
	return maxRainfall;
}
