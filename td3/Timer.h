#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>
#include "timespec_op.h"

/*!
* Timer class: Object oriented encapsulation of POSIX timer 
*/


class Timer
{
	private:
		/*!
		\brief Wrapper for virtual callback
		\param sig: signal id
		\param si: pointer to Timer object
		\param user: unused ?
		*/
		static void call_callback(int sig, siginfo_t* si, void* user);

	public:

		/*!
		\brief Constructor, initiate the POSIX timer and all its attributes
		*/
		Timer();

		/*!
		\brief Destructor, delete timer
		*/
		~Timer();

		/*!
		\brief Start the timer with the specified duration
		\param duration_ms: duration of the timer, in ms
		*/
		void start(double duration_ms);

		/*!
		\brief Stop the timer
		*/
		void stop();

	protected:
		timer_t tid; /*!< ID to POSIX timer*/

		/*!
		\brief Virtual callback definition
		*/
		virtual void callback()=0;
};
#endif
