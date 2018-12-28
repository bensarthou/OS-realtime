#include "Looper.h"
#include <cfloat>
#include <iostream>

using namespace std;

Looper::Looper()
{
	doStop = false;
	iLoop = 0;
}

Looper::~Looper()
{
}

double Looper::runLoop(double nLoops=DBL_MAX)
{
	while ((iLoop<nLoops) && (doStop == false) )
	{
		iLoop++;
	}
	return iLoop;
}

double Looper::getSample()
{
	return iLoop;
}

double Looper::stopLoop()
{
	doStop=true;
	return iLoop;
}
