#include <avr/io.h>

#include "led_utils.h"

void turnOn(int LED_ID)
{
    /* set pin 5 high to turn led on */
    PORTB |= LED_ID;
}

void turnOff(int LED_ID)
{
    /* set pin 5 low to turn led off */
    PORTB &= ~LED_ID;
}
