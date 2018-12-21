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
        // section critique
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
    int schedPolicy = atoi(argv[3]);

    double counter = 0.0;

    struct VarIncr sharedVar;
    sharedVar.nLoops = nLoops;
    sharedVar.pCounter = &counter;

    pthread_t* tabThreads = NULL;
    tabThreads = new pthread_t[nTasks];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); // Herite de la politique d'ordonnancement
    pthread_attr_setschedpolicy(&attr, SCHED_RR); // entre les threads de même priorité, fait tourner l'execution
    sched_param schedParams;
    schedParams.sched_priority = schedPolicy;

    pthread_attr_setschedparam(&attr, &schedParams);
    for(int i=0; i<nTasks; i++)
    {
        pthread_create(&tabThreads[i], NULL, call_incr, &sharedVar);
    }

    for(int i=0; i<nTasks; i++)
    {
        pthread_join(tabThreads[i], NULL);
    }

    printf("Counter value: %f\n", counter);
    pthread_attr_destroy(&attr);
}
