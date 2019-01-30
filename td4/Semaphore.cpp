#include "Semaphore.h"
#include <climits>
#include "Mutex.h"


Semaphore::Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT_MAX)
{
	counter = initCount;
	maxCount = maxCount;
	mutex = Mutex(); // set condition ?

}


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

	if (counter < 0)
	{
		counter--;
		lock.wait();
	}
}


bool Semaphore::take(double timeout_ms)
{
	Mutex::Lock lock(mutex);

	if (counter < 0)
	{
		counter--;
		if(!lock.wait(timeout_ms))
		{
			return(false);
		}

	}
	return(true);
}
