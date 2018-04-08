#include <stddef.h>
#include <avr/io.h>

#include "task.h"
#include "ledtask.h"

extern "C" {
	#include "led_utils.h"
}

bool on = false;

LEDTask1::LEDTask1(uint16_t ID) : Task(ID)
{
}

void LEDTask1::run(void * p)
{
    if (on) {
		/* set pin 5 low to turn led off */
		//PORTB &= ~LED_ONBOARD;
        on = false;
    }
    else {
		/* set pin 5 high to turn led on */
		//PORTB |= LED_ONBOARD;
        on = true;
    }
	
	reschedule();
}


LEDTask2::LEDTask2(uint16_t ID) : Task(ID)
{
}

void LEDTask2::run(void * p)
{
    if (on) {
		/* set pin 5 low to turn led off */
		//PORTB &= ~LED_PORT0;
        on = false;
    }
    else {
		/* set pin 5 high to turn led on */
		//PORTB |= LED_PORT0;
        on = true;
    }
	
	reschedule();
}