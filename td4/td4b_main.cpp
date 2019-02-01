#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "ThreadIncr.h"
#include "Mutex.h"

int main(int argc, char* argv[])
{
	(void)argc;
	std::cout << "Please input number of loops for the incrementer, and the number of threads you want to call: "<< std::endl;

	double nLoops = atof(argv[1]);
	int nTasks = atoi(argv[2]);
	double counter = 0;
	std::cout << "Counter value initialised at: "<< counter << std::endl << std::endl;

	Mutex mutex;
	ProtectedIncr incr(&counter, mutex);

	// Create tab of ThreadIncr
	std::vector<ThreadIncr> tabThreads;

	std::cout << "Calling " << nTasks << " threads at once (no mutex), incrementing counter for " << nLoops << " each" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads.push_back(ThreadIncr(&incr, nLoops));
	}

	std::cout << "Starting the threads" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads[i].start();
		if(i%2==0)
		{
			std::cout << ">>>> Making calling thread sleeps for 1000. ms" << std::endl;
			tabThreads[i].sleep_ms(1000.);
		}
	}

	std::cout << "Closing the threads" << std::endl << std::endl;

	std::cout << "Exec time of the thread no: " << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads[i].join();
		std::cout << i << " is: " << tabThreads[i].execTime_ms() << std::endl;
	}

	std::cout << "Get counter from looper: " << *(incr.getSample()) <<", should be "<< nLoops*nTasks << std::endl;
}

// Question: tâche cons/prod -> juste give/take ? 
// FIFO ?!
// Appel à unlock dans destructeur de TryLock
// td4_main
// tester timeout de Lock/tryLock
