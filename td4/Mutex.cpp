#include "Mutex.h"
#include <pthread.h>
#include "timespec_op.h"


/* Constructor */
Mutex::Mutex()
{
	// TODO: may be missing condition (or the way to set it)
	pthread_mutexattr_t attr;
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&posixId, &attr);
}


/* Destructor */
Mutex::~Mutex()
{
	pthread_mutex_destroy(&posixId);
}


/* lock the mutex */
void Mutex::lock()
{
	pthread_mutex_lock(&posixId);
}


bool Mutex::lock(double timeout_ms)
{
	struct timespec abs_time = timespec_now() + timespec_from_ms(timeout_ms);
	if (pthread_mutex_timedlock(&posixId, &abs_time) == ETIMEDOUT)
	{
		return false;
	}
	return true;
}


bool Mutex::trylock()
{
	if(pthread_mutex_trylock(&posixId) == 0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}


void Mutex::unlock()
{
	pthread_mutex_unlock(&posixId);
}



/*****************************************/
/*               Lock                    */
/*****************************************/


Mutex::Lock::Lock(Mutex& mutex) : m(mutex)
{
	m.lock();
}


Mutex::Lock::Lock(Mutex& mutex, bool useless) : m(mutex){}


Mutex::Lock::Lock(Mutex& mutex, double timeout_ms) : m(mutex)
{
	if(!(m.lock(timeout_ms)))
	{
		throw TimeoutException("Lock for mutex has timeout");
	}
}


Mutex::Lock::~Lock()
{
	m.unlock();
}


void Mutex::Lock::wait()
{
	pthread_cond_wait(&(m.posixCondId), &(m.posixId));
}


bool Mutex::Lock::wait(double timeout_ms)
{
	struct timespec abs_time = timespec_now() + timespec_from_ms(timeout_ms);

	if(pthread_cond_timedwait(&(m.posixCondId), &(m.posixId), &abs_time) == ETIMEDOUT)
	{
		return false;
	}
	return true;
}


void Mutex::Lock::notify()
{
	pthread_cond_signal(&(m.posixCondId));
}


void Mutex::Lock::notifyAll()
{
	pthread_cond_broadcast(&(m.posixCondId));
}



/*****************************************/
/*               TryLock               */
/*****************************************/


Mutex::TryLock::TryLock(Mutex& mutex) : Mutex::Lock(mutex, true)
{
	if(!(mutex.trylock()))
	{
		throw TimeoutException("Mutex couldnt been locked");
	}
}
