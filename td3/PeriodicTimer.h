#include "Timer.h"
#include "timespec_op.h"

#include <time.h>

/*!
* PeriodicTimer class: object oriented POSIX timer, with periodic definition
*/

class PeriodicTimer : public Timer
{
	public:

		/* Overload the start method of Timer class: Sets a period equals to duration_ms */
		void start(double duration_ms);
};
