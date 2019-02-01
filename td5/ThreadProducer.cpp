#include "ThreadProducer.h"


void ThreadProducer::run()
{
	for (int i = 0 ; i < tokens ; i++) {
		// Release the tokens until there is no more left
		sem->give();
		tokens_left = tokens-i-1;
	}
}

int ThreadProducer::getTokensLeft()
{
	return(tokens_left);
}


ThreadProducer::ThreadProducer(int tokens, Semaphore* sem): Thread(SCHED_OTHER), tokens(tokens), tokens_left(tokens), sem(sem){}
