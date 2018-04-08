#include "scheduler.h"

#ifndef _INCL_FACTORY
#define _INCL_FACTORY

class RTSFactory
{
	public:
		static RTScheduler		*	getScheduler();
};

#endif