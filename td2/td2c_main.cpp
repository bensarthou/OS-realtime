#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

struct Counter
{
	pthread_mutex_t mutex;
	unsigned int nLoops;
	double* pCounter;
	int* pProtected;
};


void incr(unsigned int nLoops, double* pCounter, pthread_mutex_t mutex, int* pProtected)
{
	for(unsigned int i = 0; i<nLoops; i++)
	{

		// section critique
		if(*pProtected==0)
		{
			*pCounter += 1.0;
		}
		else
		{
			pthread_mutex_lock(&mutex);
			*pCounter += 1.0;
			pthread_mutex_unlock(&mutex);
		}
	}
}

void* call_incr(void* varIncr)
{
	Counter* p_incr = (Counter*) varIncr;
	incr(p_incr->nLoops, p_incr->pCounter, p_incr->mutex, p_incr->pProtected);
}


int main(int argc, char* argv[])
{

	unsigned int nLoops = atoi(argv[1]); // number of loops done by each incrementer
	int nTasks = atoi(argv[2]); // number of tasks (incrementer) launched
	std::string schedPolicy_name = argv[3]; // string, scheduling policy (see man 7 sched)
	int boolProtected = atoi(argv[4]); // if true, activate mutex protection

	// define scheduling policy (and threads priority)
	int schedPriority;
	int schedPolicy;

	if(schedPolicy_name=="OTHER")
	{
		schedPolicy = SCHED_OTHER;
		schedPriority = 0;
	}
	else if(schedPolicy_name=="RR")
	{
		schedPolicy = SCHED_RR;
		schedPriority = 1;
	}
	if(schedPolicy_name=="FIFO")
	{
		schedPolicy = SCHED_FIFO;
		schedPriority = 1;
	}

	double counter = 0.0;

	struct Counter sharedVar;
	sharedVar.nLoops = nLoops;
	sharedVar.pCounter = &counter;
	sharedVar.pProtected = &boolProtected;

	pthread_mutex_init(&sharedVar.mutex, nullptr);

	pthread_t* tabThreads = NULL;
	tabThreads = new pthread_t[nTasks];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); // Herite de la politique d'ordonnancement

	pthread_attr_setschedpolicy(&attr, SCHED_RR); // entre les threads de même priorité, fait tourner l'execution
	sched_param schedParams;
	schedParams.sched_priority = schedPriority; // 0 si OTHER, entre 1..99 pour les autres

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
	pthread_mutex_destroy(&sharedVar.mutex);
	pthread_attr_destroy(&attr);
}
