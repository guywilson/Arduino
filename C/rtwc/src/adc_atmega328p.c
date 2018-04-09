#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"

volatile uint16_t adcResultCH0;
volatile uint16_t adcResultCH1;

uint32_t conversionCount = 0L;


void setupADC(void)
{
	sei();
	
	ADMUX	= _BV(REFS1) | _BV(REFS0) | _BV(ADLAR) | ADC_CHANNEL0;
	ADCSRA	= _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | ADC_PRESCALER_DIV16;
}

/*
** ADC Conversion complete interrupt...
*/
ISR(ADC_vect, ISR_BLOCK)
{
	static ADCRESULT	adcr;
	uint8_t				channel;
	
	channel = ADMUX & 0x07;
	
	adcr.channel = channel;
	
	switch (channel) {
		case ADC_CHANNEL0:
			/*
			** Clear last result...
			*/
			adcResultCH0 = 0x0000;

			/*
			** 10-bit result from ADC
			** Read LSB first then MSB
			*/
			adcResultCH0 |= ADCL;
			adcResultCH0 |= (ADCH << 8);

			/*
			** Recommended that the first conversion result for each channel
			** is ignored as it is likely to be innacurate. However, we still
			** need to read the result to allow the next conversion to be 
			** triggered...
			*/
			if (conversionCount < ADC_USED_CHANNELS) {
				/*
				** Trigger conversion for channel 1...
				*/
				ADMUX++;
				ADCSRA |= _BV(ADSC);
			}
			else {
				adcr.result = adcResultCH0 & 0x03FF;

				/*
				** Each channel will process a result every 7.5 seconds
				** That is 8 results every minute, which will feed into
				** a moving average filter...
				*/
				scheduleTask(TASK_ADC, 3750, &adcr);
			}
			
			conversionCount++;
			break;
			
		case ADC_CHANNEL1:
			/*
			** Clear last result...
			*/
			adcResultCH1 = 0x0000;

			/*
			** 10-bit result from ADC
			** Read LSB first then MSB
			*/
			adcResultCH1 |= ADCL;
			adcResultCH1 |= (ADCH << 8);

			/*
			** Recommended that the first conversion result for each channel
			** is ignored as it is likely to be innacurate. However, we still
			** need to read the result to allow the next conversion to be 
			** triggered...
			*/
			if (conversionCount < ADC_USED_CHANNELS) {
				/*
				** Trigger conversion for channel 0...
				*/
				ADMUX--;
				ADCSRA |= _BV(ADSC);
			}
			else {
				adcr.result = adcResultCH1 & 0x03FF;

				/*
				** Each channel will process a result every 7.5 seconds
				** That is 8 results every minute, which will feed into
				** a moving average filter...
				*/
				scheduleTask(TASK_ADC, 3750, &adcr);
			}
			
			conversionCount++;
			break;
	}
}