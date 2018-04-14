#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"
#include "ledtask.h"
#include "rxcmdtask.h"
#include "adctask.h"

#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "led_utils.h"
#include "error.h"

void setup()
{
    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    /* set pin 0 of PORTB for output*/
    DDRB |= _BV(DDB0);

	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_RXCMD, &RxCmdTask);
	registerTask(TASK_ADC, &ADCTask);
	
	setupRTC();
	setupSerial();
	setupADC();
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_HEARTBEAT, 950, NULL);

	/*
	** Start the scheduler...
	*/
	schedule();
	
	handleError(ERROR_SCHED_DROPOUT);
}
