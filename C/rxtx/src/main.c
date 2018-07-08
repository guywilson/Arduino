#include <stdint.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "rxtxmsgdef.h"

#ifndef SERIAL_PORT
#define SERIAL_PORT			"/dev/cu.wchusbserial1410"
#endif

int set_interface_attribs(int fd, int speed)
{
	struct termios SerialPortSettings;

	tcgetattr(fd, &SerialPortSettings);

	cfsetispeed(&SerialPortSettings, speed);
	cfsetospeed(&SerialPortSettings, speed);

	SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */

	SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 


	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
	
	SerialPortSettings.c_cc[VMIN]  = 10; /* Read 10 characters */  
	SerialPortSettings.c_cc[VTIME] = 50;  /* Wait indefinitely   */
	
	if ((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) {
		printf("\n  ERROR ! in Setting attributes\n");
		return -1;
	}
	
	return 0;
}

int readSerial(const char * szPortname, char * szBuffer)
{
	int					i = 0;
	int					fd;
    int					rlen;
    int					bytesRead = 0;
    int					go = 1;

    fd = open(szPortname, O_RDWR | O_NOCTTY);
    
	if (fd < 0) {
        printf("Error opening %s: %s\n", szPortname, strerror(errno));
        return -1;
    }

	set_interface_attribs(fd, B57600);
	
	tcflush(fd, TCIFLUSH);

	while (go) {
		rlen = read(fd, &szBuffer[i], 1);
		
		bytesRead += rlen;
		
		if (errno) {
			printf("Read error: %s\n", strerror(errno));
			break;
		}
		
		if (szBuffer[i] == '\n') {
			go = 0;
		}
		
		i++;
	}
	
	szBuffer[i] = 0;
	
	close(fd);
	
	return bytesRead;
}

int main(int argc, char *argv[])
{
	char				readBuffer[65];
	int					go = 1;
	int					bytesRead;

	while (go) {
			bytesRead = readSerial(SERIAL_PORT, readBuffer);
			
			printf("rx : %s\n", readBuffer);
	}

	return 0;
}
