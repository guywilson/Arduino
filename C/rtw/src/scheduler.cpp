#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "factory.h"
#include "serial_atmega328p.h"

extern "C" {
	#include "rtc_atmega328p.h"
	#include "error.h"
	#include "led_utils.h"
}

extern volatile uint32_t _realTimeClock;

RTScheduler::RTScheduler()
{
	int i;
	
	this->taskCount = 0;
	
	for (i = 0;i < MAX_TASKS;i++) {
		tasks[i] = NULL;
	}
}

void RTScheduler::addTask(Task * task)
{
    int     	i = 0;
    bool    	noFreeTasks = true;
	Task	*	t = NULL;
    
    for (i = 0;i < MAX_TASKS;i++) {
		t = tasks[i];

		if (t == NULL) {
			tasks[i] = task;
            noFreeTasks = false;
			taskCount++;
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

void RTScheduler::deleteTask(uint16_t taskID)
{
    int     	i = 0;
	Task	*	t = NULL;
    
    for (i = 0;i < MAX_TASKS;i++) {
		t = tasks[i];

        if (t != NULL && t->getID() == taskID) {
			tasks[i] = NULL;
			taskCount--;
			break;
        }
    }
}

void RTScheduler::start()
{
	int			i = 0;
	Task	*	t = NULL;
	static bool	on = false;
	
	while (1) {
		t = tasks[i];
		
		if (t != NULL) {
			if (_realTimeClock >= t->getScheduledTime()) {
				t->run(t->getParameter());
//				t->reschedule();
//				
//				if (on) {
//					turnOff(LED_ONBOARD);
//					turnOff(LED_PORT0);
//					on = false;
//				}
//				else {
//					turnOn(LED_ONBOARD);
//					turnOn(LED_PORT0);
//					on = true;
//				}
				
				if (!t->isRecurring()) {
					tasks[i] = NULL;
					taskCount--;
				}
			}
		}
		
		i++;
		
		if (i == MAX_TASKS) {
			i = 0;
		}
	}
}
