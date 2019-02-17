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
\param time_ts: constant reference to a timespec struct, in which the time to be negated is stored
\return: struct timespec, opposite time of time_ts
*/
timespec timespec_negate(const timespec& time_ts);

/*!
\brief Add two timespecs
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: struct timespec, result of time1_ts + time2_ts
*/
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Substract two timespecs
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: struct timespec, result of time1_ts - time2_ts
*/
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Makes the calling thread sleep for the time specified in delay_ts
\param delay_ts: constant reference to a timespec struct, time of the nanosleep
\return: struct timespec, resulting time of wait if nanosleep wasn't successfull
*/
timespec timespec_wait(const timespec& delay_ts);

/*!
\brief Negate a timespec variable (operator overload)
\param time_ts: constant reference to a timespec struct
\return: struct timespec, equal to -time_ts
*/
timespec operator- (const timespec& time_ts);

/*!
\brief Add two timespecs (operator overload)
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: struct timespec, result of time1_ts + time2_ts
*/
timespec operator+ (const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Substract two timespecs (operator overload)
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: struct timespec, result of time1_ts - time2_ts
*/
timespec operator- (const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Add a timespec to another
\param time_ts: reference to a timespec struct
\param delay_ts: constant reference to a timespec struct
\return: reference to time_ts, at which was added the value of delay_ts
*/
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);

/*!
\brief Substract a timespec to another
\param time_ts: reference to a timespec struct
\param delay_ts: constant reference to a timespec struct
\return: reference to time_ts, at which was substracted the value of delay_ts
*/
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);

/*!
\brief Check if two timespecs are equal
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: bool, result of the equal check
*/
bool operator== (const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Check if two timespecs are different
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: bool, result of the difference check
*/
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Check if a timespec is smaller than another one
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: bool, result of the operator check
*/
bool operator< (const timespec& time1_ts, const timespec& time2_ts);

/*!
\brief Check if a timespec is greater than another one
\param time1_ts, time2_ts: constant reference to a timespec struct
\return: bool, result of the operator check
*/
bool operator> (const timespec& time1_ts, const timespec& time2_ts);


/*!
\brief (Optional) Pretty print of a timespec, useful for debug
\param ts: constant reference to a timespec struct
*/
void print_timespec(const timespec& ts);
