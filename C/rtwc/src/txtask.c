#include <stdint.h>
#include <stddef.h>

#include "scheduler.h"
#include "serial_atmega328p.h"
#include "taskdef.h"
#include "thermometer.h"
#include "barometer.h"
#include "hygrometer.h"
#include "anemometer.h"
#include "rainguage.h"
#include "txtask.h"
#include "utils.h"

void TxTask(PTASKPARM p)
{
	char		szBuffer[64];
	int			len;
	int			txStrLen = 0;
	int			i = 0;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 't';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], getTemperature());
	szBuffer[i + len] = '>';
	i++;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'p';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], getPressure());
	szBuffer[i + len] = '>';
	i++;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'h';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], getHumidity());
	szBuffer[i + len] = '>';
	i++;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'w';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], getAvgWindSpeed());
	szBuffer[i + len] = '>';
	i++;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'r';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], getAvgRainfall());
	szBuffer[i + len] = '>';
	i++;
	txStrLen += len + 4;

	txstr(szBuffer, txStrLen);
	
	rescheduleTask(TASK_TX, NULL);
}
