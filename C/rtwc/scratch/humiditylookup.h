#ifndef _INCL_HUMIDITYLOOKUP
#define _INCL_HUMIDITYLOOKUP

#define HUMIDITY_LOOKUP_BUFFER_SIZE		642

/*
** Minimum sensor output corresponding to 0% RH is 800mv. The minimum
** ADC value at 800mv is 163", hence we subtract the offset defined here
** from the value before using as the index into the array below...
*/
#define ADC_HUMIDITY_OFFSET				163

/******************************************************************************
**
** From an ADC input linked to a Honeywell HIH-4000 humidity sensor
** with a range of 0 - 100% relative humidity.
**
** Define the relative humidity (RH) for ADC values between 163 - 1675
** correspoding to sensor voltages of 800mV to 3.9V which are the lower and
** upper ranges from the sensor for 0% RH to 100% RH.
**
** Vo = Vs(0.0062 * RH + 0.16)
**
** RH = ((ADC / 1023) - 0.16) / 0.0062
**
** This is an expensive operation on a microcontroller", hence we calcuate this 
** upfront and store in flash ROM.
**
** This array of const values uses the PROGMEM modifier", a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array", code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
static const char * const humidityLookup[HUMIDITY_LOOKUP_BUFFER_SIZE] = 
{
	"0.00",
	"0.05",
	"0.21",
	"0.37",
	"0.52",
	"0.68",
	"0.84",
	"1.00",
	"1.15",
	"1.31",
	"1.47",
	"1.63",
	"1.78",
	"1.94",
	"2.10",
	"2.26",
	"2.42",
	"2.57",
	"2.73",
	"2.89",
	"3.05",
	"3.20",
	"3.36",
	"3.52",
	"3.68",
	"3.83",
	"3.99",
	"4.15",
	"4.31",
	"4.47",
	"4.62",
	"4.78",
	"4.94",
	"5.10",
	"5.25",
	"5.41",
	"5.57",
	"5.73",
	"5.88",
	"6.04",
	"6.20",
	"6.36",
	"6.51",
	"6.67",
	"6.83",
	"6.99",
	"7.15",
	"7.30",
	"7.46",
	"7.62",
	"7.78",
	"7.93",
	"8.09",
	"8.25",
	"8.41",
	"8.56",
	"8.72",
	"8.88",
	"9.04",
	"9.19",
	"9.35",
	"9.51",
	"9.67",
	"9.83",
	"9.98",
	"10.14",
	"10.30",
	"10.46",
	"10.61",
	"10.77",
	"10.93",
	"11.09",
	"11.24",
	"11.40",
	"11.56",
	"11.72",
	"11.88",
	"12.03",
	"12.19",
	"12.35",
	"12.51",
	"12.66",
	"12.82",
	"12.98",
	"13.14",
	"13.29",
	"13.45",
	"13.61",
	"13.77",
	"13.92",
	"14.08",
	"14.24",
	"14.40",
	"14.56",
	"14.71",
	"14.87",
	"15.03",
	"15.19",
	"15.34",
	"15.50",
	"15.66",
	"15.82",
	"15.97",
	"16.13",
	"16.29",
	"16.45",
	"16.61",
	"16.76",
	"16.92",
	"17.08",
	"17.24",
	"17.39",
	"17.55",
	"17.71",
	"17.87",
	"18.02",
	"18.18",
	"18.34",
	"18.50",
	"18.65",
	"18.81",
	"18.97",
	"19.13",
	"19.29",
	"19.44",
	"19.60",
	"19.76",
	"19.92",
	"20.07",
	"20.23",
	"20.39",
	"20.55",
	"20.70",
	"20.86",
	"21.02",
	"21.18",
	"21.34",
	"21.49",
	"21.65",
	"21.81",
	"21.97",
	"22.12",
	"22.28",
	"22.44",
	"22.60",
	"22.75",
	"22.91",
	"23.07",
	"23.23",
	"23.38",
	"23.54",
	"23.70",
	"23.86",
	"24.02",
	"24.17",
	"24.33",
	"24.49",
	"24.65",
	"24.80",
	"24.96",
	"25.12",
	"25.28",
	"25.43",
	"25.59",
	"25.75",
	"25.91",
	"26.07",
	"26.22",
	"26.38",
	"26.54",
	"26.70",
	"26.85",
	"27.01",
	"27.17",
	"27.33",
	"27.48",
	"27.64",
	"27.80",
	"27.96",
	"28.11",
	"28.27",
	"28.43",
	"28.59",
	"28.75",
	"28.90",
	"29.06",
	"29.22",
	"29.38",
	"29.53",
	"29.69",
	"29.85",
	"30.01",
	"30.16",
	"30.32",
	"30.48",
	"30.64",
	"30.79",
	"30.95",
	"31.11",
	"31.27",
	"31.43",
	"31.58",
	"31.74",
	"31.90",
	"32.06",
	"32.21",
	"32.37",
	"32.53",
	"32.69",
	"32.84",
	"33.00",
	"33.16",
	"33.32",
	"33.48",
	"33.63",
	"33.79",
	"33.95",
	"34.11",
	"34.26",
	"34.42",
	"34.58",
	"34.74",
	"34.89",
	"35.05",
	"35.21",
	"35.37",
	"35.52",
	"35.68",
	"35.84",
	"36.00",
	"36.16",
	"36.31",
	"36.47",
	"36.63",
	"36.79",
	"36.94",
	"37.10",
	"37.26",
	"37.42",
	"37.57",
	"37.73",
	"37.89",
	"38.05",
	"38.21",
	"38.36",
	"38.52",
	"38.68",
	"38.84",
	"38.99",
	"39.15",
	"39.31",
	"39.47",
	"39.62",
	"39.78",
	"39.94",
	"40.10",
	"40.25",
	"40.41",
	"40.57",
	"40.73",
	"40.89",
	"41.04",
	"41.20",
	"41.36",
	"41.52",
	"41.67",
	"41.83",
	"41.99",
	"42.15",
	"42.30",
	"42.46",
	"42.62",
	"42.78",
	"42.94",
	"43.09",
	"43.25",
	"43.41",
	"43.57",
	"43.72",
	"43.88",
	"44.04",
	"44.20",
	"44.35",
	"44.51",
	"44.67",
	"44.83",
	"44.98",
	"45.14",
	"45.30",
	"45.46",
	"45.62",
	"45.77",
	"45.93",
	"46.09",
	"46.25",
	"46.40",
	"46.56",
	"46.72",
	"46.88",
	"47.03",
	"47.19",
	"47.35",
	"47.51",
	"47.66",
	"47.82",
	"47.98",
	"48.14",
	"48.30",
	"48.45",
	"48.61",
	"48.77",
	"48.93",
	"49.08",
	"49.24",
	"49.40",
	"49.56",
	"49.71",
	"49.87",
	"50.03",
	"50.19",
	"50.35",
	"50.50",
	"50.66",
	"50.82",
	"50.98",
	"51.13",
	"51.29",
	"51.45",
	"51.61",
	"51.76",
	"51.92",
	"52.08",
	"52.24",
	"52.39",
	"52.55",
	"52.71",
	"52.87",
	"53.03",
	"53.18",
	"53.34",
	"53.50",
	"53.66",
	"53.81",
	"53.97",
	"54.13",
	"54.29",
	"54.44",
	"54.60",
	"54.76",
	"54.92",
	"55.08",
	"55.23",
	"55.39",
	"55.55",
	"55.71",
	"55.86",
	"56.02",
	"56.18",
	"56.34",
	"56.49",
	"56.65",
	"56.81",
	"56.97",
	"57.12",
	"57.28",
	"57.44",
	"57.60",
	"57.76",
	"57.91",
	"58.07",
	"58.23",
	"58.39",
	"58.54",
	"58.70",
	"58.86",
	"59.02",
	"59.17",
	"59.33",
	"59.49",
	"59.65",
	"59.81",
	"59.96",
	"60.12",
	"60.28",
	"60.44",
	"60.59",
	"60.75",
	"60.91",
	"61.07",
	"61.22",
	"61.38",
	"61.54",
	"61.70",
	"61.85",
	"62.01",
	"62.17",
	"62.33",
	"62.49",
	"62.64",
	"62.80",
	"62.96",
	"63.12",
	"63.27",
	"63.43",
	"63.59",
	"63.75",
	"63.90",
	"64.06",
	"64.22",
	"64.38",
	"64.54",
	"64.69",
	"64.85",
	"65.01",
	"65.17",
	"65.32",
	"65.48",
	"65.64",
	"65.80",
	"65.95",
	"66.11",
	"66.27",
	"66.43",
	"66.58",
	"66.74",
	"66.90",
	"67.06",
	"67.22",
	"67.37",
	"67.53",
	"67.69",
	"67.85",
	"68.00",
	"68.16",
	"68.32",
	"68.48",
	"68.63",
	"68.79",
	"68.95",
	"69.11",
	"69.26",
	"69.42",
	"69.58",
	"69.74",
	"69.90",
	"70.05",
	"70.21",
	"70.37",
	"70.53",
	"70.68",
	"70.84",
	"71.00",
	"71.16",
	"71.31",
	"71.47",
	"71.63",
	"71.79",
	"71.95",
	"72.10",
	"72.26",
	"72.42",
	"72.58",
	"72.73",
	"72.89",
	"73.05",
	"73.21",
	"73.36",
	"73.52",
	"73.68",
	"73.84",
	"73.99",
	"74.15",
	"74.31",
	"74.47",
	"74.63",
	"74.78",
	"74.94",
	"75.10",
	"75.26",
	"75.41",
	"75.57",
	"75.73",
	"75.89",
	"76.04",
	"76.20",
	"76.36",
	"76.52",
	"76.68",
	"76.83",
	"76.99",
	"77.15",
	"77.31",
	"77.46",
	"77.62",
	"77.78",
	"77.94",
	"78.09",
	"78.25",
	"78.41",
	"78.57",
	"78.72",
	"78.88",
	"79.04",
	"79.20",
	"79.36",
	"79.51",
	"79.67",
	"79.83",
	"79.99",
	"80.14",
	"80.30",
	"80.46",
	"80.62",
	"80.77",
	"80.93",
	"81.09",
	"81.25",
	"81.41",
	"81.56",
	"81.72",
	"81.88",
	"82.04",
	"82.19",
	"82.35",
	"82.51",
	"82.67",
	"82.82",
	"82.98",
	"83.14",
	"83.30",
	"83.45",
	"83.61",
	"83.77",
	"83.93",
	"84.09",
	"84.24",
	"84.40",
	"84.56",
	"84.72",
	"84.87",
	"85.03",
	"85.19",
	"85.35",
	"85.50",
	"85.66",
	"85.82",
	"85.98",
	"86.14",
	"86.29",
	"86.45",
	"86.61",
	"86.77",
	"86.92",
	"87.08",
	"87.24",
	"87.40",
	"87.55",
	"87.71",
	"87.87",
	"88.03",
	"88.18",
	"88.34",
	"88.50",
	"88.66",
	"88.82",
	"88.97",
	"89.13",
	"89.29",
	"89.45",
	"89.60",
	"89.76",
	"89.92",
	"90.08",
	"90.23",
	"90.39",
	"90.55",
	"90.71",
	"90.86",
	"91.02",
	"91.18",
	"91.34",
	"91.50",
	"91.65",
	"91.81",
	"91.97",
	"92.13",
	"92.28",
	"92.44",
	"92.60",
	"92.76",
	"92.91",
	"93.07",
	"93.23",
	"93.39",
	"93.55",
	"93.70",
	"93.86",
	"94.02",
	"94.18",
	"94.33",
	"94.49",
	"94.65",
	"94.81",
	"94.96",
	"95.12",
	"95.28",
	"95.44",
	"95.59",
	"95.75",
	"95.91",
	"96.07",
	"96.23",
	"96.38",
	"96.54",
	"96.70",
	"96.86",
	"97.01",
	"97.17",
	"97.33",
	"97.49",
	"97.64",
	"97.80",
	"97.96",
	"98.12",
	"98.28",
	"98.43",
	"98.59",
	"98.75",
	"98.91",
	"99.06",
	"99.22",
	"99.38",
	"99.54",
	"99.69",
	"99.85",
	"100.01",
	"100.17",
	"100.32",
	"100.48",
	"100.64",
	"100.80",
	"100.96"
};

#endif