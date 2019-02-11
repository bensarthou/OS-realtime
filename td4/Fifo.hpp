#ifndef FIFO_HPP
#define FIFO_HPP

#include <exception>
#include <queue>
#include "Mutex.h"
#include <iostream>

using namespace std;


template <class T>
class Fifo
{
	public:
		class EmptyException : public exception
		{
			virtual const char* what() const throw()
			{
				return("Empty exception !");
			}
		};

	public:

		void push(T& element);

		T pop();

		T pop(double timeout_ms);

	protected:
		std::queue<T> elements;

	private:
		Mutex mutex;
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
