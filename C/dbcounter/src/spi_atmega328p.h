#ifndef _INCL_SPI_ATMEGA328P
#define _INCL_SPI_ATMEGA328P

#define NUM_INPUT_CHANNELS		 	8

void		setupSPI();
void		setupDebouncePorts(void);
uint8_t		getDebounceInputValue(void);
void 		incrementDebouncedCount(uint8_t channel);
void		SpiTask(PTASKPARM p);

#endif