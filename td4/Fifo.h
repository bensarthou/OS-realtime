#ifndef FIFO_H
#define FIFO_H

#include <exception>

class Fifo
{
	class EmptyException : public exception
	{
		virtual const char* what() const throw()
		{
			return("Empty exception !");
		}
	};

	public:
		Fifo();
		~Fifo();
		void push

	protected:
		std::queue<T> elements;

	private:
};

#endif
