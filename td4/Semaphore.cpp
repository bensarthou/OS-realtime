#include "Semaphore.h"
#include "Mutex.h"
#include <iostream>

Semaphore::Semaphore(unsigned int initCount, unsigned int maxCount_)
{
	counter = initCount;
	maxCount = maxCount_;
}


Semaphore::~Semaphore(){}


void Semaphore::give()
{
	Mutex::Lock lock(mutex);

	if(counter+1 <= maxCount)
	{
		counter++;
		lock.notify();
	}
}


void Semaphore::take()
{
	Mutex::Lock lock(mutex);

	while (counter <= 0)
	{
		lock.wait();
	}
	counter--;
}


bool Semaphore::take(double timeout_ms)
{
	Mutex::Lock lock(mutex);

	//TODO: measure real time before having a token given
	while (counter <= 0)
	{
		if(!lock.wait(timeout_ms))
		{
			return(false);
		}
	}
	counter--;
	return true;
}


unsigned int Semaphore::getCounter()
{
	return counter;
}
