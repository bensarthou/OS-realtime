#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <time.h>
#include <math.h>

#include <unistd.h>
#include "timespec_op.h"

using namespace std;

int main()
{

	struct timespec time1, time2, time3, time4;
	double ms = -3578.48912345;

	time1.tv_sec = -100;
	time1.tv_nsec = 75;

	time2.tv_sec = 5;
	time2.tv_nsec = 500000000.;

	time3.tv_sec = 2;
	time3.tv_nsec = 500000000.;

	time4.tv_sec = 5;
	time4.tv_nsec = 0.0;

	printf("----- Ms to timespec\n");
	print_timespec(timespec_from_ms(ms));
	printf("\n");

	printf("----- Timespec to ms\n");
	print_timespec(time1);
	printf("This timespec is equal to %f ms\n", timespec_to_ms(time1));
	printf("\n");

	printf("----- Timespec now\n");
	print_timespec(timespec_now());
	printf("\n");

	printf("----- Timespec negate\n");
	print_timespec(time1);
	printf("negates into:  \n");
	print_timespec(timespec_negate(time1));

	print_timespec(time2);
	printf("negates into:  \n");
	print_timespec(timespec_negate(time2));
	printf("\n");

	printf("----- Timespec addition\n");
	print_timespec(time1);
	printf("and \n");
	print_timespec(time2);
	printf("add into: \n");
	print_timespec(timespec_add(time1, time2));

	print_timespec(time2);
	printf("and \n");
	print_timespec(time3);
	printf("add into: \n");
	print_timespec(timespec_add(time2, time3));
	printf("\n");

	printf("----- Timespec substraction\n");
	print_timespec(time2);
	printf("and \n");
	print_timespec(time1);
	printf("substract into: \n");
	print_timespec(timespec_subtract(time2, time1));
	printf("\n");

	printf("------ TESTING OPERATORS --------- \n");
	print_timespec(time3);
	printf("+= \n");
	print_timespec(time1);
	time3 += time1;
	print_timespec(time3);
	printf("\n");

	print_timespec(time2);
	printf("-= \n");
	print_timespec(time1);
	time2 -= time1;
	print_timespec(time2);
	printf("\n");

	print_timespec(time1);
	printf("should be inferior to\n");
	print_timespec(time2);
	printf("%s\n", (time1 < time2) ? "true" : "false");
	printf("\n");

	print_timespec(time3);
	printf("should be superior to\n");
	print_timespec(time1);
	printf("%s\n", (time3 > time1) ? "true" : "false");
	printf("\n");

	double ms2 = 10000.000001;
	struct timespec ts_equal;
	ts_equal.tv_sec = 10;
	ts_equal.tv_nsec = 1;
	print_timespec(timespec_from_ms(ms2));
	printf("should be equal to\n");
	print_timespec(ts_equal);
	printf("%s\n", (ts_equal == timespec_from_ms(ms2)) ? "true" : "false");

	double ms3 = 10000.000002;
	print_timespec(timespec_from_ms(ms3));
	printf("should not be equal to\n");
	print_timespec(ts_equal);
	printf("%s\n", (ts_equal != timespec_from_ms(ms3)) ? "true" : "false");

	printf("\n------ TESTING WAIT FUNC --------- \n");
	printf("We'll print a loop that will pause for 5 secs\n");
	struct timespec res_sleep;

	for(int i=0; i<10; i++)
	{
		printf("iter %d\n", i);
		if (i==2)
		{
			res_sleep = timespec_wait(time4);
		}
	}

	printf("Leftover time in the nanosleep process\n");
	print_timespec(res_sleep);
}
