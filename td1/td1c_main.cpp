#include <iostream>
#include <sstream>
#include <climits>
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <time.h>

#include <unistd.h>

using namespace std;

struct Linear
{
	double a;
	double b;
};

unsigned int incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
	int iLoops = 0;
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


void stopCallback(int sig, siginfo_t* si, void*)
{
	volatile int* ptrStop;
	ptrStop = (volatile int*) si->si_value.sival_ptr;

	*ptrStop = true;
}

Linear calib()
{
	Linear res;

	unsigned int nLoops = UINT_MAX;
	double counter1 = 0;
	double counter2 = 0;

	volatile bool stop = false;
	unsigned int max_loops_done_4 = 0;
	unsigned int max_loops_done_6 = 0;

	// Action à effectuer quand le timer finit
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO; // Type de l'appel: fonction avec paramètres
	sa.sa_sigaction = stopCallback; // la fonction à appeler

	sigemptyset(&sa.sa_mask); // aucun flag de bloquage
	sigaction(SIGRTMIN, &sa, NULL); // Borne du signal temporel ?

	struct sigevent sev; // evenement associé à l'expiration du timer ??
	sev.sigev_notify = SIGEV_SIGNAL; // type de l'evenement: signal
	sev.sigev_signo = SIGRTMIN; // Signal émis: doit être le même que celui de l'action
	sev.sigev_value.sival_ptr = (void*) &stop; // value to be used in siginfo_t* in your handler

	timer_t tid1;
	timer_t tid2; // id du timer
	timer_create(CLOCK_REALTIME, &sev, &tid1); //creation du timer, ne pas oublier le delete
	timer_create(CLOCK_REALTIME, &sev, &tid2); //creation du timer, ne pas oublier le delete


	itimerspec its4; // contient les durées d'expiration du timer
	its4.it_value.tv_sec = 4; // durée de la première expiration, on peut y mettre 0 pour arrêter le timer
	its4.it_value.tv_nsec = 0;
	its4.it_interval.tv_sec = 0;// expiration periodique
	its4.it_interval.tv_nsec = 0;

	itimerspec its6; // contient les durées d'expiration du timer
	its6.it_value.tv_sec = 6; // durée de la première expiration, on peut y mettre 0 pour arrêter le timer
	its6.it_value.tv_nsec = 0;
	its6.it_interval.tv_sec = 0;// expiration periodique
	its6.it_interval.tv_nsec = 0;

	timer_settime(tid1, 0, &its6, NULL); // démarrage du timer

	max_loops_done_4 = incr(nLoops, &counter1, &stop);

	timer_delete(tid1); //desctruction du timer

	stop = false;

	timer_settime(tid2, 0, &its6, NULL); // démarrage du timer

	max_loops_done_6 = incr(nLoops, &counter2, &stop);

	timer_delete(tid1); //destruction du timer

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

	// Action à effectuer quand le timer finit
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO; // Type de l'appel: fonction avec paramètres
	sa.sa_sigaction = stopCallback; // la fonction à appeler

	sigemptyset(&sa.sa_mask); // aucun flag de bloquage
	sigaction(SIGRTMIN, &sa, NULL); // Borne du signal temporel ?

	struct sigevent sev; // evenement associé à l'expiration du timer ??
	sev.sigev_notify = SIGEV_SIGNAL; // type de l'evenement: signal
	sev.sigev_signo = SIGRTMIN; // Signal émis: doit être le même que celui de l'action
	sev.sigev_value.sival_ptr = (void*) &stop; // value to be used in siginfo_t* in your handler

	timer_t tid; // id du timer
	timer_create(CLOCK_REALTIME, &sev, &tid); //creation du timer, ne pas oublier le delete
	itimerspec its; // contient les durées d'expiration du timer
	its.it_value.tv_sec = 2; // durée de la première expiration, on peut y mettre 0 pour arrêter le timer
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;// expiration periodique
	its.it_interval.tv_nsec = 0;

	timer_settime(tid, 0, &its, NULL); // démarrage du timer

	max_loops_done = incr(nLoops, &counter, &stop);

	timer_delete(tid); //desctruction du timer

	printf("Nb of loops before 2-sec timer interruption: %d \n", max_loops_done);

	calib();

	/*Amélioration:
	- On peut faire plusieurs mesures des max_loops pour des temps différents, et moyenner les a, b obtenus pour obtenir une mesure plus fiable
	- On peut aussi rajouter plus de points dans la courbe et interpoler la droite linéaire qui minimise un score r2
	S'assurer que la fonction s'execute sans interruption extérieure susceptible de perturber la mesure:
	  On parle d'execution thread-suspension-free, où l'on s'assure qu'aucun autre thread vient perturber l'execution.

	  On peut déjà limiter l'execution sur un unique coeur, avec priorité haute, et utiliser non plus le temps en secondes,
		mais le nombre de cycles passés par notre programme comme mesure du temps
	*/

}