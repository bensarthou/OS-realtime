#ifndef THREADFIFO_H
#define THREADFIFO_H

#include "Thread.h"
#include "Fifo.hpp"
#include <vector>

class ThreadFifoProd : public Thread
{

	public:
		ThreadFifoProd(Fifo<int>& fifo_, int range_);
	protected:
		void run();

	private:
		Fifo<int>& fifo;
		int range;
};


class ThreadFifoCons : public Thread
{

	public:
		ThreadFifoCons(Fifo<int>& fifo_, double timeout_ms_);
        std::vector<int> getReceived();

	protected:
		void run();

	private:
		std::vector<int> received;
		Fifo<int>& fifo;
		double timeout_ms;
};

#endif
