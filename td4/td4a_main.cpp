#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "ThreadIncr.h"


int main(int argc, char* argv[])
{
	(void)argc;
	std::cout << "Please input number of loops for the incrementer, and the number of threads you want to call: "<< std::endl;

	double nLoops = atof(argv[1]);
	int nTasks = atoi(argv[2]);
	double counter = 0;
	std::cout << "Counter value initialised at 0" << std::endl << std::endl;

	Incr incr(&counter);

	// Create tab of ThreadIncr
	std::vector<ThreadIncr> tabThreads;

	std::cout << "Calling " << nTasks << " threads once at a time, incrementing counter for " << nLoops << " each" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads.push_back(ThreadIncr(&incr, nLoops));
		tabThreads[i].start();
		tabThreads[i].join();
		std::cout << ">>>> Get counter from looper: " << *(incr.getSample()) << std::endl;
	}

	std::cout << std::endl;
	counter = 0;
	Incr incr_2(&counter);

	// Create tab of ThreadIncr
	std::vector<ThreadIncr> tabThreads_2;

	std::cout << "Calling " << nTasks << " threads at once (no mutex), incrementing counter for " << nLoops << " each" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads_2.push_back(ThreadIncr(&incr_2, nLoops));
	}

	std::cout << "Starting the threads" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads_2[i].start();
		if(i%2==0)
		{
			std::cout << ">>>> Making calling thread sleeps for 1000. ms" << std::endl;
			tabThreads_2[i].sleep_ms(1000.);
		}
	}

	std::cout << "Closing the threads" << std::endl << std::endl;

	std::cout << "Exec time of the thread no: " << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads_2[i].join();
		std::cout << i << " is: " << tabThreads_2[i].execTime_ms() << std::endl;
	}

	std::cout << "Get counter from looper: " << *(incr_2.getSample()) <<", should be "<< nLoops*nTasks << std::endl;
}
