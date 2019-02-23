#include "Countdown.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <time.h>

using namespace std;

int main(int, char* argv[])
{
	cout << "Please input starting value of counter:" << endl;
	int counter = atoi(argv[1]);
	Countdown countdown(&counter);
	cout << "Starting countdown of " << counter << " iterations"<< endl;

	countdown.start(1000.);

	while(counter>0){}

	cout <<"Countdown ended." << endl;
}
