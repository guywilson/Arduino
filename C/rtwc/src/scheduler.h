#ifndef _INCL_SCHEDULER
#define _INCL_SCHEDULER

#define MAX_TASKS           	16

typedef void *		PTASKPARM;

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

void		initScheduler();
void		registerTask(uint16_t taskID, void (* run)(PTASKPARM));
void		scheduleTask(uint16_t taskID, uint32_t time, PTASKPARM p);
void		rescheduleTask(uint16_t taskID, PTASKPARM p);
void		unscheduleTask(uint16_t taskID);

void		schedule();

#endif