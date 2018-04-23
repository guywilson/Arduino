#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "rtc_atmega328p.h"
#include "error.h"

#define CHECK_TIMER_OVERFLOW
#define MAX_TIMER_VALUE				0xFFFFFFFF

typedef struct
{
	uint16_t		ID;
	uint32_t		startTime;
	uint32_t		scheduledTime;
	uint32_t		delay;
	uint8_t			isScheduled;
	uint8_t			isAllocated;
	PTASKPARM		pParameter;
	
	void (* run)(PTASKPARM);
}
TASKDEF;

typedef TASKDEF *	PTASKDEF;

extern volatile uint32_t _realTimeClock;

TASKDEF		taskDefs[MAX_TASKS];
int			taskCount = 0;

/******************************************************************************
**
** Calculate the scheduled time
**
** If we don't care about checking if the timer will overflow, use a macro
** to calculate the default scheduled time.
**
******************************************************************************/
#ifdef CHECK_TIMER_OVERFLOW
uint32_t _getScheduledTime(uint32_t startTime, uint32_t requestedDelay)
{
	uint32_t		overflowTime;
	
	overflowTime = MAX_TIMER_VALUE - startTime;
	
	if (overflowTime < requestedDelay) {
		return (requestedDelay - overflowTime);
	}
	else {
		return (startTime + requestedDelay);
	}
}
#else
#define _getScheduledTime(startTime, requestedDelay)	(startTime + requestedDelay)
#endif

/******************************************************************************
**
** Public API functions
**
******************************************************************************/
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

void deregisterTask(uint16_t taskID)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->ID				= 0;
			td->startTime		= 0;
			td->scheduledTime	= 0;
			td->delay			= 0;
			td->isScheduled		= 0;
			td->isAllocated		= 0;
			td->pParameter		= NULL;
			
			taskCount--;
			break;
		}
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
			td->scheduledTime = _getScheduledTime(td->startTime, td->delay);
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
			td->scheduledTime = _getScheduledTime(td->startTime, td->delay);
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
	
	/*
	** Scheduler loop, run forever waiting for tasks to be
	** scheduled...
	*/
	while (1) {
		td = &taskDefs[i];
		
		if (td->isScheduled && td->isAllocated) {
			if (_realTimeClock >= td->scheduledTime) {
				/*
				** Mark the task as un-scheduled, so by default the
				** task will not run again automatically. If the task
				** reschedules itself, this flag will be reset to 1...
				*/
				td->isScheduled = 0;
				
				/*
				** Run the task...
				*/
				td->run(td->pParameter);
			}
		}
		
		i++;
		
		if (i == MAX_TASKS) {
			i = 0;
		}
	}
}
