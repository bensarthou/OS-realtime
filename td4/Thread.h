#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include <time.h>
#include <pthread.h>
#include "PosixThread.h"
#include "timespec_op.h"

/*!
* Trehad class, derived from PosixThread
*/

class Thread : public PosixThread
{
	private:
		struct timespec startTime, stopTime; /*!< timespec attribute to store the time when the thread is started/stopped */

		//! Call the virual method run
		/*!
		\brief Call the run method on a thread (only implemented in daughter class of Thread), and compute the exec time. return the thread.
		\param v_thread: pointer to a thread
		\return static void*: the thread executed
		*/
		static void* call_run(void* v_thread);

	protected:

		//! Virtual method defining what the thread do when started
		virtual void run()=0;

	public:

		//! Standard Constructor
		Thread();

		//! Standard Destructor
		~Thread();

		//! Pause method
		/*!
		\brief Pause the execution of the thread for delay_ms
		\param delay_ms: sleep time of the calling thread in ms
		*/
		static void sleep_ms(double delay_ms);

		//! Getter for start time
		/*!
		\brief return in ms the time at which the thread has been started
		\return double: time of start in ms.
		*/
		double startTime_ms();

		//! Getter for stop time
		/*!
		\brief return in ms the time at which the thread has been stopped
		\return double: time of stop in ms.
		*/
		double stopTime_ms();

		//! Getter for exec time
		/*!
		\brief return in ms the duration of the thread execution (measured in call_run)
		\return double: duration of execution.
		*/
		double execTime_ms();

		//! Start a thread running
		/*!
		\brief Start running a thread by calling call_run on the thread.
		*/
		void start();
};
#endif
