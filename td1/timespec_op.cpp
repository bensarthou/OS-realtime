#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <time.h>
#include <math.h>

#include <unistd.h>
#include "timespec_op.h"

using namespace std;

double timespec_to_ms(const timespec& time_ts)
{
	/*Convert timespec format to milliseconds*/
	double ms = 0.0;

	ms = time_ts.tv_sec*1000. + time_ts.tv_nsec/1000000.;

	return ms;
}


timespec timespec_from_ms(double time_ms)
{
	/*Convert milliseconds (in double) to timespec type*/

	struct timespec time_ts;

	// Convert to ns
	double time_ns = time_ms *1000000.;

	long temp_nsec = 0.0;
	long nsec = 0.0;
	time_t sec = 0;

	// Check for sign of time_ns
	if(time_ns >= 0)
	{
		// do euclidian division on integer part of nsec to get number of seconds
		nsec = ((long long int)floor(time_ns))%1000000000;

		sec = (time_t)((time_ns - nsec)/1000000000.);

	}
	else
	{
		time_ns = - time_ns;
		// do euclidian division on integer part of nsec to get number of seconds
		temp_nsec = ((long long int)floor(time_ns))%1000000000;
		sec = (time_t)((temp_nsec-time_ns)/1000000000.);

		// For negative values, decrement sec to add positive nsec
		sec = sec - 1;
		nsec = 1000000000. - temp_nsec;

	}

	time_ts.tv_sec = sec;
	time_ts.tv_nsec = nsec;

	return time_ts;
}


timespec timespec_now()
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts;
}


timespec timespec_negate(const timespec& time_ts)
{
	struct timespec ts;
	ts.tv_sec = -time_ts.tv_sec - 1;
	ts.tv_nsec = 1000000000. - time_ts.tv_nsec;
	return ts;
}


timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec res;
	// Calcul de la somme de 2 instants
	res.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;

	// Gestion du cas overflow des nanoseconds
	if (time1_ts.tv_nsec + time2_ts.tv_nsec >= 1000000000)
	{
		res.tv_sec += 1;
		res.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec - 1000000000;
	}
	else
	{
		res.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
	}

	return res;
}


timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
	struct timespec res;
	// Calcul de la différence de 2 instants
	res.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
	// Gestion du cas overflow des nanoseconds
	if (time1_ts.tv_nsec < time2_ts.tv_nsec)
	{
		res.tv_sec -= 1;
		res.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec + 1000000000;
	}
	else
	{
		res.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
	}

	return res;
}


timespec timespec_wait(const timespec& delay_ts)
{
	struct timespec res;

	res.tv_nsec = 0;
	res.tv_sec = 0.0;

	if(nanosleep(&delay_ts , &res) < 0 )
	{
		printf("Nano sleep system call failed \n");
		return res;
	}

	printf("Nano sleep successfull \n");

	return res;
}


timespec operator- (const timespec& time_ts)
{
	return timespec_negate(time_ts);
}


timespec operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_add(time1_ts, time2_ts);
}


timespec operator- (const timespec& time1_ts, const timespec& time2_ts)
{
	return timespec_subtract(time1_ts, time2_ts);
}


timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
	// Calcul de la somme de 2 instants
	time_ts.tv_sec = time_ts.tv_sec + delay_ts.tv_sec;

	// Gestion du cas overflow des nanoseconds
	if (time_ts.tv_nsec + delay_ts.tv_nsec > 1000000000)
	{
		time_ts.tv_sec += 1;
		time_ts.tv_nsec = time_ts.tv_nsec + delay_ts.tv_nsec - 1000000000;
	}
	else
	{
		time_ts.tv_nsec = time_ts.tv_nsec + delay_ts.tv_nsec;
	}

	return time_ts;
}


timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
	// Calcul de la différence de 2 instants
	time_ts.tv_sec = time_ts.tv_sec - delay_ts.tv_sec;
	// Gestion du cas overflow des nanoseconds
	if (time_ts.tv_nsec < delay_ts.tv_nsec)
	{
		time_ts.tv_sec -= 1;
		time_ts.tv_nsec = time_ts.tv_nsec - delay_ts.tv_nsec + 1000000000;
	}
	else
	{
		time_ts.tv_nsec = time_ts.tv_nsec - delay_ts.tv_nsec;
	}

	return time_ts;
}


bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
	if((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
	if((time1_ts.tv_sec != time2_ts.tv_sec) || (time1_ts.tv_nsec != time2_ts.tv_nsec))
	{
		return true;
	}
	else
	{
		return false;
	}

}


bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
	if (time1_ts.tv_sec < time2_ts.tv_sec)
	{
		return true;
	}
	else if ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec < time2_ts.tv_nsec))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
	if (time1_ts.tv_sec > time2_ts.tv_sec)
	{
		return true;
	}
	else if ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec > time2_ts.tv_nsec))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void print_timespec(const timespec& ts)
{
	printf("timespec:(%ld s, %ld ns) = %f ms\n",
			ts.tv_sec, ts.tv_nsec, ts.tv_sec*1000. + ts.tv_nsec/1000000.);
}
