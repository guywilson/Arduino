#include <stdint.h>

#ifndef _INCL_TIMER
#define _INCL_TIMER

class Timer
{
    private:
        uint32_t            startTime = 0;
        
        uint32_t            getTimerValue();
        
    public:
        Timer();
        
        bool                compare(const uint32_t requested);
        uint32_t            stop();
        
        void                reset();
};

#endif