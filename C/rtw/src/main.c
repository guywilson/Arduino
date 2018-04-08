#include <avr/io.h>

#include "factory.h"
#include "taskfactory.h"
#include "taskdef.h"
#include "ledtask.h"
#include "serial_atmega328p.h"

extern "C" {
	#include "rtc_atmega328p.h"
	#include "led_utils.h"
	#include "error.h"
}

extern "C" void __cxa_pure_virtual()
{
	handleError(ERROR_PUREVIRTUAL);
}

int main(void)
{
    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    /* set pin 0 of PORTB for output*/
    DDRB |= _BV(DDB0);

	setupRTC();
	setupSerial();
	
	RTScheduler * s = RTSFactory::getScheduler();

	Task * t1 = getTask(TASK_LED1);
	t1->schedule(100);
	
	s->addTask(t1);

	Task * t2 = getTask(TASK_LED2);
	t2->schedule(25);
	
	s->addTask(t2);
	
	/*
	** Start the scheduler...
	*/
	s->start();
	
	handleError(ERROR_SCHED_DROPOUT);
}
