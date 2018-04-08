#include <avr/io.h>

#include "scheduler.h"
#include "rxcmdtask.h"
#include "serial_atmega328p.h"

void RxCmdTask(PTASKPARM p)
{
	RX_CMD * cmd = (RX_CMD *)p;
	
	processCommand(
		cmd->messageID, 
		cmd->command, 
		cmd->message, 
		cmd->dataLength, 
		cmd->errorState);
}
