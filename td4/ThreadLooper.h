#ifndef THREADLOOPER_H
#define THREADLOOPER_H

#include "Thread.h"
#include "Looper.h"

class ThreadLooper: public Thread
{
	public:
		ThreadLooper(Looper* looper, double nLoops);

	protected:
		void run();

	private:
		Looper* looper;
		double nLoops;
};
#endif
