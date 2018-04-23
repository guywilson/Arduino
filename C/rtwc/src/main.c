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
#include "pwmtask.h"

#include "led_utils.h"
#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "int_atmega328p.h"
#include "pwm_atmega328p.h"
#include "error.h"

void setup(void)
{
	//stop interrupts
	cli();
	
	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_RXCMD, &RxCmdTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANONOMETER, &anonometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	registerTask(TASK_PWM, &PWMTask);

	setupLEDPin();
	setupRTC();
	setupSerial();
	setupADC();
	setupExternalInterrupts();

	//enable interrupts
    sei();
	
	setupPWM();
	triggerADC();
}

int main(void)
{
	setup();
	
	scheduleTask(TASK_HEARTBEAT, 950, NULL);
	scheduleTask(TASK_ANONOMETER, 1000, NULL);
	scheduleTask(TASK_RAINGUAGE, 3600000, NULL); // Schedule in 1 hour...
	scheduleTask(TASK_PWM, 50, NULL);

	/*
	** Start the scheduler...
	*/
	schedule();
	
	/*
	** Should never reach here...
	*/
	handleError(ERROR_SCHED_DROPOUT);
	
	return 0;
}
