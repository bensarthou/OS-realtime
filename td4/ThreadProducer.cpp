#include "ThreadProducer.h"
#include "Semaphore.h"


ThreadProducer::ThreadProducer(Semaphore& sem): sem(sem),  tokens_given(0){}


void ThreadProducer::run()
{
	sem.give();
	tokens_given++;
}

int ThreadProducer::getTokens()
{
	return(tokens_given);
}
