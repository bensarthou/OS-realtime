#include "Countdown.h"
#include <cstdlib>
#include <cstdio>
#include <time.h>

Countdown::Countdown(int* pCounter)
{
	this->pCounter = pCounter;
}

Countdown::~Countdown()
{
}

void Countdown::callback()
{
	printf("Current value of counter: %d\n",*pCounter);
	(*pCounter)--;
}
