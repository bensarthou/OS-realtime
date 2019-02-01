#ifndef THREADCONSUMER_H
#define THREADCONSUMER_H

#include "Thread.h"
#include "Semaphore.h"

class threadConsumer : public Thread
{
	private:
		bool stop;
		int approved;
		int denied;
		Semaphore* sem;
		double timeout_ms;

	protected:
		void run();

	public:
		int getApproved();
		int getDenied();
		int getID();
		void setStop(bool s);
		ThreadConsumer(Semaphore* sem, double timeout_ms);
};

#endif
