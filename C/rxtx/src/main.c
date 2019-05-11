#include <stdint.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "rxtxmsgdef.h"

#ifndef SERIAL_PORT
#define SERIAL_PORT			"/dev/cu.wchusbserial1410"
#endif

/*
** Request frame (6 - 80 bytes)
** <START><LENGTH><MSG_ID><CMD><DATA (0 - 74)><CHECKSUM><END>
**                 |                        |
**                  --included in checksum--
**
** ACK response frame
** <START><LENGTH><MSG_ID><ACK><DATA><CHECKSUM><END>
**
** NAK response frame
** <START><MSG_ID><NAK><ERR_CODE><END>
**
**
** The checksum is calculated as follows:
**
** The sender adds all the data bytes plus the cmd and msg id, taking
** just the least significant byte and subtracting that from 0xFF gives
** the checksum.
**
** The receiver adds all the data bytes plus the cmd, msg id and checksum,
** the least significant byte should equal 0xFF if the checksum is valid.
*/

#define NUM_REQUEST_FRAME_BYTES		  6
#define MAX_DATA_LENGTH				 74
#define MAX_REQUEST_MESSAGE_LENGTH	(NUM_REQUEST_FRAME_BYTES + MAX_DATA_LENGTH)

#define MAX_CMD_FRAME_LENGTH		 76		// Data + msgID + cmd

#define MSG_CHAR_START				0x7E
#define MSG_CHAR_END				0x81

#define MSG_CHAR_ACK				0x06
#define MSG_CHAR_NAK				0x15

#define MSG_NAK_UNKNOWN_CMD			0x01
#define MSG_NAK_INVALID_CHECKSUM	0x02
#define MSG_NAK_DATA_ERROR			0x04
#define MSG_NAK_DATA_OVERRUN		0x08

#define RX_STATE_START				0x01
#define RX_STATE_LENGTH				0x02
#define RX_STATE_MSGID				0x03
#define RX_STATE_CMD				0x04
#define RX_STATE_DATA				0x05
#define RX_STATE_CHECKSUM			0x06
#define RX_STATE_END				0x07

#define RX_CMD_TPH					0x01
#define RX_CMD_ANEMOMETER			0x02
#define RX_CMD_RAINGUAGE			0x04

char szPort[128];

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

int readSerial(const char * pszPortname, uint8_t * data)
{
	int					i = 0;
	int					fd;
    int					rlen;
    int					bytesRead = 0;
    int					go = 1;

    fd = open(pszPortname, O_RDWR | O_NOCTTY);
    
	if (fd < 0) {
        printf("Error opening %s: %s\n", pszPortname, strerror(errno));
        return -1;
    }

	set_interface_attribs(fd, B57600);
	
	tcflush(fd, TCIFLUSH);

	while (go) {
		rlen = read(fd, &data[i], 1);
		
		bytesRead += rlen;
		
		if (errno) {
			printf("Read error: %s\n", strerror(errno));
			break;
		}
		
		if (data[i] == MSG_CHAR_END) {
			go = 0;
		}
		
		i++;
	}
	
	close(fd);
	
	return bytesRead;
}

int writeSerial(const char * pszPortname, uint8_t * data, int dataLength)
{
	int			fd;
	int			bytesWritten = 0;

	fd = open(pszPortname, O_RDWR | O_NOCTTY);

	if (fd < 0) {
        printf("Error opening %s: %s\n", pszPortname, strerror(errno));
        return -1;
    }

	set_interface_attribs(fd, B57600);

	tcflush(fd, TCIFLUSH);

	bytesWritten = write(fd, data, dataLength);

	if (errno) {
		printf("Write error: %s\n", strerror(errno));
	}

	close(fd);

	return bytesWritten;
}

void * queryTPHThread(void * pArgs)
{
	uint8_t		msgID = 1;
	int			go = 1;
	int			frameLength = 0;
	int			readLen;
	int			i;
	uint8_t		frame[80];

	while (go) {
		frame[0] = MSG_CHAR_START;
		frame[1] = 2;
		frame[2] = msgID++;
		frame[3] = RX_CMD_TPH;
		frame[4] = 0x00FF - ((frame[2] + frame[3]) & 0x00FF);
		frame[5] = MSG_CHAR_END;

		frameLength = 6;

		writeSerial(szPort, frame, frameLength);

		usleep(500000L);

		readLen = readSerial(szPort, frame);

		for (i = 0;i < readLen;i++) {
			printf("Read [0x%02X\n", frame[i]);
		}

		sleep(5);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int			err;
	pthread_t	tid;

	if (argc > 1) {
		strcpy(szPort, &argv[1][0]);
	}

	err = pthread_create(&tid, NULL, &queryTPHThread, NULL);

    if (err != 0) {
    	printf("\nCan't create thread :[%s]", strerror(err));
    }
    else {
    	printf("\n Thread created successfully\n");
    }

    while (1) {
    	usleep(1000L);
    }

	return 0;
}
