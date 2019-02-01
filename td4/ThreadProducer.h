#ifndef THREADPRODUCER_H
#define THREADPRODUCER_H

#include "Thread.h"
#include "Semaphore.h"

class ThreadProducer : public Thread
{
	protected:
		Semaphore& sem;
		int tokens_given;
		int token_loop;
		void run();

	public:
		ThreadProducer(Semaphore& sem, int token_loop);
		int getTokens();
};

#endif
