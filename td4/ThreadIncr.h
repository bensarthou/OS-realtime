#ifndef THREADINCR_H
#define THREADINCR_H

#include "Thread.h"
#include "Incr.h"

class ThreadIncr: public Thread
{
	public:
		ThreadIncr(Incr* incr, double nLoops);

	protected:
		void run();

	private:
		Incr* incr;
		double nLoops;
};
#endif
