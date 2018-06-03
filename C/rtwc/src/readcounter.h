#ifndef _INCL_READCOUNTER
#define _INCL_READCOUNTER

void	setupCounterRead(void);
void	setCounterChannel(uint8_t channel);
void 	toggleCounterInterruptLine(uint8_t state);
uint8_t getNextCounterBit(void);

#endif