#include <stddef.h>

#include "task.h"

extern "C" {
	#include "rtc_atmega328p.h"
	#include "error.h"
}

Task::Task(uint16_t ID)
{
	clear();
	this->_ID = ID;
}

void * Task::getParameter()
{
	return this->_parameter;
}

void Task::setRecurring(bool recurring)
{
	this->_isRecurring = recurring;
}

uint16_t Task::getID()
{
    return this->_ID;
}

uint32_t Task::getStartTime()
{
	return this->_startTime;
}

uint32_t Task::getScheduledTime()
{
    return this->_scheduleTime;
}

bool Task::isRecurring()
{
	return this->_isRecurring;
}

uint16_t Task::schedule(const uint32_t time)
{
    return schedule(time, NULL);
}

uint16_t Task::schedule(const uint32_t time, void * pParameter)
{
	this->_startTime = getCurrentTime();
	this->_requestedDelay = time;
    this->_scheduleTime = this->_startTime + this->_requestedDelay;
	this->_parameter = pParameter;
	this->_isRecurring = false;
	
	return this->_ID;
}

void Task::reschedule()
{
    this->_startTime = getCurrentTime();
    this->_scheduleTime = this->_startTime + this->_requestedDelay;
	this->_isRecurring = true;
}

void Task::reschedule(const uint32_t time)
{
    this->_startTime = getCurrentTime();
	this->_requestedDelay = time;
    this->_scheduleTime = this->_startTime + this->_requestedDelay;
	this->_isRecurring = true;
}

void Task::clear()
{
	this->_scheduleTime = 0L;
	this->_startTime = 0L;
	this->_requestedDelay = 0L;
	this->_parameter = NULL;
	this->_isRecurring = false;
}

void Task::run(void * p)
{
	handleError(ERROR_PUREVIRTUAL);
}