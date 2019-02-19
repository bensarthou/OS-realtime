#include <signal.h>
#include <time.h>
#include <iostream>
#include <unistd.h>


using namespace std;

void myIncrementer(int sig, siginfo_t* si, void*)
{
	volatile int* ptrCounter;
	ptrCounter = (volatile int*) si->si_value.sival_ptr;

	*ptrCounter += 1;
	cout << "Compteur:" << *ptrCounter << endl;
}

int main()
{

	volatile int counter = 0;

	// Action to be done as timer callback
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO; // callback type (function)
	sa.sa_sigaction = myIncrementer; // the callback func

	sigemptyset(&sa.sa_mask); // No block flag
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev; // definition of callback variable
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = (void*) &counter; // value to be used in siginfo_t* in your handler

	timer_t tid; // Timer id
	timer_create(CLOCK_REALTIME, &sev, &tid); // Creation the timer object

	itimerspec its; // Define expiration time for the timer
	its.it_value.tv_sec = 10; // First tick
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0; // timer period
	its.it_interval.tv_nsec = 500000000;

	// STARTING THE TIMER
	timer_settime(tid, 0, &its, NULL);


	while(counter < 15)
	{
		usleep(5);
	}

	timer_delete(tid); //Timer destruction

}
