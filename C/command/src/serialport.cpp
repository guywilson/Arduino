#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "serialport.h"
#include "exception.h"

void SerialPort::setRTS()
{
	int			status;

	if (isHalfDuplex) {
		if (ioctl(fd, TIOCMGET, &status) == -1) {
			throw new Exception(
						ERR_IOCTL, 
						"Error setting IOCTL.", 
						__FILE__, 
						"SerialPort", 
						"setRTS()", 
						__LINE__);
		}

		status |= TIOCM_RTS;

		if (ioctl(fd, TIOCMSET, &status) == -1) {
			throw new Exception(
						ERR_IOCTL, 
						"Error setting IOCTL.", 
						__FILE__, 
						"SerialPort", 
						"setRTS()", 
						__LINE__);
		}
	}
}

void SerialPort::clearRTS()
{
	int			status;

	if (isHalfDuplex) {
		if (ioctl(fd, TIOCMGET, &status) == -1) {
			throw new Exception(
						ERR_IOCTL, 
						"Error setting IOCTL.", 
						__FILE__, 
						"SerialPort", 
						"clearRTS()", 
						__LINE__);
		}

		status &= ~TIOCM_RTS;

		if (ioctl(fd, TIOCMSET, &status) == -1) {
			throw new Exception(
						ERR_IOCTL, 
						"Error setting IOCTL.", 
						__FILE__, 
						"SerialPort", 
						"clearRTS()", 
						__LINE__);
		}
	}
}

void SerialPort::configure(
					char *		pszPortName, 
					int 		baud, 
					Parity 		parity, 
					Duplex 		duplex, 
					StopBits 	stopBits, 
					DataBits 	dataBits)
{
	strncpy(this->szPortName, pszPortName, 256);
	
	this->baud		= baud;
	this->parity 	= parity;
	this->duplex 	= duplex;
	this->stopBits 	= stopBits;
	this->dataBits 	= dataBits;
	
	this->isConfigured = true;
}

void SerialPort::openPort(bool wait)
{
	int flags = O_RDWR | O_NOCTTY;
	
	if (!isConfigured) {
		throw new Exception(
					ERR_OPEN_PORT, 
					"Port not configured.", 
					__FILE__, 
					"SerialPort", 
					"openPort()", 
					__LINE__);
	}
	
	if (!wait) {
		flags |= O_NDELAY;
	}
	
	this->fd = open(this->szPortName, flags);
	
	if (this->fd < 0) {
		throw new Exception(
					ERR_OPEN_PORT, 
					"Error opening port.", 
					__FILE__, 
					"SerialPort", 
					"openPort()", 
					__LINE__);
	}
	
	_setPortParams();
}

void SerialPort::_setPortParams()
{
	struct termios			SerialPortSettings;

	tcgetattr(fd, &SerialPortSettings);

	cfsetispeed(&SerialPortSettings, baud);
	cfsetospeed(&SerialPortSettings, baud);

	if (parity == parityEnabled) {
		SerialPortSettings.c_cflag |= PARENB;
	}
	else {
		SerialPortSettings.c_cflag &= ~PARENB;
	}
	
	if (stopBits == stopbits1) {
		SerialPortSettings.c_cflag &= ~CSTOPB;
	}
	else {
		SerialPortSettings.c_cflag |= CSTOPB;
	}
	
	SerialPortSettings.c_cflag &= ~CSIZE;

	if (dataBits == databits5) {
		SerialPortSettings.c_cflag |=  CS5;
	}
	else if (dataBits == databits6) {
		SerialPortSettings.c_cflag |=  CS6;
	}
	else if (dataBits == databits7) {
		SerialPortSettings.c_cflag |=  CS7;
	}
	else {
		SerialPortSettings.c_cflag |=  CS8;
	}

	SerialPortSettings.c_oflag &= ~OPOST;	/*No Output Processing*/
	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	
	if (duplex == halfDuplex) {
		this->isHalfDuplex = true;
		SerialPortSettings.c_cflag |= CRTSCTS;
		SerialPortSettings.c_cflag |= CLOCAL;
	}
	else {
		this->isHalfDuplex = false;
		SerialPortSettings.c_cflag &= ~CRTSCTS;
		SerialPortSettings.c_cflag |= CREAD | CLOCAL;
	}

	SerialPortSettings.c_cc[VMIN]  = 10; /* Read 10 characters */  
	SerialPortSettings.c_cc[VTIME] = 50;  /* Wait indefinitely   */
	
	if ((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) {
		throw new Exception(
					ERR_TERMIOS, 
					"Error setting port attributes.", 
					__FILE__, 
					"SerialPort", 
					"openPort()", 
					__LINE__);
	}
}

void SerialPort::closePort()
{
	close(fd);
}

void SerialPort::tx(byte data)
{
	int		wlen;
	
	openPort(false);
	
	setRTS();
	
	wlen = write(fd, &data, 1);
	
	clearRTS();

	closePort();
	
	if (errno) {
		throw new Exception(
					errno, 
					"Error writing to port.", 
					__FILE__, 
					"SerialPort", 
					"tx()", 
					__LINE__);
	}

	if (wlen != 1) {
		throw new Exception(
					ERR_PORT_IO, 
					"Error writing to port.", 
					__FILE__, 
					"SerialPort", 
					"tx()", 
					__LINE__);
	}
}

byte SerialPort::rx()
{
	int		rlen;
	byte	b;
	
	rlen = read(fd, &b, 1);
	
	if (errno) {
		throw new Exception(
					errno, 
					"Error reading from port.", 
					__FILE__, 
					"SerialPort", 
					"rx()", 
					__LINE__);
	}
	
	return b;
}

void SerialPort::tx(byte * p, int length)
{
	int		wlen;
	
	openPort(false);
	
	setRTS();
	
	wlen = write(fd, p, length);
	
	clearRTS();

	closePort();
	
	if (errno) {
		throw new Exception(
					errno, 
					"Error writing to port.", 
					__FILE__, 
					"SerialPort", 
					"tx()", 
					__LINE__);
	}

	if (wlen != length) {
		throw new Exception(
					ERR_PORT_IO, 
					"Error writing to port.", 
					__FILE__, 
					"SerialPort", 
					"tx()", 
					__LINE__);
	}
}

int SerialPort::rx(byte * p, int size, int length)
{
	int		i = 0;
	int		bytesRead = 0;
	bool	go = true;
	
	openPort(true);
	
	while (go) {
		p[i++] = rx();
		
		bytesRead++;
		
		if (bytesRead == size || bytesRead == length) {
			go = false;
		}
	}

	closePort();
	
	return bytesRead;
}
