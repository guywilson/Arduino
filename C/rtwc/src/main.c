#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "taskdef.h"
#include "ledtask.h"
#include "rxcmdtask.h"

#include "rtc_atmega328p.h"
#include "led_utils.h"
#include "error.h"

void setup()
{
    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    /* set pin 0 of PORTB for output*/
    DDRB |= _BV(DDB0);

	setupRTC();
	setupSerial();
	initScheduler();
	
	registerTask(TASK_LED1, &LEDTask1);
	registerTask(TASK_LED2, &LEDTask2);
	registerTask(TASK_RXCMD, &RxCmdTask);
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_LED1, 75, NULL);
	//scheduleTask(TASK_LED2, 75, NULL);
	
	/*
	** Start the scheduler...
	*/
	schedule();
	
	handleError(ERROR_SCHED_DROPOUT);
}
