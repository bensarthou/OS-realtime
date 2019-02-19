#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

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


int main(int, char* argv[])
{
	std::cout << "Please input number of loops to increment the counter: " << std::endl;
	unsigned int nLoops = atoi(argv[1]);

	// initialize counter at 0.0
	double counter = 0.0;

	struct timespec start, end, duration;

	clock_gettime(CLOCK_REALTIME, &start);

	// We measure the exec time of the incrementation
	incr(nLoops, &counter);

	clock_gettime(CLOCK_REALTIME, &end);
	std::cout << "Final value of pCounter:" << counter << std::endl;

	// Computing difference between start and stop timespec
	duration.tv_sec = end.tv_sec - start.tv_sec;

	// In case of nanoseconds overflow
	if (end.tv_nsec < start.tv_nsec)
	{
		duration.tv_sec -= 1;
		end.tv_nsec += 1000000000;
	}

	duration.tv_nsec = end.tv_nsec - start.tv_nsec;

	printf("Measured duration is %ld seconds and %ld nanoseconds, equivalent to %f millisconds\n",
	duration.tv_sec, duration.tv_nsec, duration.tv_sec*1000. + duration.tv_nsec/1000000.);
}
