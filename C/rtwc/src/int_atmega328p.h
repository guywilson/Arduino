#ifndef _INCL_INTATMEGA328P
#define _INCL_INTATMEGA328P

#define	INT_PIN_0					0
#define INT_PIN_1					1

void		setupExternalInterrupts(void);
uint16_t 	getExternalInterruptCount(int intPin);

#endif