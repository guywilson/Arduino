#include <stdint.h>

#include "timer.h"

#ifndef _INCL_TASK
#define _INCL_TASK

class Task
{
    private:
        uint16_t            _ID;
		uint32_t			_startTime;
		uint32_t			_requestedDelay;
        uint32_t            _scheduleTime;
		void *				_parameter;
		bool				_isRecurring;
		
	protected:
		void				setRecurring(bool recurring);
        
    public:
		Task(uint16_t ID);
        
        uint16_t            getID();
		uint32_t			getStartTime();
        uint32_t            getScheduledTime();
		bool				isRecurring();
        
        uint16_t            schedule(const uint32_t time);
        uint16_t            schedule(const uint32_t time, void * pParameter);
        
        void                reschedule();
        void                reschedule(const uint32_t time);

		void *				getParameter();
        
        void                clear();
        
        virtual void        run(void * p);
};

#endif