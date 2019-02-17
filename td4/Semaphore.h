#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Mutex.h"
#include <climits>

/*!
* Semaphore class
*/


class Semaphore {
	public:

		//! Constructor with definition of attributes
		/*!
		\brief Set the semaphore attribute at creation, with default values (Semophore with 0 tokens, as many as possible)
		*/
		Semaphore(unsigned int initCount = 0, unsigned int maxCount = UINT_MAX);

		//! Destructor by default
		~Semaphore();

		//! Give a token to a thread when asked
		/*!
		\brief This method gives a token: lock mutex and increment token counter if max is not reached
		*/
		void give();

		//! Take a token back when asked
		/*!
		\brief This method takes a token: Lock the mutex, and wait until a token is released to take him by decrementing counter
		*/
		void take();

		//! Try to take a token, can timeout
		/*!
		\brief This method is similar to take, except that the wait call on Mutex can timeout with the specified value.
		\param timeout_ms: double, time to timeout in ms
		\return bool: true if the token has been taken, false if not.
		*/
		bool take(double timeout_ms);

		//! Getter for counter
		/*!
		\return value of current counter attribute of the Semaphore
		*/
		unsigned int getCounter();

	protected:
		unsigned int counter; /*!< Number of current tokens the semaphore has, and that can be given to threads*/
		unsigned int maxCount; /*!< maximum number of tokens that the Semaphore can hold */
		Mutex mutex; /*!< Mutex object, to protect the access to the Semaphore*/

	private:
};

#endif
