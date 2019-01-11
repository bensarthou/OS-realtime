#include <time.h>
#include <signal.h>
#include "timespec_op.h"

class Timer
{
	private:
		/* call_callback definition */
		static void call_callback(int sig, siginfo_t* si, void* user);

	public:

		/* Constructor, initiate the POSIX timer */
		Timer();

		/* Destructor */
		~Timer();

		/*Start the timer for duration duration_ms */

		void start(double duration_ms);

		/* Stop the timer */
		void stop();

	protected:
		timer_t tid; // POSIX timer

		/* Virtual callback definition, to be implemented in a derivate class */
		virtual void callback()=0;
};
