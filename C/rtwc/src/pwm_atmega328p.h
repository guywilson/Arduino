#ifndef _INCL_PWM_ATMEGA328P
#define _INCL_PWM_ATMEGA328P

void setupPWM(void);
void increasePWMOnTime(uint8_t amount);
void decreasePWMOnTime(uint8_t amount);

#endif