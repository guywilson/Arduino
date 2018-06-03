#include <stddef.h>
#include <avr/io.h>

#include "scheduler.h"
#include "heartbeat.h"
#include "led_utils.h"
#include "taskdef.h"

void HeartbeatTask(PTASKPARM p)
{
	static uint8_t on = 0;
	
    if (on) {
		/* set pin 5 low to turn led off */
		PORTB &= ~LED_ONBOARD;
        on = 0;
		scheduleTask(TASK_HEARTBEAT, 9500, NULL);
    }
    else {
		/* set pin 5 high to turn led on */
		PORTB |= LED_ONBOARD;
        on = 1;
		scheduleTask(TASK_HEARTBEAT, 500, NULL);
    }
}
