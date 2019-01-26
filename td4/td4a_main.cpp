#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "ThreadIncr.h"
#include "Thread.h"

int main(int argc, char* argv[])
{
    double nLoops = atof(argv[1]);
    int nTasks = atoi(argv[2]);
    double counter = 0;
    std::cout << "Counter value initialised at 0" << std::endl;

    Incr incr(&counter);

    // Create tab of ThreadIncr
    std::vector<ThreadIncr> tabThreads;

    std::cout << "Calling " << nTasks << " threads once at a time, incrementing counter for " << nLoops << " each" << std::endl;

    for(int i=0; i<nTasks; i++)
    {
        tabThreads.push_back(ThreadIncr(&incr, nLoops));
        tabThreads[i].start();
        tabThreads[i].join();
        std::cout << "Get counter from looper:" << *(incr.getSample()) << std::endl;
    }

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
    }

    std::cout << "Closing the threads" << std::endl;

    for(int i=0; i<nTasks; i++)
    {
        tabThreads_2[i].join();
    }

    std::cout << "Get counter from looper:" << *(incr_2.getSample()) << std::endl;

}
