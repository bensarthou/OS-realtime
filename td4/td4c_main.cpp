#include <pthread.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>

#include "ThreadProducer.h"
#include "ThreadConsumer.h"
#include "Semaphore.h"

using namespace std;

int main(int argc, char* argv[])
{
	(void)argc;

	cout << "Please input 4 values: nb of consumer tasks, timeout in ms for a consumer task,"
		 << " nb of producer tasks, nb of tokens given per producer task, "
		 << "nb of max tokens for semaphore" << endl;

	int nCons = atoi(argv[1]);
	double consTimeOut = atof(argv[2]);
	int nProd = atoi(argv[3]);
	int nLoop = atoi(argv[4]);

	Semaphore sem(0);

	// Create a vector of producer threads and consumer threads
	std::vector<std::unique_ptr<ThreadProducer>> tabThProd(nProd);
	std::vector<std::unique_ptr<ThreadConsumer>> tabThCons(nCons);

	cout << endl << ">>>> Vector initialisation" << endl;
	cout << "Initialising vector of " << nProd << " producer tasks, creating " << nLoop
		 << " tokens." << endl;

	for(auto& thProd : tabThProd)
	{
		thProd.reset(new ThreadProducer(sem, nLoop));
		thProd->start();
	}

	cout << "Initialising vector of " << nCons << " consumer tasks, consuming tokens until "
		 << consTimeOut << " ms has passed."<< endl;

	for(auto& thCons : tabThCons)
	 {
		thCons.reset(new ThreadConsumer(sem, nLoop));
		thCons->start();
	 }

	cout << endl << ">>>> Joining all the threads" << endl;
	cout << "Producer thread i has produced:"<< endl;

	for(auto& thProd : tabThProd)
	{
		thProd->join();
		cout << " >> " << thProd->getTokens() << endl;
	}

	cout << "Consumer thread i has tried to consume: " << endl;
	for(auto& thCons : tabThCons)
	{
        cout << "trying to join" <<endl;
		thCons->join();
		cout << " >> " << thCons->getApproved() << " consumed, "
						   << thCons->getDenied() << " denied." << endl;
	}


}
