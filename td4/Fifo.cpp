#include "Fifo.h"

// template <class T>
// Fifo<T>::Fifo(){}
//
// template <class T>
// Fifo<T>::~Fifo(){}

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
	lock.wait();
	T temp_element = elements.front();
	elements.pop();

	return temp_element;
}


template <class T>
T Fifo<T>::pop(double timeout_ms)
{
	Mutex::Lock lock(mutex);
	if(lock.wait(timeout_ms))
	{
		T temp_element = elements.front();
		elements.pop();

		return temp_element;
	}
	else
	{
		throw Fifo::EmptyException();
	}
}

template class Fifo<int>;
