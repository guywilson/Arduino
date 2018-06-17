#include "int_atmega328p.h"

#ifndef _INCL_ANEMOMETER
#define _INCL_ANONOMETER

#define WIND_SPEED_AVG_COUNT			 16
#define WIND_SPEED_AVG_SHIFT			  4

#define ANEMOMETER_EXTINT_PIN			INT_PIN_0

void		anemometerTask(PTASKPARM p);
uint16_t	getAvgRPS(void);
int 		getAvgWindSpeed(char * pszDest);

#endif