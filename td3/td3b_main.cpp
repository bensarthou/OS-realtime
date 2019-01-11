#include "Countdown.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <time.h>

using namespace std;

int main()
{
	int counter = 10;
	Countdown countdown(&counter);
	cout << "Starting countdown of " << counter << "iterations"<< endl;

	countdown.start(100.);

	while(counter>0){}

	cout <<"Countdown ended." << endl;
}
