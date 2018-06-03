#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "dbtask.h"
#include "taskdef.h"

#include "int_atmega328p.h"

void DebounceTask(PTASKPARM p)
{
	static uint8_t		index = 0;
	static uint8_t		inputState[NUM_CHECKS];
	static uint8_t		debouncedState = 0x00;
	uint8_t				i;
	uint8_t				transientState = 0xFF;
	
	/*
	** Read the port state every run...
	*/
	inputState[index++] = getDebounceInputValue();

	for (i = 0;i < NUM_CHECKS;i++) {
		transientState &= inputState[i];
	}
	
	debouncedState ^= transientState;

	for (i = 0;i < NUM_INPUT_CHANNELS;i++) {
		if ((debouncedState >> i) & 0x01) {
			incrementDebouncedCount(i);
		}
	}
	
	if (index == NUM_CHECKS) {
		index = 0;
	}
	
	rescheduleTask(TASK_DEBOUNCE, NULL);
}
