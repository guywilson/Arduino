#ifndef _INCL_INTATMEGA328P
#define _INCL_INTATMEGA328P

#define	INT_PIN_0					0

#define NUM_INPUT_CHANNELS		 	8

void		setupExternalInterrupts(void);
void		setupDebouncePorts(void);
uint8_t		getRequestedCounter(void);
uint8_t		getDebounceInputValue(void);
void		incrementDebouncedCount(uint8_t channel);

#endif