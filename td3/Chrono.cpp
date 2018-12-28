#include <time.h>
#include "timespec_op.h"
#include "Chrono.h"


/* Constructor */
Chrono::Chrono()
{
    startTime_ = timespec_now();
    stopTime_ = timespec_from_ms(0.0);

    active = true;
}

/* Destructor */
Chrono::~Chrono()
{

}

/* Stop the chronometer, set stopTime_ at the current time and isActive at false*/
void Chrono::stop()
{
    stopTime_ = timespec_now();
    active = false;

}


/* reset the chronometer (set startTime_ at current) and set isActive at true*/
void Chrono::restart()
{
    startTime_ = timespec_now();
    active = true;

}

/* get active value (if the chronometer is running or not)*/
bool Chrono::isActive()
{
    return active;
}

/* getters, return startTime_, and stopTime_ values, in milliseconds*/
double Chrono::startTime()
{
    return timespec_to_ms(startTime_);
}
double Chrono::stopTime()
{
    return timespec_to_ms(stopTime_);
}

/* According if the chronometer is active or not, return current duration between start and
   current time, or duration between startTime_ and stopTime_*/
double Chrono::lap()
{
    if(!active)
    {
        return timespec_to_ms(stopTime_ - startTime_);
    }
    else
    {
        return timespec_to_ms(timespec_now() - startTime_);
    }
}
