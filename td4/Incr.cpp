#include "Incr.h"
#include <cfloat>
#include <iostream>
#include <time.h>

using namespace std;

Incr::Incr()
{
	doStop = false;
	*counter = 0;
}

Incr::Incr(double* counter_)
{
	doStop = false;
	counter = counter_;
}


Incr::~Incr(){}

double* Incr::runLoop(double nLoops=DBL_MAX)
{
	int i = 0;
	while ((i<nLoops) && (doStop == false) )
	{
		*counter+= 1.0;
		i++;
	}
	return counter;
}

double* Incr::getSample()
{
	return counter;
}

double* Incr::stopLoop()
{
	doStop=true;
	return counter;
}
