#include "ThreadProducer.h"
#include "Semaphore.h"


ThreadProducer::ThreadProducer(Semaphore& sem, int token_loop_): sem(sem),  tokens_given(0),
																 token_loop(token_loop_){}


void ThreadProducer::run()
{
	for(int i=0; i<token_loop; i++)
	{
		sem.give();
		tokens_given++;
	}
}

int ThreadProducer::getTokens()
{
	return(tokens_given);
}
