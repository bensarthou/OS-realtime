#ifndef Countdown_h_INCLUDED
#define Countdown_h_INCLUDED

#include "PeriodicTimer.h"

/*!
* Countdown class: Timer that decrement a counter until time is up
*/


class Countdown : public PeriodicTimer
{
	private:
		int* pCounter; /*!< pointer to value to be decremented during the timer execution*/

	protected:
		/*!
		\brief callback for countdown, decrement counter at each call
		*/
		void callback();

	public:

		/*!
		\brief Constructor, takes the pointer to the counter to be decremented as arg
		*/
		Countdown(int* pCounter);

		//! Destructor
		~Countdown();

};
#endif
