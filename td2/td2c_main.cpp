#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "timespec_op.h"

using namespace std;

/*!
Struct Counter:
encapsulates parameters for incrementer, as well as a mutex
*/
struct Counter
{
	pthread_mutex_t mutex;
	unsigned int nLoops;
	double* pCounter;
	int* pProtected;
};


/*!
\brief Increment nloops time a counter value, with mutex protection
\param nLoops: number of loop to be done
\param pCounter: pointer to counter value, to be incremented
\param pProtected: param to activate mutex protection if value is not 0.
*/
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


/*!
\brief Callback to incrementer
\param varIncr: pointer to a structure with params for incrementer
\return varIncr pointer.
*/
void* call_incr(void* varIncr)
{
	Counter* p_incr = (Counter*) varIncr;
	incr(p_incr->nLoops, p_incr->pCounter, p_incr->mutex, p_incr->pProtected);

	return varIncr;
}


int main(int, char* argv[])
{

	cout << "Please input number of loops, number of threads, scheduling policy and bool for mutex protection (0 for true)" << endl;
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
		schedPriority = sched_get_priority_max(SCHED_RR)-1;
	}
	if(schedPolicy_name=="FIFO")
	{
		schedPolicy = SCHED_FIFO;
		schedPriority = sched_get_priority_max(SCHED_FIFO)-1;
	}

	double counter = 0.0;

	struct Counter sharedVar;
	sharedVar.nLoops = nLoops;
	sharedVar.pCounter = &counter;
	sharedVar.pProtected = &boolProtected;

	pthread_mutexattr_t m_attr;
	pthread_mutexattr_init(&m_attr);

	pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&sharedVar.mutex, &m_attr);


	pthread_t* tabThreads = NULL;
	tabThreads = new pthread_t[nTasks];

	// definition of scheduling policy and order
	sched_param schedParams;
	schedParams.sched_priority = schedPriority;
	pthread_setschedparam(pthread_self(), schedPolicy, &schedParams);

	timespec start = timespec_now();
	for(int i=0; i<nTasks; i++)
	{
		pthread_create(&tabThreads[i], NULL, call_incr, &sharedVar);
	}

	for(int i=0; i<nTasks; i++)
	{
		pthread_join(tabThreads[i], NULL);
	}
	timespec end = timespec_now();
	timespec duration = end - start;


	cout << "Counter value:" << counter << endl;

	cout << "The execution time is: ";
	print_timespec(duration);
	cout << endl;

	pthread_mutex_destroy(&sharedVar.mutex);
}
