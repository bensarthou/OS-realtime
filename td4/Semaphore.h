#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Mutex.h"

class Semaphore {
	public:
		Semaphore(unsigned int initCount, unsigned int maxCount);
		~Semaphore();
		void give();
		void flush();
		void take();
		bool take(double timeout_ms);

	protected:
		unsigned int counter;
		unsigned int maxCount;
		Mutex mutex;

	private:
};

#endif
