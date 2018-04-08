#include <avr/io.h>

#include "task.h"
#include "rxcmdtask.h"
#include "serial_atmega328p.h"


RxCmdTask::RxCmdTask(uint16_t ID) : Task(ID)
{	
}

void RxCmdTask::run(void * p)
{
	RX_CMD * cmd = (RX_CMD *)p;
	
	processCommand(
		cmd->messageID, 
		cmd->command, 
		cmd->message, 
		cmd->dataLength, 
		cmd->errorState);
}