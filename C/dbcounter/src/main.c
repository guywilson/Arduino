#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"
#include "heartbeat.h"
#include "dbtask.h"

#include "led_utils.h"
#include "rtc_atmega328p.h"
#include "spi_atmega328p.h"
#include "pwm_atmega328p.h"
#include "error.h"

void setup(void)
{
	//stop interrupts
	cli();
	
	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_DEBOUNCE, &DebounceTask);
	registerTask(TASK_SPI, &SpiTask);

	setupLEDPin();
	setupRTC();
	setupDebouncePorts();
	setupSPI();
	setupPWM();

	//enable interrupts
    sei();
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_HEARTBEAT, 29500, NULL);
	scheduleTask(TASK_DEBOUNCE, 3, NULL);
	scheduleTask(TASK_SPI, 10, NULL);

	/*
	** Start the scheduler...
	*/
	startScheduler();
	
	/*
	** Should never reach here...
	*/
	handleError(ERROR_SCHED_DROPOUT);
	
	return 0;
}
