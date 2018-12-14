#include <signal.h>
#include <time.h>
#include <iostream>
#include <unistd.h>


/*
Implémentez un timer Posix périodique de fréquence 2 Hz imprimant un message avec la valeur
d’un compteur régulièrement incrémenté. Le programme doit s’arrêter après 15 incrémentations.
*/


using namespace std;

void myIncrementer(int sig, siginfo_t* si, void*)
{
	volatile int* ptrCounter;
	ptrCounter = (volatile int*) si->si_value.sival_ptr;

	*ptrCounter += 1;
	std::cout << "Compteur:" << *ptrCounter << std::endl;
}

int main()
{

	volatile int counter = 0;

	// Action à effectuer quand le timer finit
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO; // Type de l'appel: fonction avec paramètres
	sa.sa_sigaction = myIncrementer; // la fonction à appeler

	sigemptyset(&sa.sa_mask); // aucun flag de bloquage
	sigaction(SIGRTMIN, &sa, NULL); // Borne du signal temporel ?

	struct sigevent sev; // evenement associé à l'expiration du timer ??
	sev.sigev_notify = SIGEV_SIGNAL; // type de l'evenement: signal
	sev.sigev_signo = SIGRTMIN; // Signal émis: doit être le même que celui de l'action
	sev.sigev_value.sival_ptr = (void*) &counter; // value to be used in siginfo_t* in your handler

	timer_t tid; // id du timer
	timer_create(CLOCK_REALTIME, &sev, &tid); //creation du timer, ne pas oublier le delete
	itimerspec its; // contient les durées d'expiration du timer
	its.it_value.tv_sec = 10; // durée de la première expiration, on peut y mettre 0 pour arrêter le timer
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;// expiration periodique
	its.it_interval.tv_nsec = 500000000;

	timer_settime(tid, 0, &its, NULL); // démarrage du timer

	while(counter < 15)
	{
		usleep(5);
	}

	timer_delete(tid); //desctruction du timer

}
