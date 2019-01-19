#include "Calibrator.h"
#include <cfloat>

Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples)
{
	remainingSamples = nSamples;

	start(samplingPeriod_ms);

	looper.runLoop(DBL_MAX);

	//Here the loop takes the main thread, but the callback function of Calibrator
	//will call regurlaly getSample() and stopLoop() on the thread running the
	//periodicTimer instance
	a = (samples.back()-samples.front())/((nSamples-1)*samplingPeriod_ms);
	b = samples.back()-samplingPeriod_ms*a;
}


Calibrator::~Calibrator()
{
}


double Calibrator::nLoops(double duration_ms)
{
	return(a*duration_ms+b);
}


double Calibrator::getLastValue()
{
	return(samples.front());
}


void Calibrator::callback()
{
	if (remainingSamples>0)
	{
		samples.push_back(looper.getSample());
		remainingSamples--;
	}
	else
	{
		samples.push_back(looper.stopLoop());//Gets last counter value
		stop();//Stop the inner timer
	}
}
