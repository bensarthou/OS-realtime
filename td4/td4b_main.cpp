#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

#include "ThreadIncr.h"
#include "Mutex.h"

int main(int, char* argv[])
{
	std::cout << "Please input number of loops for the incrementer, and the number of threads you want to call: "<< std::endl;

	double nLoops = atof(argv[1]);
	int nTasks = atoi(argv[2]);
	double counter = 0;
	std::cout << "Counter value initialised at: "<< counter << std::endl << std::endl;

	Mutex mutex;
	ProtectedIncr incr(&counter, mutex);

	// Create tab of ThreadIncr
	// std::vector<ThreadIncr> tabThreads;
    std::vector<std::unique_ptr<ThreadProtectedIncr>> tabThreads(nTasks);

	std::cout << "Calling " << nTasks << " threads at once (no mutex), incrementing counter for " << nLoops << " each" << std::endl;

	for(auto& thread : tabThreads)
	{
        thread.reset(new ThreadProtectedIncr(&incr, nLoops));
	}

	std::cout << "Starting the threads" << std::endl;

	for(int i=0; i<nTasks; i++)
	{
		tabThreads[i]->start();
		if(i==0)
		{
			std::cout << ">>>> Making calling thread sleeps for 1000. ms" << std::endl;
			tabThreads[i]->sleep_ms(1000.);
		}
	}

	std::cout << "Closing the threads" << std::endl << std::endl;
	std::cout << "Exec time of the thread no: " << std::endl;
	for(int i=0; i<nTasks; i++)
	{
		tabThreads[i]->join();
		std::cout << i << " is: " << tabThreads[i]->execTime_ms() << std::endl;
	}

	std::cout << "Get counter from looper: " << *(incr.getSample()) <<", should be "<< nLoops*nTasks << std::endl;
}

// FIFO ?!
// tester timeout de Lock/tryLock =>
// wait(timeout) => timeout total ou non => oui, recuperer le temps depuis la fonction posix
// push_back: changer la méthode pour éviter les copies d'object (utiliser un setter)
