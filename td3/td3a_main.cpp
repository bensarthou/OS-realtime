#include <cstdio>
#include <iostream>
#include "Chrono.h"
#include <unistd.h>
#include <time.h>

using namespace std;

int main()
{
	cout << "We will start, stop and reset timer every 5 seconds"
	Chrono chrono;
	int i = 0;
	while(i<10){
		cout<<"Chrono starts, timer is at "<<chrono.lap()<<" ms. We will pause 5 seconds"<<endl;
		sleep(5);
		chrono.stop();
		cout<<"Chrono stops, timer is at "<<chrono.lap()<<" ms."<<endl;
		chrono.restart();
		cout<< "Chrono restarts" <<endl;
		i++;
	}
}
