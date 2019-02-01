#include <time.h>
#include <pthread.h>
#include "PosixThread.h"
#include "Thread.h"
#include "timespec_op.h"


Thread::Thread(){}
Thread::~Thread(){}

void* Thread::call_run(void* v_thread)
{
	Thread* p_th = (Thread*) v_thread;
	p_th->startTime = timespec_now();
	p_th->run();
	p_th->stopTime = timespec_now();
	return v_thread;
}


void Thread::start()
{
	PosixThread::start(call_run, (void*) this);
}


void Thread::sleep_ms(double delay_ms)
{
	struct timespec delay = timespec_from_ms(delay_ms);
	timespec_wait(delay);
}


double Thread::startTime_ms()
{
	return timespec_to_ms(startTime);
}


double Thread::stopTime_ms()
{
	return timespec_to_ms(stopTime);
}


double Thread::execTime_ms()
{
	struct timespec elapsedTime = stopTime - startTime;
	return timespec_to_ms(elapsedTime);
}
