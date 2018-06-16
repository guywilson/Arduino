#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"
#include "heartbeat.h"
#include "adctask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "txtask.h"

#include "led_utils.h"
#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "int_atmega328p.h"
#include "readcounter.h"
#include "serial_atmega328p.h"
#include "error.h"

void setup(void)
{
	//stop interrupts
	cli();
	
	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANEMOMETER, &anemometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	registerTask(TASK_TX, &TxTask);

	setupLEDPin();
	setupRTC();
	setupSerial();
	setupADC();
	setupCounterRead();
	setupExternalInterrupts();

	//enable interrupts
    sei();
	
	triggerADC();
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_HEARTBEAT, 2950, NULL);
	scheduleTask(TASK_ANEMOMETER, 1000, NULL);
	scheduleTask(TASK_RAINGUAGE, 3600000, NULL); // Schedule in 1 hour...
	scheduleTask(TASK_TX, 5000, NULL);

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
