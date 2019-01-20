#include <pthread.h>
#include <cstdlib>
#include "PosixThread.h"
#include "timespec_op.h"

PosixThread::PosixThread()
{
	pthread_attr_init(&posixAttr);
}


PosixThread::PosixThread(pthread_t posixId_)
{
	try {
		pthread_getschedparam(posixId_, 0, NULL);
	}
	// thread id not found
	catch(ESRCH)
	{
		throw(Posix::Exception('thread doesnt exist'));
	}

	posixId = posixId_;

	pthread_attr_init(&posixAttr);
}


PosixThread::~PosixThread()
{
	pthread_attr_destroy(&posixAttr);
}


void PosixThread::start(void* (*) (void *), void* threadArg)
{
	thread_started = true;
	pthread_create(posixId, posixAttr, threadFunc, threadArg);
}


void PosixThread::join()
{
	pthread_join(posixId, NULL);
}


bool PosixThread::join(double timeout_ms)
{

	pthread_timedjoin_np(posixId, NULL, timespec_from_ms(timeout_ms));
}


bool PosixThread::setScheduling(int schedPolicy, int priority)
{
	sched_param schedParams;
	schedParams.sched_priority = priority; // 0 si OTHER, entre 1..99 pour les autres
	pthread_attr_setschedpolicy(&attr, schedPolicy);

	pthread_attr_setschedparam(&attr, &schedParams);

	return thread_started;

}


bool PosixThread::getScheduling(int* p_schedPolicy=nullptr, int* p_priority=nullptr)
{
	sched_param schedParams;

	pthread_attr_getschedparam(&posixAttr, &schedParams);
	p_priority = &schedParams.sched_priority

	pthread_attr_getschedpolicy(&posixAttr, p_priority);
	return thread_started;
}
