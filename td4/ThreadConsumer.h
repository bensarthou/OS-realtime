#ifndef THREADCONSUMER_H
#define THREADCONSUMER_H

#include "Thread.h"
#include "Semaphore.h"

class ThreadConsumer : public Thread
{
	private:
		Semaphore& sem;
		double timeout_ms;
		int approved;
		int denied;

	protected:
		void run();

	public:
		int getApproved();
		int getDenied();
		ThreadConsumer(Semaphore& sem, double timeout_ms);
};

#endif
