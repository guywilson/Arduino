#include <stdint.h>

#include "utils.h"


/******************************************************************************
**
** Converts a floating point number to a null terminated string.
**
** Supports positive floating point numbers up to 429 496 729 and only converts 
** 1 decimal place to the string.
**
******************************************************************************/
int doubleToString(uint8_t * dest, double value)
{
	int				i;
	int				strLen;
	uint32_t		intValue;
	
	intValue = (uint32_t)(value * 10);
	
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

/*
** Supports positive 16-bit integers up to 65535
*/
int uint16ToString(uint8_t * dest, uint16_t value)
{
	int				i;
	int				strLen;

	if (value > 10000) {
		strLen = 5;
	}
	else if (value > 1000) {
		strLen = 4;
	}
	else if (value > 100) {
		strLen = 3;
	}
	else if (value > 10) {
		strLen = 2;
	}
	else if (value >= 1) {
		strLen = 1;
	}
	else {
		strLen = 1;
		dest[0] = '0';
	}

	i = strLen - 1;
	
	while (value > 0) {
		dest[i] = (value % 10) + '0';
		value /= 10;
		
		i--;
	}
	
	dest[strLen] = 0;
	
	return strLen;
}

void uint16ToBinaryString(uint8_t * dest, uint16_t value)
{
	int			i = 15;
	
	while (i >= 0) {
		dest[i] = ((char)(value & 0x0001)) + '0';
		value = value >> 1;
		i--;
	}
	
	dest[16] = 0;
}

/*
** Supports positive 32-bit integers up to 4 294 967 295
*/
int uint32ToString(uint8_t * dest, uint32_t value)
{
	int				i;
	int				strLen;

	if (value > 1000000000) {
		strLen = 10;
	}
	else if (value > 100000000) {
		strLen = 9;
	}
	else if (value > 10000000) {
		strLen = 8;
	}
	else if (value > 1000000) {
		strLen = 7;
	}
	else if (value > 100000) {
		strLen = 6;
	}
	else if (value > 10000) {
		strLen = 5;
	}
	else if (value > 1000) {
		strLen = 4;
	}
	else if (value > 100) {
		strLen = 3;
	}
	else if (value > 10) {
		strLen = 2;
	}
	else if (value >= 1) {
		strLen = 1;
	}
	else {
		strLen = 1;
		dest[0] = '0';
	}

	i = strLen - 1;
	
	while (value > 0) {
		dest[i] = (value % 10) + '0';
		value /= 10;
		
		i--;
	}
	
	dest[strLen] = 0;
	
	return strLen;
}

void uint32ToBinaryString(uint8_t * dest, uint32_t value)
{
	int			i = 31;
	
	while (i >= 0) {
		dest[i] = ((char)(value & 0x00000001)) + '0';
		value = value >> 1;
		i--;
	}
	
	dest[32] = 0;
}
