#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

struct VarIncr
{
    unsigned int nLoops;
    double* pCounter;
};


void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned int i = 0; i<nLoops; i++)
    {
        *pCounter += 1.0;
    }
}

void* call_incr(void* varIncr)
{
    VarIncr* p_incr = (VarIncr*) varIncr;
    incr(p_incr->nLoops, p_incr->pCounter);
}


int main(int argc, char* argv[])
{

    unsigned int nLoops = atoi(argv[1]);
    int nTasks = atoi(argv[2]);

    double counter = 0.0;

    struct VarIncr sharedVar;
    sharedVar.nLoops = nLoops;
    sharedVar.pCounter = &counter;

    pthread_t* tabThreads = NULL;
    tabThreads = new pthread_t[nTasks];

    for(int i=0; i<nTasks; i++)
    {
        pthread_create(&tabThreads[i], NULL, call_incr, &sharedVar);
    }

    for(int i=0; i<nTasks; i++)
    {
        pthread_join(tabThreads[i], NULL);
    }

    printf("Counter value: %f\n", counter);
}
