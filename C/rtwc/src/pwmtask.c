#include <stddef.h>

#include "scheduler.h"
#include "taskdef.h"
#include "pwmtask.h"

#include "pwm_atmega328p.h"

int		count = 0;
int		direction = 1;

void PWMTask(PTASKPARM p)
{
	if (direction == 1) {
		increasePWMOnTime(PWM_CHANGE_INCREMENT);
		count += PWM_CHANGE_INCREMENT;
		
		if (count >= 255) {
			direction = -1;
		}
	}
	else if (direction == -1) {
		decreasePWMOnTime(PWM_CHANGE_INCREMENT);
		count -= PWM_CHANGE_INCREMENT;
		
		if (count <= 0) {
			direction = 1;
		}
	}
	
	rescheduleTask(TASK_PWM, NULL);
}
