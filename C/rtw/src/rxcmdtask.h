#ifndef _INCL_RXCMDTASK
#define _INCL_RXCMDTASK


typedef struct
{
	uint8_t		messageID; 
	uint8_t		command;
	uint8_t * 	message; 
	uint8_t 	dataLength; 
	uint8_t 	errorState;
}
RX_CMD;

class RxCmdTask : public Task
{
    public:
		RxCmdTask(uint16_t ID);
        
        void        run(void * p);        
};

#endif