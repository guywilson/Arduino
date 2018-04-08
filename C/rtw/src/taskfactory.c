#include <stddef.h>

#include "task.h"
#include "taskfactory.h"
#include "taskdef.h"
#include "ledtask.h"
#include "rxcmdtask.h"

/******************************************************************************
**
** Define tasks here...
**
******************************************************************************/

LEDTask1			ledTask1(TASK_LED1);
LEDTask2			ledTask2(TASK_LED1);
RxCmdTask			rxCmdTask(TASK_RXCMD);

/*****************************************************************************/

Task * getTask(int taskID)
{
	Task *		t = NULL;
	
	switch (taskID) {
		case TASK_LED1:
			t = &ledTask1;
			break;
			
		case TASK_LED2:
			t = &ledTask2;
			break;
			
		case TASK_RXCMD:
			t = &rxCmdTask;
			break;
	}
	
	return t;
}
