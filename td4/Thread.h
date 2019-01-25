#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include <time.h>
#include <pthread.h>
#include "PosixThread.h"
#include "timespec_op.h"


class Thread : public PosixThread
{
	private:
		static struct timespec startTime, stopTime;
		static void* call_run(void* v_thread);

	protected:

		virtual void run()=0;

	public:

		/* Constructor */
		Thread();

		/* Destructor */
		~Thread();

		/* Pause the execution of the thread for delay_ms */
		static void sleep_ms(double delay_ms);

		/* return in ms, the time of start, stop and the total execution time of the thread*/
		double startTime_ms();
		double stopTime_ms();
		double execTime_ms();

		void start();
};
#endif
