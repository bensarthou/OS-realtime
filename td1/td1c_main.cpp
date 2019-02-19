#include <iostream>
#include <sstream>
#include <climits>
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <time.h>

#include <unistd.h>

using namespace std;


/*!Struct linear
\brief: containing 2 double, defining the relationship between exec time and number of loops
*/
struct Linear
{
	double a;
	double b;
};


/*!
\brief incrementer function, with early stopping
\param nLoops: number of incrementations to be done
\param pCounter: pointer to counter to be incremented
\param pStop: pointer to bool, can early stop the incrementation

\return actual number of incrementations done.
*/
unsigned int incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
	unsigned int iLoops = 0;
	for(iLoops = 0; iLoops<nLoops; iLoops++)
	{
		if(*pStop)
		{
			break;
		}
		*pCounter += 1.0;
	}
	return iLoops;
}


/*!
\brief This timer callback function will change the value of the bool Stop, during timer execution
*/
void stopCallback(int, siginfo_t* si, void*)
{
	volatile int* ptrStop;
	ptrStop = (volatile int*) si->si_value.sival_ptr;

	*ptrStop = true;
}


/*!
\brief: Function to calibrate a loop: Run an incrementation, early stop it at 4 or 6 seconds with
a timer, and measure the (linear) relationship between execution time and number of incrementations done

\return: param of the linear relation, as a Linear struct
*/
Linear calib()
{
	Linear res;

	unsigned int nLoops = UINT_MAX;
	double counter1 = 0;
	double counter2 = 0;

	volatile bool stop = false; // early stopping
	unsigned int max_loops_done_4 = 0; // Number of loops done during 4 seconds
	unsigned int max_loops_done_6 = 0; // Number of loops done during 6 seconds

	/************************/
	/* DEFINITION OF TIMERS */
	/************************/

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = stopCallback; // callback: modify Stop value

	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = (void*) &stop; // value to be used in siginfo_t* in your handler

	timer_t tid1;
	timer_t tid2; // id du timer
	timer_create(CLOCK_REALTIME, &sev, &tid1);
	timer_create(CLOCK_REALTIME, &sev, &tid2);

	// 4 second timer, no repeat
	itimerspec its4;
	its4.it_value.tv_sec = 4;
	its4.it_value.tv_nsec = 0;
	its4.it_interval.tv_sec = 0;
	its4.it_interval.tv_nsec = 0;

	// 6 second timer, no repeat
	itimerspec its6;
	its6.it_value.tv_sec = 6;
	its6.it_value.tv_nsec = 0;
	its6.it_interval.tv_sec = 0;
	its6.it_interval.tv_nsec = 0;

	/***********************************************/
	/* RUNNING TWO TIMERS OF DIFFERENTS DURATIONS  */
	/***********************************************/
	timer_settime(tid1, 0, &its4, NULL); // 4 sec timer starts

	max_loops_done_4 = incr(nLoops, &counter1, &stop);

	timer_delete(tid1);

	stop = false; // re-init early stopping

	timer_settime(tid2, 0, &its6, NULL); // 6 sec timer starts

	max_loops_done_6 = incr(nLoops, &counter2, &stop);

	timer_delete(tid1);

	/***********************************************************************/
	/* USING MEASURES AND LINEAR RELATION TO DEFINE CALIBRATION PARAMETERS */
	/***********************************************************************/

	res.a = (max_loops_done_6 - max_loops_done_4)/(6.0 - 4.0);
	res.b = max_loops_done_6 - 6*res.a;

	printf("We measured %d loops for a 4-sec timer, and %d for a 6-sec timer\n", max_loops_done_4,
			max_loops_done_6);
	printf("Linear law is %f*t+%f \n", res.a, res.b);

	return res;

}





int main()
{
	unsigned int nLoops = UINT_MAX;
	double counter = 0;

	volatile bool stop = false;
	unsigned int max_loops_done = 0;

	/***********************/
	/* DEFINITION OF TIMER */
	/***********************/

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = stopCallback; // callback for the timers

	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = (void*) &stop; // Stop value to be used by callback

	timer_t tid;
	timer_create(CLOCK_REALTIME, &sev, &tid);

	// Timer time definition (2 seconds expiration)
	itimerspec its;
	its.it_value.tv_sec = 2;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;

	timer_settime(tid, 0, &its, NULL); // Launching timer

	// Running the incrementer, when the timer will stop, so does the incrementation
	max_loops_done = incr(nLoops, &counter, &stop);

	timer_delete(tid);

	printf("We have run an incrementation and stop it at 2 seconds. Nb of loops before 2-sec timer interruption: %d \n", max_loops_done);


	/********************/
	/* LOOP CALIBRATION */
	/********************/
    printf(">>>> CALIBRATION:\n");
	Linear res_calib = calib();
    printf(">>>> TEST:\n");

	/********************/
	/* TEST CALIBRATION */
	/********************/
	printf("We want to run enough loops for the incrementation to run 5 seconds\n");
	unsigned int nLoops_calib = res_calib.a*5000.+res_calib.b;
	printf("Calibration says number of loop should be: %d\n", nLoops_calib);

	struct timespec start, end, duration;

	clock_gettime(CLOCK_REALTIME, &start);

	// We measure the exec time of the incrementation
    stop = false;
    counter = 0;
	max_loops_done = incr(nLoops_calib, &counter, &stop);

	clock_gettime(CLOCK_REALTIME, &end);
	std::cout << "Final value of counter:" << counter << std::endl;

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


	/*Amélioration:
	- On peut faire plusieurs mesures des max_loops pour des temps différents, et moyenner les a, b obtenus pour obtenir une mesure plus fiable
	- On peut aussi rajouter plus de points dans la courbe et interpoler la droite linéaire qui minimise un score r2
	S'assurer que la fonction s'execute sans interruption extérieure susceptible de perturber la mesure:
	  On parle d'execution thread-suspension-free, où l'on s'assure qu'aucun autre thread vient perturber l'execution.

	  On peut déjà limiter l'execution sur un unique coeur, avec priorité haute, et utiliser non plus le temps en secondes,
		mais le nombre de cycles passés par notre programme comme mesure du temps
	*/

}
