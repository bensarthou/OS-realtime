#include "Semaphore.h"
#include "Mutex.h"


Semaphore::Semaphore(unsigned int initCount = 0, unsigned int maxCount)
{
	counter = initCount;
	maxCount = maxCount;
	mutex = Mutex(); // set condition ?

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
