#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Mutex.h"
#include <climits>

class Semaphore {
	public:
		Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT_MAX);
		~Semaphore();
		void give();
		void take();
		bool take(double timeout_ms);
		unsigned int getCounter();

	protected:
		unsigned int counter;
		unsigned int maxCount;
		Mutex mutex;

	private:
};

#endif
