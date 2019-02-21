#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

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
	cout << "Please input number of loops and number of threads: \n" << endl;
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

	cout << "Counter value: " << counter << endl;
}
