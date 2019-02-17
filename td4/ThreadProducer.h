#ifndef THREADPRODUCER_H
#define THREADPRODUCER_H

#include "Thread.h"
#include "Semaphore.h"

/*!
* Thread class to producing tokens into a semaphore object
*/


class ThreadProducer : public Thread
{
	protected:
		Semaphore& sem; /*!< Reference to a semaphore object*/
		int tokens_given; /*!< attribute to check execution of run*/
		int token_loop; /*!< number of tokens produced by this thread*/

		//! Running the thread to give tokens to the semaphore
		/*!
		\brief Give token_loop tokens to the semaphore, by calling the give method
		*/
		void run();

	public:
		//! Constructor with setting of attributes (tokens_given is initalised at 0)
		ThreadProducer(Semaphore& sem, int token_loop);

		//! Getter for tokens_given
		/*!
		\return tokens_given, int value of number of tokens given to the semaphore by this thread
		*/
		int getTokens();
};

#endif
