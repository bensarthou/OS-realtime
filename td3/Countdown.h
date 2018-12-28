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
