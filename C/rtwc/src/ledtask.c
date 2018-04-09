#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "ledtask.h"
#include "led_utils.h"
#include "taskdef.h"

void LEDTask1(PTASKPARM p)
{
	static uint8_t on = 0;
	
    if (on) {
		/* set pin 5 low to turn led off */
		PORTB &= ~LED_ONBOARD;
        on = 0;
		scheduleTask(TASK_LED1, 950, NULL);
    }
    else {
		/* set pin 5 high to turn led on */
		PORTB |= LED_ONBOARD;
        on = 1;
		scheduleTask(TASK_LED1, 50, NULL);
    }
}

void LEDTask2(PTASKPARM p)
{
	static uint8_t on = 0;
	
    if (on) {
		/* set pin 5 low to turn led off */
		PORTB &= ~LED_PORT0;
        on = 0;
    }
    else {
		/* set pin 5 high to turn led on */
		PORTB |= LED_PORT0;
        on = 1;
    }
	
	rescheduleTask(TASK_LED2, NULL);
}
