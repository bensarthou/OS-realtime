#include "PeriodicTimer.h"

void PeriodicTimer::start(double duration_ms)
{
    struct itimerspec its;


    its.it_value.tv_sec= duration_ms/1000;
    its.it_value.tv_nsec = (duration_ms-its.it_value.tv_sec*1000)*1000000;
    its.it_interval = its.it_value;

    timer_settime(tid,0,&its,NULL);
}
