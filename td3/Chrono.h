#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>
#include "timespec_op.h"

class Chrono
{
	private:

		timespec startTime_; // Time at the start (or restart) of the chronometer
		timespec stopTime_; // Time at the stop of the chronometer
		bool active; // describe if the chronometer is currently running or not

	public:

		/* Constructor */
		Chrono();

		/* Destructor */
		~Chrono();

		/* Stop the chronometer, set stopTime_ at the current time and isActive at false*/
		void stop();

		/* reset the chronometer (set startTime_ at current) and set isActive at true*/
		void restart();

		/* get active value (if the chronometer is running or not)*/
		bool isActive();

		/* getters, return startTime_, and stopTime_ values, in milliseconds*/
		double startTime();
		double stopTime();

		/* According if the chronometer is active or not, return current duration between start and
		   current time, or duration between startTime_ and stopTime_*/
		double lap();

};

#endif
