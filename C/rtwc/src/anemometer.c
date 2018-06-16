#include <stddef.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "int_atmega328p.h"
#include "kphlookup.h"
#include "anemometer.h"
#include "readcounter.h"
#include "taskdef.h"
#include "utils.h"
#include "serial_atmega328p.h"

uint16_t	rpsBuffer[WIND_SPEED_AVG_COUNT];

void anemometerTask(PTASKPARM p)
{
	static uint16_t		i = 0;
	static uint8_t		bitCount = 0;
	static uint8_t		isReadingCounter = 1;
	static uint8_t		interruptLineState = 1;
	static uint8_t		rpsCount = 0;
	uint16_t			revolutionsPerSecond;
	
	/*
	** Get number of interrupts (revolutions) since the last
	** envocation of the task (runs once every second), e.g.
	** revolutions per second, from this we can calculate the
	** wind speed. This value is accumulated to calculate the
	** average every 64 seconds...
	*/
	if (isReadingCounter) {
		setCounterChannel(0);
		toggleCounterInterruptLine(interruptLineState);
		
		/*
		** If the interrupt line is high, do nothing
		** simple reschedule the task for 1ms to drop
		** the line, then we should be ready to read 
		** a bit from the counter...
		*/
		if (interruptLineState) {
			interruptLineState = 0;
		}
		else {
			interruptLineState = 1;
			
			rpsCount |= (getNextCounterBit() << bitCount);
		
			bitCount++;
		}
		
		/*
		** We've read the whole byte...
		*/
		if (bitCount == 8) {
			bitCount = 0;
			isReadingCounter = 0;
		}
		
		scheduleTask(TASK_ANEMOMETER, 1, NULL);
	}
	else {
		revolutionsPerSecond = rpsCount;

		rpsBuffer[i] = revolutionsPerSecond;

		i++;

		if (i == WIND_SPEED_AVG_COUNT) {
			i = 0;
		}

		isReadingCounter = 1;
		
		scheduleTask(TASK_ANEMOMETER, 984, NULL);
	}
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

char * getAvgWindSpeed(void)
{
	char *			avgSpeed;
	uint16_t		avgRPS;
	
	avgRPS = getAvgRPS();
	
	if (avgRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		avgRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}
	
	avgSpeed = pgm_read_ptr(&(kphLookup[avgRPS]));
	
	return avgSpeed;
}
