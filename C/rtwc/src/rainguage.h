#include "int_atmega328p.h"

#ifndef _INCL_RAINGUAGE
#define _INCL_RAINGUAGE

#define RAINGUAGE_EXTINT_PIN			INT_PIN_1
#define RAINGUAGE_AVG_COUNT				24

void rainGuageTask(PTASKPARM p);
char * getAvgRainfall(void);

#endif