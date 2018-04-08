#include "factory.h"

RTScheduler		scheduler;

RTScheduler * RTSFactory::getScheduler()
{
	return &scheduler;
}
