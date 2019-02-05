#ifndef FIFO_H
#define FIFO_H

#include <exception>
#include <queue>
#include "Mutex.h"

// template <typename T, class Q = std::queue<T>>
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
		// Fifo();
		// ~Fifo();

		void push(T& element);

		T pop();

		T pop(double timeout_ms);

	protected:
		std::queue<T> elements;

	private:
		Mutex mutex;
};

#endif
