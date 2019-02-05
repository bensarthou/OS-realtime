#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <iostream>
#include <memory>

#include "ThreadFifo.h"
#include "Fifo.h"

using namespace std;

int main(int argc, char* argv[])
{
	(void)argc;

	cout << "Please input 4 values: nb of consumer tasks, timeout in ms for a consumer task,"
		 << " nb of producer tasks, nb of tokens given per producer task, " << endl;

	int nCons = atoi(argv[1]);
	double consTimeOut = atof(argv[2]);
	int nProd = atoi(argv[3]);
	int range = atoi(argv[4]);

	// Create a vector of producer threads and consumer threads
	std::vector<std::unique_ptr<ThreadFifoProd>> tabThProd(nProd);
	std::vector<std::unique_ptr<ThreadFifoCons>> tabThCons(nCons);

	Fifo<int> fifo;

	cout << endl << ">>>> Vector initialisation" << endl;
	cout << "Initialising vector of " << nProd << " producer tasks, creating " << range
		 << " tokens." << endl;

	for(auto& thProd : tabThProd)
	{
		thProd.reset(new ThreadFifoProd(fifo, range));
		thProd->start();
	}

	cout << "Initialising vector of " << nCons << " consumer tasks, consuming tokens until "
		 << consTimeOut << " ms has passed."<< endl;

	for(auto& thCons : tabThCons)
	 {
		thCons.reset(new ThreadFifoCons(fifo, consTimeOut));
		thCons->start();
	 }


	cout << endl << ">>>> Joining all the threads" << endl;

	for(auto& thProd : tabThProd)
	{
		thProd->join();
	}

	cout << "Consumer thread i has consumed: " << endl;
	for(auto& thCons : tabThCons)
	{
		thCons->join();
		vector<int> rec = thCons->getReceived();
		for (std::vector<int>::const_iterator i = rec.begin(); i != rec.end(); ++i)
			{
				cout << *i << ' ';
			}
	}

}
