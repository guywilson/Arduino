#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"
#include "heartbeat.h"
#include "rxcmdtask.h"
#include "adctask.h"
#include "anonometer.h"
#include "rainguage.h"

#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "int_atmega328p.h"
#include "error.h"

void setup()
{
    //stop interrupts
    cli();

	/* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    /* set pin 0 of PORTB for output*/
    DDRB |= _BV(DDB0);

	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_RXCMD, &RxCmdTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANONOMETER, &anonometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	
	setupRTC();
	setupSerial();
	setupADC();
	setupExternalInterrupts();

	//enable interrupts
    sei();
	
	triggerADC();
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_HEARTBEAT, 950, NULL);
	scheduleTask(TASK_ANONOMETER, 1000, NULL);
	scheduleTask(TASK_RAINGUAGE, 3600000, NULL); // Schedule in an hour...

	/*
	** Start the scheduler...
	*/
	schedule();
	
	handleError(ERROR_SCHED_DROPOUT);
}
