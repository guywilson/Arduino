#ifndef _INCL_TEMPLOOKUP
#define _INCL_TEMPLOOKUP

#define TEMP_LOOKUP_BUFFER_SIZE			1024
#define TEMP_INDEX_OFFSET				 409

/******************************************************************************
**
** From ADC inputs linked to a Texas Instruments LM35CAZ temperature sensor
** with a range of -40C to 110C. The +ve and -ve ranges from the sensor go
** to seperate analogue inputs. The sensor output is -400mV to +1100mV but we
** are only interested in the range -40C to 60C (The highest temperate ever 
** recorded on earth is 56.7C in Death Valley, California) so that yields a
** voltage range of -400mv to +600mV, e.g. a range of 1V. We use an 
** implementation amplifier on each of the +ve and -ve inputs with a gain of 
** 5 to yield an input voltage range of -2V to +3V, this equates to an ADC
** value range of -409 to + 614 (a spread of 1023).
**
** We calculate the array offset by subtracting the -ve input from the +ve
** input and adding the offset 409 to give a range of 0 - 1023", e.g.
**
** index = (ADC(+ve) - AD(-ve)) + 409
**
** As the sensor output is linear, the temperature is calculated using the 
** equation of the straight line output graph:
**
** T = ((100 / 1023) * -409) + 0
**
** This is an expensive operation on a microcontroller, hence we calcuate this 
** upfront and store in flash ROM.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
static const char * const tempLookup[TEMP_LOOKUP_BUFFER_SIZE] = 
{
	"-39.98",
	"-39.88",
	"-39.78",
	"-39.69",
	"-39.59",
	"-39.49",
	"-39.39",
	"-39.30",
	"-39.20",
	"-39.10",
	"-39.00",
	"-38.91",
	"-38.81",
	"-38.71",
	"-38.61",
	"-38.51",
	"-38.42",
	"-38.32",
	"-38.22",
	"-38.12",
	"-38.03",
	"-37.93",
	"-37.83",
	"-37.73",
	"-37.63",
	"-37.54",
	"-37.44",
	"-37.34",
	"-37.24",
	"-37.15",
	"-37.05",
	"-36.95",
	"-36.85",
	"-36.75",
	"-36.66",
	"-36.56",
	"-36.46",
	"-36.36",
	"-36.27",
	"-36.17",
	"-36.07",
	"-35.97",
	"-35.87",
	"-35.78",
	"-35.68",
	"-35.58",
	"-35.48",
	"-35.39",
	"-35.29",
	"-35.19",
	"-35.09",
	"-35.00",
	"-34.90",
	"-34.80",
	"-34.70",
	"-34.60",
	"-34.51",
	"-34.41",
	"-34.31",
	"-34.21",
	"-34.12",
	"-34.02",
	"-33.92",
	"-33.82",
	"-33.72",
	"-33.63",
	"-33.53",
	"-33.43",
	"-33.33",
	"-33.24",
	"-33.14",
	"-33.04",
	"-32.94",
	"-32.84",
	"-32.75",
	"-32.65",
	"-32.55",
	"-32.45",
	"-32.36",
	"-32.26",
	"-32.16",
	"-32.06",
	"-31.96",
	"-31.87",
	"-31.77",
	"-31.67",
	"-31.57",
	"-31.48",
	"-31.38",
	"-31.28",
	"-31.18",
	"-31.09",
	"-30.99",
	"-30.89",
	"-30.79",
	"-30.69",
	"-30.60",
	"-30.50",
	"-30.40",
	"-30.30",
	"-30.21",
	"-30.11",
	"-30.01",
	"-29.91",
	"-29.81",
	"-29.72",
	"-29.62",
	"-29.52",
	"-29.42",
	"-29.33",
	"-29.23",
	"-29.13",
	"-29.03",
	"-28.93",
	"-28.84",
	"-28.74",
	"-28.64",
	"-28.54",
	"-28.45",
	"-28.35",
	"-28.25",
	"-28.15",
	"-28.05",
	"-27.96",
	"-27.86",
	"-27.76",
	"-27.66",
	"-27.57",
	"-27.47",
	"-27.37",
	"-27.27",
	"-27.17",
	"-27.08",
	"-26.98",
	"-26.88",
	"-26.78",
	"-26.69",
	"-26.59",
	"-26.49",
	"-26.39",
	"-26.30",
	"-26.20",
	"-26.10",
	"-26.00",
	"-25.90",
	"-25.81",
	"-25.71",
	"-25.61",
	"-25.51",
	"-25.42",
	"-25.32",
	"-25.22",
	"-25.12",
	"-25.02",
	"-24.93",
	"-24.83",
	"-24.73",
	"-24.63",
	"-24.54",
	"-24.44",
	"-24.34",
	"-24.24",
	"-24.14",
	"-24.05",
	"-23.95",
	"-23.85",
	"-23.75",
	"-23.66",
	"-23.56",
	"-23.46",
	"-23.36",
	"-23.26",
	"-23.17",
	"-23.07",
	"-22.97",
	"-22.87",
	"-22.78",
	"-22.68",
	"-22.58",
	"-22.48",
	"-22.39",
	"-22.29",
	"-22.19",
	"-22.09",
	"-21.99",
	"-21.90",
	"-21.80",
	"-21.70",
	"-21.60",
	"-21.51",
	"-21.41",
	"-21.31",
	"-21.21",
	"-21.11",
	"-21.02",
	"-20.92",
	"-20.82",
	"-20.72",
	"-20.63",
	"-20.53",
	"-20.43",
	"-20.33",
	"-20.23",
	"-20.14",
	"-20.04",
	"-19.94",
	"-19.84",
	"-19.75",
	"-19.65",
	"-19.55",
	"-19.45",
	"-19.35",
	"-19.26",
	"-19.16",
	"-19.06",
	"-18.96",
	"-18.87",
	"-18.77",
	"-18.67",
	"-18.57",
	"-18.48",
	"-18.38",
	"-18.28",
	"-18.18",
	"-18.08",
	"-17.99",
	"-17.89",
	"-17.79",
	"-17.69",
	"-17.60",
	"-17.50",
	"-17.40",
	"-17.30",
	"-17.20",
	"-17.11",
	"-17.01",
	"-16.91",
	"-16.81",
	"-16.72",
	"-16.62",
	"-16.52",
	"-16.42",
	"-16.32",
	"-16.23",
	"-16.13",
	"-16.03",
	"-15.93",
	"-15.84",
	"-15.74",
	"-15.64",
	"-15.54",
	"-15.44",
	"-15.35",
	"-15.25",
	"-15.15",
	"-15.05",
	"-14.96",
	"-14.86",
	"-14.76",
	"-14.66",
	"-14.57",
	"-14.47",
	"-14.37",
	"-14.27",
	"-14.17",
	"-14.08",
	"-13.98",
	"-13.88",
	"-13.78",
	"-13.69",
	"-13.59",
	"-13.49",
	"-13.39",
	"-13.29",
	"-13.20",
	"-13.10",
	"-13.00",
	"-12.90",
	"-12.81",
	"-12.71",
	"-12.61",
	"-12.51",
	"-12.41",
	"-12.32",
	"-12.22",
	"-12.12",
	"-12.02",
	"-11.93",
	"-11.83",
	"-11.73",
	"-11.63",
	"-11.53",
	"-11.44",
	"-11.34",
	"-11.24",
	"-11.14",
	"-11.05",
	"-10.95",
	"-10.85",
	"-10.75",
	"-10.65",
	"-10.56",
	"-10.46",
	"-10.36",
	"-10.26",
	"-10.17",
	"-10.07",
	"-9.97",
	"-9.87",
	"-9.78",
	"-9.68",
	"-9.58",
	"-9.48",
	"-9.38",
	"-9.29",
	"-9.19",
	"-9.09",
	"-8.99",
	"-8.90",
	"-8.80",
	"-8.70",
	"-8.60",
	"-8.50",
	"-8.41",
	"-8.31",
	"-8.21",
	"-8.11",
	"-8.02",
	"-7.92",
	"-7.82",
	"-7.72",
	"-7.62",
	"-7.53",
	"-7.43",
	"-7.33",
	"-7.23",
	"-7.14",
	"-7.04",
	"-6.94",
	"-6.84",
	"-6.74",
	"-6.65",
	"-6.55",
	"-6.45",
	"-6.35",
	"-6.26",
	"-6.16",
	"-6.06",
	"-5.96",
	"-5.87",
	"-5.77",
	"-5.67",
	"-5.57",
	"-5.47",
	"-5.38",
	"-5.28",
	"-5.18",
	"-5.08",
	"-4.99",
	"-4.89",
	"-4.79",
	"-4.69",
	"-4.59",
	"-4.50",
	"-4.40",
	"-4.30",
	"-4.20",
	"-4.11",
	"-4.01",
	"-3.91",
	"-3.81",
	"-3.71",
	"-3.62",
	"-3.52",
	"-3.42",
	"-3.32",
	"-3.23",
	"-3.13",
	"-3.03",
	"-2.93",
	"-2.83",
	"-2.74",
	"-2.64",
	"-2.54",
	"-2.44",
	"-2.35",
	"-2.25",
	"-2.15",
	"-2.05",
	"-1.96",
	"-1.86",
	"-1.76",
	"-1.66",
	"-1.56",
	"-1.47",
	"-1.37",
	"-1.27",
	"-1.17",
	"-1.08",
	"-0.98",
	"-0.88",
	"-0.78",
	"-0.68",
	"-0.59",
	"-0.49",
	"-0.39",
	"-0.29",
	"-0.20",
	"-0.10",
	"0.00",
	"0.10",
	"0.20",
	"0.29",
	"0.39",
	"0.49",
	"0.59",
	"0.68",
	"0.78",
	"0.88",
	"0.98",
	"1.08",
	"1.17",
	"1.27",
	"1.37",
	"1.47",
	"1.56",
	"1.66",
	"1.76",
	"1.86",
	"1.96",
	"2.05",
	"2.15",
	"2.25",
	"2.35",
	"2.44",
	"2.54",
	"2.64",
	"2.74",
	"2.83",
	"2.93",
	"3.03",
	"3.13",
	"3.23",
	"3.32",
	"3.42",
	"3.52",
	"3.62",
	"3.71",
	"3.81",
	"3.91",
	"4.01",
	"4.11",
	"4.20",
	"4.30",
	"4.40",
	"4.50",
	"4.59",
	"4.69",
	"4.79",
	"4.89",
	"4.99",
	"5.08",
	"5.18",
	"5.28",
	"5.38",
	"5.47",
	"5.57",
	"5.67",
	"5.77",
	"5.87",
	"5.96",
	"6.06",
	"6.16",
	"6.26",
	"6.35",
	"6.45",
	"6.55",
	"6.65",
	"6.74",
	"6.84",
	"6.94",
	"7.04",
	"7.14",
	"7.23",
	"7.33",
	"7.43",
	"7.53",
	"7.62",
	"7.72",
	"7.82",
	"7.92",
	"8.02",
	"8.11",
	"8.21",
	"8.31",
	"8.41",
	"8.50",
	"8.60",
	"8.70",
	"8.80",
	"8.90",
	"8.99",
	"9.09",
	"9.19",
	"9.29",
	"9.38",
	"9.48",
	"9.58",
	"9.68",
	"9.78",
	"9.87",
	"9.97",
	"10.07",
	"10.17",
	"10.26",
	"10.36",
	"10.46",
	"10.56",
	"10.65",
	"10.75",
	"10.85",
	"10.95",
	"11.05",
	"11.14",
	"11.24",
	"11.34",
	"11.44",
	"11.53",
	"11.63",
	"11.73",
	"11.83",
	"11.93",
	"12.02",
	"12.12",
	"12.22",
	"12.32",
	"12.41",
	"12.51",
	"12.61",
	"12.71",
	"12.81",
	"12.90",
	"13.00",
	"13.10",
	"13.20",
	"13.29",
	"13.39",
	"13.49",
	"13.59",
	"13.69",
	"13.78",
	"13.88",
	"13.98",
	"14.08",
	"14.17",
	"14.27",
	"14.37",
	"14.47",
	"14.57",
	"14.66",
	"14.76",
	"14.86",
	"14.96",
	"15.05",
	"15.15",
	"15.25",
	"15.35",
	"15.44",
	"15.54",
	"15.64",
	"15.74",
	"15.84",
	"15.93",
	"16.03",
	"16.13",
	"16.23",
	"16.32",
	"16.42",
	"16.52",
	"16.62",
	"16.72",
	"16.81",
	"16.91",
	"17.01",
	"17.11",
	"17.20",
	"17.30",
	"17.40",
	"17.50",
	"17.60",
	"17.69",
	"17.79",
	"17.89",
	"17.99",
	"18.08",
	"18.18",
	"18.28",
	"18.38",
	"18.48",
	"18.57",
	"18.67",
	"18.77",
	"18.87",
	"18.96",
	"19.06",
	"19.16",
	"19.26",
	"19.35",
	"19.45",
	"19.55",
	"19.65",
	"19.75",
	"19.84",
	"19.94",
	"20.04",
	"20.14",
	"20.23",
	"20.33",
	"20.43",
	"20.53",
	"20.63",
	"20.72",
	"20.82",
	"20.92",
	"21.02",
	"21.11",
	"21.21",
	"21.31",
	"21.41",
	"21.51",
	"21.60",
	"21.70",
	"21.80",
	"21.90",
	"21.99",
	"22.09",
	"22.19",
	"22.29",
	"22.39",
	"22.48",
	"22.58",
	"22.68",
	"22.78",
	"22.87",
	"22.97",
	"23.07",
	"23.17",
	"23.26",
	"23.36",
	"23.46",
	"23.56",
	"23.66",
	"23.75",
	"23.85",
	"23.95",
	"24.05",
	"24.14",
	"24.24",
	"24.34",
	"24.44",
	"24.54",
	"24.63",
	"24.73",
	"24.83",
	"24.93",
	"25.02",
	"25.12",
	"25.22",
	"25.32",
	"25.42",
	"25.51",
	"25.61",
	"25.71",
	"25.81",
	"25.90",
	"26.00",
	"26.10",
	"26.20",
	"26.30",
	"26.39",
	"26.49",
	"26.59",
	"26.69",
	"26.78",
	"26.88",
	"26.98",
	"27.08",
	"27.17",
	"27.27",
	"27.37",
	"27.47",
	"27.57",
	"27.66",
	"27.76",
	"27.86",
	"27.96",
	"28.05",
	"28.15",
	"28.25",
	"28.35",
	"28.45",
	"28.54",
	"28.64",
	"28.74",
	"28.84",
	"28.93",
	"29.03",
	"29.13",
	"29.23",
	"29.33",
	"29.42",
	"29.52",
	"29.62",
	"29.72",
	"29.81",
	"29.91",
	"30.01",
	"30.11",
	"30.21",
	"30.30",
	"30.40",
	"30.50",
	"30.60",
	"30.69",
	"30.79",
	"30.89",
	"30.99",
	"31.09",
	"31.18",
	"31.28",
	"31.38",
	"31.48",
	"31.57",
	"31.67",
	"31.77",
	"31.87",
	"31.96",
	"32.06",
	"32.16",
	"32.26",
	"32.36",
	"32.45",
	"32.55",
	"32.65",
	"32.75",
	"32.84",
	"32.94",
	"33.04",
	"33.14",
	"33.24",
	"33.33",
	"33.43",
	"33.53",
	"33.63",
	"33.72",
	"33.82",
	"33.92",
	"34.02",
	"34.12",
	"34.21",
	"34.31",
	"34.41",
	"34.51",
	"34.60",
	"34.70",
	"34.80",
	"34.90",
	"35.00",
	"35.09",
	"35.19",
	"35.29",
	"35.39",
	"35.48",
	"35.58",
	"35.68",
	"35.78",
	"35.87",
	"35.97",
	"36.07",
	"36.17",
	"36.27",
	"36.36",
	"36.46",
	"36.56",
	"36.66",
	"36.75",
	"36.85",
	"36.95",
	"37.05",
	"37.15",
	"37.24",
	"37.34",
	"37.44",
	"37.54",
	"37.63",
	"37.73",
	"37.83",
	"37.93",
	"38.03",
	"38.12",
	"38.22",
	"38.32",
	"38.42",
	"38.51",
	"38.61",
	"38.71",
	"38.81",
	"38.91",
	"39.00",
	"39.10",
	"39.20",
	"39.30",
	"39.39",
	"39.49",
	"39.59",
	"39.69",
	"39.78",
	"39.88",
	"39.98",
	"40.08",
	"40.18",
	"40.27",
	"40.37",
	"40.47",
	"40.57",
	"40.66",
	"40.76",
	"40.86",
	"40.96",
	"41.06",
	"41.15",
	"41.25",
	"41.35",
	"41.45",
	"41.54",
	"41.64",
	"41.74",
	"41.84",
	"41.94",
	"42.03",
	"42.13",
	"42.23",
	"42.33",
	"42.42",
	"42.52",
	"42.62",
	"42.72",
	"42.82",
	"42.91",
	"43.01",
	"43.11",
	"43.21",
	"43.30",
	"43.40",
	"43.50",
	"43.60",
	"43.70",
	"43.79",
	"43.89",
	"43.99",
	"44.09",
	"44.18",
	"44.28",
	"44.38",
	"44.48",
	"44.57",
	"44.67",
	"44.77",
	"44.87",
	"44.97",
	"45.06",
	"45.16",
	"45.26",
	"45.36",
	"45.45",
	"45.55",
	"45.65",
	"45.75",
	"45.85",
	"45.94",
	"46.04",
	"46.14",
	"46.24",
	"46.33",
	"46.43",
	"46.53",
	"46.63",
	"46.73",
	"46.82",
	"46.92",
	"47.02",
	"47.12",
	"47.21",
	"47.31",
	"47.41",
	"47.51",
	"47.61",
	"47.70",
	"47.80",
	"47.90",
	"48.00",
	"48.09",
	"48.19",
	"48.29",
	"48.39",
	"48.48",
	"48.58",
	"48.68",
	"48.78",
	"48.88",
	"48.97",
	"49.07",
	"49.17",
	"49.27",
	"49.36",
	"49.46",
	"49.56",
	"49.66",
	"49.76",
	"49.85",
	"49.95",
	"50.05",
	"50.15",
	"50.24",
	"50.34",
	"50.44",
	"50.54",
	"50.64",
	"50.73",
	"50.83",
	"50.93",
	"51.03",
	"51.12",
	"51.22",
	"51.32",
	"51.42",
	"51.52",
	"51.61",
	"51.71",
	"51.81",
	"51.91",
	"52.00",
	"52.10",
	"52.20",
	"52.30",
	"52.39",
	"52.49",
	"52.59",
	"52.69",
	"52.79",
	"52.88",
	"52.98",
	"53.08",
	"53.18",
	"53.27",
	"53.37",
	"53.47",
	"53.57",
	"53.67",
	"53.76",
	"53.86",
	"53.96",
	"54.06",
	"54.15",
	"54.25",
	"54.35",
	"54.45",
	"54.55",
	"54.64",
	"54.74",
	"54.84",
	"54.94",
	"55.03",
	"55.13",
	"55.23",
	"55.33",
	"55.43",
	"55.52",
	"55.62",
	"55.72",
	"55.82",
	"55.91",
	"56.01",
	"56.11",
	"56.21",
	"56.30",
	"56.40",
	"56.50",
	"56.60",
	"56.70",
	"56.79",
	"56.89",
	"56.99",
	"57.09",
	"57.18",
	"57.28",
	"57.38",
	"57.48",
	"57.58",
	"57.67",
	"57.77",
	"57.87",
	"57.97",
	"58.06",
	"58.16",
	"58.26",
	"58.36",
	"58.46",
	"58.55",
	"58.65",
	"58.75",
	"58.85",
	"58.94",
	"59.04",
	"59.14",
	"59.24",
	"59.34",
	"59.43",
	"59.53",
	"59.63",
	"59.73",
	"59.82",
	"59.92",
	"60.02"
};

#endif