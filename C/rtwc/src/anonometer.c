#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "int_atmega328p.h"
#include "kphlookup.h"
#include "anonometer.h"
#include "taskdef.h"
#include "utils.h"
#include "serial_atmega328p.h"

uint16_t	rpsBuffer[WIND_SPEED_AVG_COUNT];
uint16_t	maxRPS = 0;

void anonometerTask(PTASKPARM p)
{
	static uint16_t		i = 0;
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
	if (revolutionsPerSecond > maxRPS) {
		maxRPS = revolutionsPerSecond;
	}
	
	rpsBuffer[i] = revolutionsPerSecond;
	
	i++;
	
	if (i == WIND_SPEED_AVG_COUNT) {
		i = 0;
	}
	
	rescheduleTask(TASK_ANONOMETER, NULL);
}

uint16_t getAvgRPS(void)
{
	int			i;
	uint16_t	avgRPS = 0;
	
	for (i = 0;i < WIND_SPEED_AVG_COUNT;i++) {
		avgRPS += rpsBuffer[i];
	}
	
	avgRPS = avgRPS >> WIND_SPEED_AVG_SHIFT;
	
	return avgRPS;
}

uint16_t getMaxRPS(void)
{
	return maxRPS;
}

float getAvgWindSpeed(void)
{
	float			avgSpeed;
	uint16_t		avgRPS;
	
	avgRPS = getAvgRPS();
	
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