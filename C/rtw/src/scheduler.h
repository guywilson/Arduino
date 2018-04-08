#include "task.h"

#ifndef _INCL_SCHEDULER
#define _INCL_SCHEDULER

#define MAX_TASKS           16


class RTScheduler
{
    private:
		Task		*		tasks[MAX_TASKS];
        
        int                 taskCount;
 
 	public:
        RTScheduler();
        
        void        addTask(Task * task);
        void        deleteTask(uint16_t taskID);
        
        void        start();
};

#endif