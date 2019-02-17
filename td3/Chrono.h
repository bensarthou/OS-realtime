#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>
#include "timespec_op.h"

/*!
* Chrono class: encapsulation of a chronometer using timespec
*/


class Chrono
{
	private:

		timespec startTime_; /*!< Time at the start (or restart) of the chronometer */
		timespec stopTime_; /*!< Time at the stop of the chronometer */
		bool active; /*!< describe if the chronometer is currently running or not*/

	public:

		/*! Constructor
		\brief: initialize startTime at current clock, stopTime at 0
		*/
		Chrono();

		//! Destructor
		~Chrono();

		/*!
		\brief Stop the chronometer, set stopTime_ at the current time and isActive at false
		*/
		void stop();

		/*!
		\brief reset the chronometer (set startTime_ at current) and set isActive at true
		*/
		void restart();

		/*!
		\brief Getter for attribute active
		\return bool active
		*/
		bool isActive();

		/*!
		\brief Getter for startTime_
		\return: value of startTime_ in milliseconds
		*/
		double startTime();

		/*!
		\brief Getter for stopTime_
		\return: value of stopTime_ in milliseconds
		*/
		double stopTime();

		/*!
		\brief According if the chronometer is active or not, return current duration between start and
		   current time, or duration between startTime_ and stopTime_
		\return double: duration as specified above, in milliseconds
		*/
		double lap();

};

#endif
