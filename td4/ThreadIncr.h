#ifndef THREADINCR_H
#define THREADINCR_H

#include "Thread.h"
#include "Incr.h"

/*!
* Incrementer thread class, will run an incrementer object until stop (no mutex protection)
*/


class ThreadIncr: public Thread
{
	public:
		//! Constructor with definition of attributes
		/*!
		\brief Set the thread with an pointer to a non protected incrementer, and the number of loops
		*/
		ThreadIncr(Incr* incr, double nLoops);

	protected:
		//! Run the incrementer when the thread start
		/*!
		\brief At thread start, run the incrementer, to augment the counter value by nLoops
		*/
		void run();

	private:
		Incr* incr; /*!< Incrementer object, not protected*/
		double nLoops; /*!< Number of times the incrementer shall be increased*/
};


/*!
* Incrementer thread class, will run an incrementer object until stop (with mutex protection)
*/


class ThreadProtectedIncr: public Thread
{
	public:
		//! Constructor with definition of attributes
		/*!
		\brief Set the thread with an pointer to a protected incrementer, and the number of loops
		*/
		ThreadProtectedIncr(ProtectedIncr* incr, double nLoops);

	protected:
		//! Run the incrementer when the thread start
		/*!
		\brief At thread start, run the incrementer, to augment the counter value by nLoops
		*/
		void run();

	private:
		ProtectedIncr* incr; /*!< Incrementer object, protected with a mutex*/
		double nLoops; /*!< Number of times the incrementer shall be increased*/
};
#endif
