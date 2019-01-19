#ifndef Countdown_h_INCLUDED
#define Countdown_h_INCLUDED

#include "PeriodicTimer.h"

class Countdown : public PeriodicTimer
{
	private:
		int* pCounter;

	protected:
		void callback();

	public:
		Countdown(int* pCounter);
		~Countdown();

};
#endif
