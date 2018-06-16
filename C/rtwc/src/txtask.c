#include <stdint.h>
#include <stddef.h>
#include <string.h>

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
	char		szTemperature[8];
	char		szPressure[8];
	char		szHumidity[8];
	char		szWindSpeed[8];
	char		szRainfall[8];
	int			len;
	int			txStrLen = 0;
	int			i = 0;

	strcpy(szTemperature, getTemperature());
	strcpy(szPressure, getPressure());
	strcpy(szHumidity, getHumidity());
	strcpy(szWindSpeed, getAvgWindSpeed());
	strcpy(szRainfall, getAvgRainfall());

	szBuffer[i++] = '<';
	szBuffer[i++] = 't';
	szBuffer[i++] = ':';
	strcpy(&szBuffer[i], szTemperature);
	len = strlen(szTemperature);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'p';
	szBuffer[i++] = ':';
	strcpy(&szBuffer[i], szPressure);
	len = strlen(szPressure);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'h';
	szBuffer[i++] = ':';
	strcpy(&szBuffer[i], szHumidity);
	len = strlen(szHumidity);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'w';
	szBuffer[i++] = ':';
	strcpy(&szBuffer[i], szWindSpeed);
	len = strlen(szWindSpeed);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'r';
	szBuffer[i++] = ':';
	strcpy(&szBuffer[i], szRainfall);
	len = strlen(szRainfall);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i] = 0;

	txstr(szBuffer, txStrLen);
	
	rescheduleTask(TASK_TX, NULL);
}
