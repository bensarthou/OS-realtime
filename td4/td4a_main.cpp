#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

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
	std::vector<std::unique_ptr<ThreadIncr>> tabThreads(nTasks);

	std::cout << "Calling " << nTasks << " threads once at a time, incrementing counter for " << nLoops << " each" << std::endl;

	for(auto& thread : tabThreads)
	{
        thread.reset(new ThreadIncr(&incr, nLoops));
		thread->start();
		thread->join();
		std::cout << ">>>> Get counter from looper: " << *(incr.getSample()) << std::endl;
	}




	std::cout << std::endl;
	counter = 0;
	Incr incr_2(&counter);

	// Create tab of ThreadIncr
	std::vector<std::unique_ptr<ThreadIncr>> tabThreads_2(nTasks);

	std::cout << "Calling " << nTasks << " threads at once (no mutex), incrementing counter for " << nLoops << " each" << std::endl;

	for(auto& thread : tabThreads_2)
	{
        thread.reset(new ThreadIncr(&incr_2, nLoops));
	}

	std::cout << "Starting the threads" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads_2[i]->start();
		if(i==0)
		{
			std::cout << ">>>> Making calling thread sleeps for 1000. ms" << std::endl;
			tabThreads_2[i]->sleep_ms(1000.);
		}
	}

	std::cout << "Closing the threads" << std::endl << std::endl;

	std::cout << "Exec time of the thread no: " << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads_2[i]->join();
		std::cout << i << " is: " << tabThreads_2[i]->execTime_ms() << std::endl;
	}

	std::cout << "Get counter from looper: " << *(incr_2.getSample()) <<", should be "<< nLoops*nTasks << std::endl;
}
