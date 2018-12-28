#include "Timer.h"

Timer::Timer()
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction=call_callback;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = this;
	timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
	timer_delete(tid);
}


void Timer::start(double duration_ms)
{

	struct itimerspec its;
	its.it_value.tv_sec= duration_ms/1000;
	its.it_value.tv_nsec = (duration_ms-its.it_value.tv_sec*1000)*1000000;
	its.it_interval.tv_sec=0;
	its.it_interval.tv_nsec = 0;
	timer_settime(tid,0,&its,NULL);
}


void Timer::stop()
{
	struct itimerspec stop;
	stop.it_value.tv_sec = 0;
	stop.it_value.tv_nsec = 0;
	stop.it_interval.tv_sec = 0;
	stop.it_interval.tv_nsec = 0;
	timer_settime(tid,0,&stop,NULL);
}


void Timer::call_callback(int sig, siginfo_t* si, void*)
{
	Timer* timer = (Timer*) si->si_value.sival_ptr;
	timer->callback();
}
