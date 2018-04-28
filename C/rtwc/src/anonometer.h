#include "int_atmega328p.h"

#ifndef _INCL_ANONOMETER
#define _INCL_ANONOMETER

#define WIND_SPEED_AVG_COUNT			 16
#define WIND_SPEED_AVG_SHIFT			  4

#define ANONOMETER_EXTINT_PIN			INT_PIN_0

void		anonometerTask(PTASKPARM p);
uint16_t	getAvgRPS(void);
uint16_t 	getMaxRPS(void);
float 		getAvgWindSpeed(void);
float 		getMaxWindSpeed(void);

#endif