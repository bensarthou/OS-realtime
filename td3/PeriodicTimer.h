#include "Timer.h"
#include <time.h>

class PeriodicTimer : public Timer
{
	public:

		/* Overload the start method of Timer class: Sets a period equals to duration_ms */
		void start(double duration_ms);
};
