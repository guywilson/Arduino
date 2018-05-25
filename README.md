# Arduino
Arduino development

rtwc - Real Time Weather Station Controller
-------------------------------------------

Written in C and built using the avr-gcc toolset.

Based around a real-time scheduler, suitable for any number of real-time control systems. The scheduler uses a real-time clock driven by a timer interrupt, in this implementation on the Atmega328p, the real-time clock is incremented every millisecond. The scheduler can handle upto 16 scheduled tasks.

The scheduler API consists of the following functions:

void initScheduler();                         // Initialise the scheduler
void registerTask(taskID, ptr_to_task_func);  // Register a task with the scheduler, pass the address of the task function
void deregisterTask(taskID);                  // De-register a previously registered task
void scheduleTask(taskID, time, task_parms);  // Schedule a task to run in time ms
void rescheduleTask(taskID, task_parms);      // Reschedule a task to run again with the same time delay
void unscheduleTask(taskID);                  // Unschedule a previously scheduled task

void startScheduler();                        // Start the scheduler loop, should never return

The weather station controller is accepts commands via the serial port on the microcontroller, on an Arduino board, this is typically mapped to a USB port. The controller accepts the following commands:

PING            Returns ACK
ADC_READ        Returns the value of the specified ADC channel
AVG_WIND_SPEED  Returns the average wind speed in km/h
MAX_WIND_SPEED  Returns the max wind speed in km/h
AVG_RAINFALL    Returns the average rainfall in mm/h
MAX_RAINFALL    Returns the max rainfall in mm/h

The weather station takes inputs from sensors for temperature (ADC), air pressure (ADC), humidity (ADC), wind speed (EXTINT), rainfall (EXTINT).

command - Command controller envisaged to run on a RaspberryPi
--------------------------------------------------------------

Communicated with the Arduino over the serial port.
