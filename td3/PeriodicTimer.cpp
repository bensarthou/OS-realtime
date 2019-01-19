#include "PeriodicTimer.h"
#include "timespec_op.h"

void PeriodicTimer::start(double duration_ms)
{
	struct itimerspec its;

	its.it_value = timespec_from_ms(duration_ms);
	its.it_interval = timespec_from_ms(duration_ms);

	timer_settime(tid, 0, &its,NULL);
}
