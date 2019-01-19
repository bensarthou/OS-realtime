#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include "PeriodicTimer.h"
#include "Looper.h"

#include <vector>

class Calibrator : public PeriodicTimer
{
	private:
		// l(t) = a*t+b
		double a;
		double b;

		// Vector storing all sampled values
		std::vector<double> samples;

		Looper looper;
		unsigned int remainingSamples;

	protected:

		/* measures parameters a and b of Looper::runLoop during time t:
		called function is getSample if there are still samples to do,
		Looper::stopLoop() if not. */

		void callback();

	public:

		/* Constructor:
		Runs a periodic timer with samplingPeriod_ms / nSamples period, and
		compute a and b values from it. */
		Calibrator(double samplingPeriod_ms, unsigned int nSamples);

		/* Destructor */
		~Calibrator();

		/* Convert a duration in milliseconds onto a number of loops with l(t) = a*t+b */
		double nLoops(double duration_ms);

		/* Gets last value of loop */
		double getLastValue();
};
#endif
