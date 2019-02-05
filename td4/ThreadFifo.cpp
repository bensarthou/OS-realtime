#include "ThreadFifo.h"


ThreadFifoProd::ThreadFifoProd(Fifo<int>& fifo_, int range_): fifo(fifo_), range(range_){}


void ThreadFifoProd::run()
{
	for(int i = 0; i<range; i++)
	{
		fifo.push(i);
	}
}


ThreadFifoCons::ThreadFifoCons(Fifo<int>& fifo_, double timeout_ms_): fifo(fifo_), timeout_ms(timeout_ms_){}


void ThreadFifoCons::run()
{
	bool emptyFifo = false;

	while(!emptyFifo)
	{
		try
		{
			received.push_back(fifo.pop(timeout_ms));
		}
		catch(Fifo<int>::EmptyException)
		{
			emptyFifo = true;
		}
	}
}


std::vector<int> ThreadFifoCons::getReceived()
{
    return received;
}
