#include "Scheduler.h"


Scheduler gScheduler;

int main()
{
	// Preparation
	// ...


	// Initialization
	// ...
	schedInitialize(&gScheduler);
	
	// Superloop
	//
	while (1)
	{
		schedCycle(&gScheduler);
	}
}
