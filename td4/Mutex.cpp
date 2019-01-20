#include "Mutex.h"
#include <pthread.h>
#include "timespec_op.h"


/* Constructor */
Mutex()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&posixId, &attr);
}


/* Destructor */
~Mutex()
{
	pthread_mutex_destroy(&posixId);
}


/* lock the mutex */
void lock()
{
	pthread_mutex_lock(&posixId);
}


bool lock(double timeout_ms)
{

	struct timespec abs_time = timespec_now() + timespec_from_ms(timeout_ms);
	pthread_mutex_timedlock(&posixId, &abs_time)

}


bool trylock()
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


void unlock()
{
	pthread_mutex_unlock(&posixId);
}
