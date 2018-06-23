#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "humiditylookup.h"
#include "mbarlookup.h"
#include "templookup.h"
#include "kphlookup.h"
#include "rainfall.h"

int doubleToString(char * dest, double value)
{
	int				i;
	int				strLen;
	uint32_t		intValue;
	
	intValue = (uint32_t)(value * 100);
	
	if (intValue > 1000000000) {
		strLen = 11;
	}
	else if (intValue > 100000000) {
		strLen = 10;
	}
	else if (intValue > 10000000) {
		strLen = 9;
	}
	else if (intValue > 1000000) {
		strLen = 8;
	}
	else if (intValue > 100000) {
		strLen = 7;
	}
	else if (intValue > 10000) {
		strLen = 6;
	}
	else if (intValue > 1000) {
		strLen = 5;
	}
	else if (intValue > 100) {
		strLen = 4;
	}
	else if (intValue > 10) {
		strLen = 3;
	}
	else if (intValue >= 1) {
		strLen = 3;
		dest[0] = '0';
		dest[1] = '.';
	}
	else {
		strLen = 3;
		dest[0] = '0';
		dest[1] = '.';
		dest[2] = '0';
	}

	i = strLen - 1;
	
	while (intValue > 0) {
		if (i == strLen - 2) {
			dest[i] = '.';
		}
		else {
			dest[i] = (intValue % 10) + '0';
			intValue /= 10;
		}
		
		i--;
	}
	
	dest[strLen] = 0;
	
	return strLen;
}

void TxTest(void)
{
	char		szBuffer[64];
	char		szTemperature[8];
	char		szPressure[8];
	char		szHumidity[8];
	int			len;
	int			txStrLen = 0;
	int			i = 0;

	strcpy(szTemperature, tempLookup[100]);
	strcpy(szPressure, mbarLookup[100]);
	strcpy(szHumidity, humidityLookup[100]);

	printf("Temp = %s\n", szTemperature);
	printf("Pressure = %s\n", szPressure);
	printf("Humidity = %s\n", szHumidity);
	
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
	len = doubleToString(&szBuffer[i], kphLookup[100]);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'r';
	szBuffer[i++] = ':';
	len = doubleToString(&szBuffer[i], rainfallLookup[100]);
	szBuffer[i + len] = '>';
	i += len + 1;
	txStrLen += len + 4;
	
	szBuffer[i] = 0;

	printf("TX buffer (len [%d]) [%s]\n", txStrLen, szBuffer);
}

int main(void)
{
	int		length;
	char	buf[64];
	
	length = doubleToString(buf, 12.125);
	
	printf("12.125 as string [%s] with length %d\n\n", buf, length);
	
	TxTest();
	
	return 0;
}
