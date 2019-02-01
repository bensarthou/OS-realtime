#ifndef THREADPRODUCER_H
#define THREADPRODUCER_H

#include "Thread.h"
#include "Semaphore.h"

class ThreadProducer : public Thread
{
	protected:
		int tokens_given;
		Semaphore& sem;
		void run();

	public:
		ThreadProducer(Semaphore& sem);
		int getTokens();
};

#endif
