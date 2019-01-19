#include "CpuLoop.h"

CpuLoop::CpuLoop(Calibrator& calibrator): calibrator_(calibrator)
{
}

CpuLoop::~CpuLoop()
{
}

void CpuLoop::runTime(double duration_ms)
{
	// get the number of loops you should do according to the calibrator l = a*t +b
	double l = calibrator_.nLoops(duration_ms);

	// run the according number of loops
	runLoop(l);

}
