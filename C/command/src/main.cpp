#include <iostream>
#include <termios.h>
#include <pthread.h>

#include "serialport.h"
#include "serialrx.h"
#include "serialtx.h"
#include "exception.h"
#include "serialstate.h"
#include "cmdthread.h"

#define NUM_VALID_BAUDRATES			9

using namespace std;

static const int baudRates[NUM_VALID_BAUDRATES][2] =
{
	{1200,		B1200},
	{1800,		B1800},
	{2400,		B2400},
	{4800,		B4800},
	{9600,		B9600},
	{19200,		B19200},
	{38400,		B38400},
	{57600,		B57600},
	{115200,	B115200}
};


void showHelp()
{
	int			i;
	
	cout << endl;
	cout << "Weather Station Control Program" << endl << endl;
	cout << "Parameters:" << endl;
	cout << "\t-p <port name>\tSerial port for comms with the weather station" << endl;
	cout << "\t-b <baud rate>\tBaud rate for the serial port, must be one of:" << endl;
	
	for (i = 0;i < NUM_VALID_BAUDRATES;i++) {
		cout << "\t\t" << baudRates[i][0] << endl;
	}
	
	cout << endl;
}


int main(int argc, char * argv[])
{
	int				i;
	int				j;
	int				rtn = 0;
	char	*		pszArg = nullptr;
	char			szPortName[128];
	int				baud = 0;
	int				baudConst = B9600;
	bool			isValidBaud = false;
	SerialState *	pState;
	pthread_t		rxThread;
	pthread_t		txThread;
	pthread_t		windThread;
	pthread_t		rainThread;
	pthread_t		adcThread;
	
	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			pszArg = &argv[i][0];
			
			if (pszArg[0] == '-' || pszArg[0] == '/') {
				i++;
				
				switch (pszArg[1]) {
					case 'p':
						strncpy(szPortName, &argv[i][0], 128);
						break;
						
					case 'b':
						baud = atoi(&argv[i][0]);
						
						for (j = 0;j < NUM_VALID_BAUDRATES;j++) {
							if (baud == baudRates[j][0]) {
								baudConst = baudRates[j][1];
								isValidBaud = true;
								break;
							}
						}
						
						if (!isValidBaud) {
							cout << endl << "Invalid baud rate: " << baud << endl;
							showHelp();
						}
						break;
						
					case '?':
						showHelp();
						break;
						
					default:
						cout << endl << "Unknown argument: " << pszArg[0] << pszArg[1] << endl;
						showHelp();
						break;
				}
			}
			else {
				showHelp();
			}
		}
	}
	else {
		showHelp();
	}
	
	try {
		pState = new SerialState();

		SerialPort & port = SerialPort::getInstance();

		cout << endl << "Opening port [" << szPortName << "] with baud [" << baud << "]." << endl << endl;

		port.configure(
				szPortName, 
				baudConst, 
				parityDisabled, 
				fullDuplex, 
				stopbits1, 
				databits8);
		
		pState->pSerialPort = &port;

		rtn = pthread_create(
				&rxThread, 
				NULL, 
				&rx_thread_func, 
				(void *)pState);

		if (rtn) {
			throw new Exception(
						ERR_THREAD_CREATE, 
						"Error creating thread rx_thread_func.", 
						__FILE__, 
						"-", 
						"main", 
						__LINE__);
		}

		rtn = pthread_create(
				&txThread, 
				NULL, 
				&tx_thread_func, 
				(void *)pState);

		if (rtn) {
			throw new Exception(
						ERR_THREAD_CREATE, 
						"Error creating thread tx_thread_func.", 
						__FILE__, 
						"-", 
						"main", 
						__LINE__);
		}

		rtn = pthread_create(
				&windThread, 
				NULL, 
				&cmd_wind_speed_thread, 
				(void *)pState);

		if (rtn) {
			throw new Exception(
						ERR_THREAD_CREATE, 
						"Error creating thread cmd_wind_speed_thread.", 
						__FILE__, 
						"-", 
						"main", 
						__LINE__);
		}

		rtn = pthread_create(
				&rainThread, 
				NULL, 
				&cmd_rainfall_thread, 
				(void *)pState);

		if (rtn) {
			throw new Exception(
						ERR_THREAD_CREATE, 
						"Error creating thread cmd_rainfall_thread.", 
						__FILE__, 
						"-", 
						"main", 
						__LINE__);
		}

		rtn = pthread_create(
				&adcThread, 
				NULL, 
				&cmd_adc_thread, 
				(void *)pState);

		if (rtn) {
			throw new Exception(
						ERR_THREAD_CREATE, 
						"Error creating thread cmd_adc_thread.", 
						__FILE__, 
						"-", 
						"main", 
						__LINE__);
		}

		string command;
		bool loop = true;

		while (loop) {
			cout << "> ";
			getline(cin, command);

			if (command.length() == 0) {
				continue;
			}

			if (command.compare(0, 4, "exit") == 0 || command.compare(0, 4, "quit") == 0 || command[0] == 'q') {
				loop = false;
			}
		}

		delete pState;
	}
	catch (Exception * e) {
		cout << e->getExceptionString() << endl << endl;
	}
	
	return 0;
}
