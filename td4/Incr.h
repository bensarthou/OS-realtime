#ifndef INCR_H
#define INCR_H

#include "Mutex.h"

/*!
* Incr class: increment a counter with a specific number of loop (counter not protected)
*/
class Incr
{
	protected:

		bool doStop; /*!< stop the loop when true */
		double* counter; /*!< pointer to a counter which will be incremented */

	public:

		//! Constructor by default
		/*!
		\brief Initialize attributes
		*/
		Incr();

		//! Constructor with reference to counter pointer
		/*!
		\brief ask a double*, variable to be incremented
		\param counter_, double pointer to be incremented
		*/
		Incr(double* counter_);


		//! Destructor by default
		~Incr();

		//! Run nloops number of loops
		/*!
		\brief Increment counter attribute nLoops time, without protection of the counter
		\param nLoops: double, number of time the counter will be incremented
		\return double* value of the counter at the end of the run
		*/
		double* runLoop(double nLoops);

		//! Getter for counter
		/*!
		\brief get the current value of counter
		\return double*, pointer to counter value
		*/
		double* getSample();

		//! Stop the loop and return counter value
		/*!
		\brief Set doLoop to false, stop runLoop if running and return counter pointer
		\return double*, pointer to counter value
		*/
		double* stopLoop();

};



/*!
* ProtectedIncr class: increment a counter a specific number of times, with mutex protection of
	the attribute
*/
class ProtectedIncr : public Incr
{

	private:
		Mutex& mutex; /*!< mutex object, to be used to protect the counter value during increment */

	public:

		// ! Constructor with reference to counter and mutex
		ProtectedIncr(double* counter_, Mutex& mutex);

		//! Run nloops number of loops, and protect incrementation with a mutex Lock
		/*!
		\brief Increment counter attribute nLoops time, and protect the incrementation
				from multiple access, by locking/unlocking the mutex
		\param nLoops: double, number of time the counter will be incremented
		\return double* value of the counter at the end of the run
		*/
		double* runLoop(double nLoops);

};


#endif
