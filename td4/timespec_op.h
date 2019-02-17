#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <time.h>
#include <math.h>

#include <unistd.h>

/*!
\brief Convert time from timespec type to milliseconds (double)
\param time_ts: constant reference to a timespec struct, in which the time to be converted is stored
\return: double, time in milliseconds
*/
double timespec_to_ms(const timespec& time_ts);

/*!
\brief Convert time from milliseconds (double) to a timespec struct
\param time_ms: time in milliseconds, stored in double
\return: struct timespec, time_ms stored in a timespec struct
*/
timespec timespec_from_ms(double time_ms);

/*!
\brief Give current clock time in a struct timespec
\return: Current time, stored in timespec
*/
timespec timespec_now();

/*!
\brief return the negative time
\param time_ts: onstant reference to a timespec struct, in which the time to be converted is stored
\return: struct timespec, time_ms stored in a timespec struct
*/
timespec timespec_negate(const timespec& time_ts);

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);

timespec timespec_wait(const timespec& delay_ts);

timespec operator- (const timespec& time_ts);

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts);

timespec operator- (const timespec& time1_ts, const timespec& time2_ts);

timespec& operator+= (timespec& time_ts, const timespec& delay_ts);

timespec& operator-= (timespec& time_ts, const timespec& delay_ts);

bool operator== (const timespec& time1_ts, const timespec& time2_ts);

bool operator!= (const timespec& time1_ts, const timespec& time2_ts);

bool operator< (const timespec& time1_ts, const timespec& time2_ts);

bool operator> (const timespec& time1_ts, const timespec& time2_ts);

void print_timespec(const timespec& ts);
