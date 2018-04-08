#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "ledtask.h"
#include "rtc_atmega328p.h"
#include "error.h"
#include "led_utils.h"

extern volatile uint32_t _realTimeClock;

TASKDEF		taskDefs[MAX_TASKS];
int			taskCount = 0;

void initScheduler()
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	taskCount = 0;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		td->ID				= 0;
		td->startTime		= 0;
		td->scheduledTime	= 0;
		td->delay			= 0;
		td->isScheduled		= 0;
		td->isAllocated		= 0;
		td->pParameter		= NULL;
	}
}

void registerTask(uint16_t taskID, void (* run)(PTASKPARM))
{
	int			i = 0;
	PTASKDEF	td = NULL;
	uint8_t		noFreeTasks = 1;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (!td->isAllocated) {
			td->ID = taskID;
			td->isAllocated = 1;
			td->run = run;
			taskCount++;
			noFreeTasks = 0;
			break;
		}
	}
    
	if (noFreeTasks) {
		handleError(ERROR_SCHED_NOFREETASKS);
	}
	if (taskCount > MAX_TASKS) {
		handleError(ERROR_SCHED_TASKCOUNTOVERFLOW);
	}
}

void scheduleTask(uint16_t taskID, uint32_t time, PTASKPARM p)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = _realTimeClock;
			td->delay = time;
			td->scheduledTime = td->startTime + td->delay;
			td->isScheduled = 1;
			td->pParameter = p;
			break;
		}
	}
}

void rescheduleTask(uint16_t taskID, PTASKPARM p)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = _realTimeClock;
			td->scheduledTime = td->startTime + td->delay;
			td->isScheduled = 1;
			td->pParameter = p;
			break;
		}
	}
}

void unscheduleTask(uint16_t taskID)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = 0;
			td->scheduledTime = 0;
			td->isScheduled = 0;
			td->pParameter = NULL;
			break;
		}
	}
}

void schedule()
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	while (1) {
		td = &taskDefs[i];
		
		if (td->isScheduled && td->isAllocated) {
			if (_realTimeClock >= td->scheduledTime) {
				td->isScheduled = 0;
				td->run(td->pParameter);
			}
		}
		
		i++;
		
		if (i == MAX_TASKS) {
			i = 0;
		}
	}
}
