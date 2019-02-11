#ifndef FIFO_HPP
#define FIFO_HPP

#include <exception>
#include <queue>
#include "Mutex.h"
#include <iostream>

using namespace std;

/*!
* Fifo class: template fifo with multiple access
*/

template <class T>
class Fifo
{
	public:

		/*!
		* EmptyException class: Exception to be raised if fifo is empty and pop is called
		*/
		class EmptyException : public exception
		{
			//! method to be called when catching exception
			virtual const char* what() const throw()
			{
				return("Empty exception !");
			}
		};

	public:

		//! push to queue
		/*!
		\brief push a type T element to the queue, and notify the mutex condition if other threads
				are waiting to pop
		\param element: T variable to be pushed at queue front.
		*/
		void push(T& element);

		//! pop element of the queue
		/*!
		\brief pop the front element of the queue, by locking mutex.
					If queue is empty, wait for mutex cond to signal a new element
		\return T: variable of type T, popped value of the queue
		*/
		T pop();

		//! pop, with timeout
		/*!
		\brief pop the front element of the queue, by locking mutex.
					If queue is empty, wait for mutex cond to signal a new element.
					If wait timeout, raise EmptyException
		\param timeout_ms: double value, time to wait timeout
		\return T: variable of type T, popped value of the queue
		*/
		T pop(double timeout_ms);

	protected:
		std::queue<T> elements; /*!< template queue, that will stored the type T elements,
									and can be accessed by multiple threads */

	private:
		Mutex mutex; /*!< mutex object, used to protect the access to the queue */
};


template <class T>
void Fifo<T>::push(T& element)
{
	Mutex::Lock lock(mutex);
	elements.push(element);
	lock.notify();
}

template <class T>
T Fifo<T>::pop()
{
	Mutex::Lock lock(mutex);
	while(elements.empty())
	{
		lock.wait();
	}

	T temp_element = elements.front();
	elements.pop();

	return temp_element;
}


template <class T>
T Fifo<T>::pop(double timeout_ms)
{
	Mutex::Lock lock(mutex);

	while(elements.empty())
	{
		if(lock.wait(timeout_ms)){}
		else
		{
			throw Fifo::EmptyException();
		}
	}

	T temp_element = elements.front();
	elements.pop();

	return temp_element;

}

template class Fifo<int>;


#endif
