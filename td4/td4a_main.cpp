#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "ThreadLooper.h"
#include "Thread.h"

int main(int argc, char* argv[])
{
    double nLoops = atof(argv[1]);
    int nTasks = atoi(argv[2]);

    Looper looper;

    // Create tab of ThreadIncr
    std::vector<ThreadLooper> tabThreads;

    for(int i=0; i<nTasks; i++)
    {
        std::cout << "Entering the main" << std::endl;
        tabThreads[i] = ThreadLooper(&looper, nLoops);

        std::cout << "Start the thread" << std::endl;
        tabThreads[i].start();
        // Start the thread
    }

    for(int i=0; i<nTasks; i++)
    {
        std::cout << "Stop the thread" << std::endl;
        tabThreads[i].join();
    }


    std::cout << looper.getSample() << std::endl;
}
