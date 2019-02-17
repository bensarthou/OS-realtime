#ifndef THREADCONSUMER_H
#define THREADCONSUMER_H

#include "Thread.h"
#include "Semaphore.h"

/*!
* Thread class for consuming tokens of a semaphore object
*/


class ThreadConsumer : public Thread
{
	private:
		Semaphore& sem; /*!< Reference to a semaphore object*/
		double timeout_ms; /*!< timeout time when trying to take a token, in ms */
		int approved; /*!< Number of tokens successfully taken, useful for debug*/
		int denied; /*!< Number of tokens that the thread timeouts to take*/

	protected:
		//! Running the thread to take tokens from the semaphore
		/*!
		\brief Take tokens from the semaphore, by calling the take method, until one call to take timeouts
		*/
		void run();

	public:
		//! Getter for approved
		/*!
		\return approved, int value of number of tokens successfully taken from the semaphore
		*/
		int getApproved();
		//! Getter for denied
		/*!
		\return denied, int value of number of tokens that thread timeouts to take.
		*/
		int getDenied();

		//! Constructor with setting of attributes (tokens_given is initalised at 0)
		ThreadConsumer(Semaphore& sem, double timeout_ms);
};

#endif
