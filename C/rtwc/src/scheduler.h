#include <stdint.h>

#ifndef _INCL_SCHEDULER
#define _INCL_SCHEDULER

#define MAX_TASKS           	16

typedef void *					PTASKPARM;
typedef uint32_t				timer_t;	// Implemented timer resolution, change if
											// your RTC is 64-bit for example.

#define MAX_TIMER_VALUE			~((timer_t)0)

void		initScheduler();
void		registerTask(uint16_t taskID, void (* run)(PTASKPARM));
void		deregisterTask(uint16_t taskID);
void		scheduleTask(uint16_t taskID, timer_t time, PTASKPARM p);
void		rescheduleTask(uint16_t taskID, PTASKPARM p);
void		unscheduleTask(uint16_t taskID);

void		startScheduler();

#endif