#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "int_atmega328p.h"
#include "kphlookup.h"
#include "anonometer.h"
#include "taskdef.h"

uint16_t	maxRPS = 0;
uint16_t	avgRPS = 0;

void anonometerTask(PTASKPARM p)
{
	static uint16_t		index = 0;
	static uint16_t		max = 0;
	static uint16_t		avg = 0;
	uint16_t			revolutionsPerSecond;
	
	/*
	** Get number of interrupts (revolutions) since the last
	** envocation of the task (runs once every second), e.g.
	** revolutions per second, from this we can calculate the
	** wind speed. This value is accumulated to calculate the
	** average every 64 seconds...
	*/
	revolutionsPerSecond = getExternalInterruptCount(ANONOMETER_EXTINT_PIN);
	
	/*
	** Keep track of the maximum value. In terms of
	** wind speed, this gives us the maximum 'gust' speed
	*/
	if (revolutionsPerSecond > max) {
		max = revolutionsPerSecond;
	}
	
	avg += revolutionsPerSecond;
	
	index++;
	
	if (index == WIND_SPEED_AVG_COUNT) {
		/*
		** Divide by 64...
		*/
		avgRPS = (avg >> WIND_SPEED_AVG_SHIFT) & 0x00FF;
		maxRPS = max;
		
		/*
		** Reset values...
		*/
		avg		= 0;
		max		= 0;
		index	= 0;
	}
	
	rescheduleTask(TASK_ANONOMETER, NULL);
}

float getAvgWindSpeed(void)
{
	float			avgSpeed;
	
	if (avgRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		avgRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}
	
	avgSpeed = pgm_read_float(&(kphLookup[avgRPS]));
	
	return avgSpeed;
}

float getMaxWindSpeed(void)
{
	float			maxSpeed;
	
	if (maxRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		maxRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}
	
	maxSpeed = pgm_read_float(&(kphLookup[maxRPS]));
	
	return maxSpeed;
}