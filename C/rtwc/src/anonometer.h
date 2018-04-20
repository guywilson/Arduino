#include "int_atmega328p.h"

#ifndef _INCL_ANONOMETER
#define _INCL_ANONOMETER

#define WIND_SPEED_AVG_COUNT			 64
#define WIND_SPEED_AVG_SHIFT			  7

#define ANONOMETER_EXTINT_PIN			INT_PIN_0

void anonometerTask(PTASKPARM p);
float getAvgWindSpeed(void);
float getMaxWindSpeed(void);

#endif