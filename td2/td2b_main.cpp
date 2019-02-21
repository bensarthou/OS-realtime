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
Struct VarIncr:
\brief encapsulates nLoops and pCounter to use in thread callback for incrementer
*/
struct VarIncr
{
	unsigned int nLoops;
	double* pCounter;
};


/*!
\brief Increment nloops time a counter value
\param nLoops: number of loop to be done
\param pCounter: pointer to counter value, to be incremented
*/
void incr(unsigned int nLoops, double* pCounter)
{
	for(unsigned int i = 0; i<nLoops; i++)
	{
		*pCounter += 1.0;
	}
}

/*!
\brief Callback to incrementer
\param varIncr: pointer to a structure with params for incrementer
\return varIncr pointer.
*/
void* call_incr(void* varIncr)
{
	VarIncr* p_incr = (VarIncr*) varIncr;
	incr(p_incr->nLoops, p_incr->pCounter);

	return varIncr;
}

int main(int, char* argv[])
{

	cout << "Please input number of loops, number of tasks and scheduling policy name: " << endl;
	unsigned int nLoops = atoi(argv[1]); // number of loops done by each incrementer
	int nTasks = atoi(argv[2]); // number of tasks (incrementer) launched
	std::string schedPolicy_name = argv[3]; // string, scheduling policy (see man 7 sched)

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
		schedPriority = sched_get_priority_max(SCHED_RR);
	}
	if(schedPolicy_name=="FIFO")
	{
		schedPolicy = SCHED_FIFO;
		schedPriority = sched_get_priority_max(SCHED_FIFO);
	}

	double counter = 0.0;

	struct VarIncr sharedVar;
	sharedVar.nLoops = nLoops;
	sharedVar.pCounter = &counter;

	// declare list of threads
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
	// pthread_attr_destroy(&attr);
}
