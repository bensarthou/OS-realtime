#include "ThreadConsumer.h"

ThreadConsumer::ThreadConsumer(Semaphore& sem, double timeout_ms): sem(sem), timeout_ms(timeout_ms),
																	approved(0), denied(0){}


void ThreadConsumer::run(){
	while (sem.take(timeout_ms))
	{
		approved++;
	}
	denied++;
}


int ThreadConsumer::getApproved()
{
	return(approved);
}


int ThreadConsumer::getDenied()
{
	return(denied);
}
