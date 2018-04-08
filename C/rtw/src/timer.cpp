#include "timer.h"
#include "factory.h"

extern uint32_t getCurrentTime();

Timer::Timer()
{
    this->startTime = getCurrentTime();
}

bool Timer::compare(const uint32_t requested)
{
    if (getTimerValue() >= requested) {
        return true;
    }
    else {
        return false;
    }
}

uint32_t Timer::stop()
{
    uint32_t    timerValue;
    
    timerValue = getTimerValue();
    
    this->startTime = 0;
    
    return timerValue;
}

void Timer::reset()
{
    this->startTime = getCurrentTime();
}

uint32_t Timer::getTimerValue()
{
    return (getCurrentTime() - this->startTime);
}

