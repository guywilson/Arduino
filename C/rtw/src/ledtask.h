#ifndef _INCL_LEDTASK
#define _INCL_LEDTASK

class LEDTask1 : public Task
{
    public:
		LEDTask1(uint16_t ID);
        
		void        run(void * p);        
};

class LEDTask2 : public Task
{
    public:
		LEDTask2(uint16_t ID);
        
		void        run(void * p);        
};

#endif