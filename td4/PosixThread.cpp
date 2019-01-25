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
	sched_param schedParams;
	int policy;

	int error = pthread_getschedparam(posixId_, &policy, &schedParams);
	if(error==ESRCH)
	{
		// thread id not found
		throw(PosixThread::Exception("Thread doesnt exist"));
	}

	posixId = posixId_;

}


PosixThread::~PosixThread()
{
	pthread_attr_destroy(&posixAttr);
}


void PosixThread::start(void* (*threadFunc) (void *), void* threadArg)
{
	thread_started = true;
	pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
}


void PosixThread::join()
{
	pthread_join(posixId, NULL);
}


bool PosixThread::join(double timeout_ms)
{

	const timespec timeout = timespec_from_ms(timeout_ms);
	pthread_timedjoin_np(posixId, NULL, &timeout);
}


bool PosixThread::setScheduling(int schedPolicy, int priority)
{
	sched_param schedParams;
	schedParams.sched_priority = priority; // 0 si OTHER, entre 1..99 pour les autres

	sched_param schedParamsTest;
	int policy_test;

	int error = pthread_getschedparam(posixId, &policy_test, &schedParamsTest);
	if(error==ESRCH)
	{
		// thread is not active
		pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
		pthread_attr_setschedparam(&posixAttr, &schedParams);

		thread_started = false;
	}
	else
	{
		pthread_setschedparam(posixId, schedPolicy, &schedParams);
		thread_started = true;
	}

	return thread_started;
}


bool PosixThread::getScheduling(int* p_schedPolicy, int* p_priority)
{
	sched_param schedParams;
	int policy;

	// This code is only if thread is not active
	int error = pthread_getschedparam(posixId, &policy, &schedParams);
	if(error==ESRCH)
	{
		// thread is not active
		pthread_attr_getschedparam(&posixAttr, &schedParams);
		p_priority = &schedParams.sched_priority;

		pthread_attr_getschedpolicy(&posixAttr, p_priority);
		thread_started = false;
	}
	else
	{
		p_schedPolicy = &policy;
		p_priority = &schedParams.sched_priority;
		thread_started = true;
	}

	return thread_started;
}
