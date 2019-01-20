#include <time.h>
#include <pthread.h>
#include "PosixThread.h"
#include "timespec_op.h"


Thread::Thread(){}
Thread::~Thread(){}

static void* Thread::call_run(void* v_thread)
{
	Thread* p_th = (Thread*) v_th;
	p_th->run();
	return v_th;
}


void start()
{
	startTime = timespec_now();
	PosixThread::start(); // TODO: arg ?
}

static void Thread::sleep_ms(double delay_ms)
{
	struct timespec delay = timespec_from_ms(delay_ms);
	totalSleepTime += delay;
	timespec_wait(delay);
}


double Thread::startTime_ms()
{
	return timespec_to_ms(startTime);
}


double Thread::stopTime_ms()
{
	// TODO: when to set stopTime ??
	return timespec_to_ms(stopTime);
}


double Thread::execTime_ms()
{
	struct timespec elapsedTime = stopTime - startTime - totalSleepTime;
	return timespec_to_ms(elapsedTime);
}
