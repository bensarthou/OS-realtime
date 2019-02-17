#ifndef THREADFIFO_H
#define THREADFIFO_H

#include "Thread.h"
#include "Fifo.hpp"
#include <vector>

/*!
* Thread class to push value into a multi-threaded fifo
*/

class ThreadFifoProd : public Thread
{

	public:
		//! Constructor with setting of attributes
		ThreadFifoProd(Fifo<int>& fifo_, int range_);
	protected:
		//! Run the producer thread
		/*!
		\brief push the value from 0 to range into the Fifo referenced in this thread
		*/
		void run();

	private:
		Fifo<int>& fifo; /*!< Reference to a multi-threaded FIFO object of integer values*/
		int range; /*!< max value of the range values pushed into the FIFO*/
};

/*!
* Thread class to pop multi-threaded fifo
*/

class ThreadFifoCons : public Thread
{

	public:
		//! Constructor with setting of attributes
		ThreadFifoCons(Fifo<int>& fifo_, double timeout_ms_);

		//! Getter for received attribute
		/*!
		\return vector of int, vector of received values from popping the FIFO
		*/
		std::vector<int> getReceived();

	protected:
		//! Run the consumer thread
		/*!
		\brief pop values from the Fifo referenced in this thread until it is empty, pop are done with a timeout to ensure closure.
		*/
		void run();

	private:
		std::vector<int> received; /*!< vector where to store int values popped out the Fifo*/
		Fifo<int>& fifo; /*!< Reference to a multi-threaded FIFO object of integer values*/
		double timeout_ms; /*!< value of tiemout in ms used for pop elements of FIFO*/
};

#endif
