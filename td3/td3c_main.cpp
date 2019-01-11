#include "Calibrator.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	double duration_ms = 1000.;
	unsigned int n_samples=10;

	cout << "Duration of one period is" << duration_ms << " ms, we run "<< n_samples << " samples." << endl;
	cout << "Starting calibrator... " << endl;

	Calibrator calibrator(duration_ms, n_samples);

	cout << "Last value of loop is: " << calibrator.getLastValue() << endl;
	cout << "Estimated last value from calibration: " << calibrator.nLoops(duration_ms) << endl;

	cout << "If the two are equal, then we have successfully calibrated our loop" << endl;

}

/* class Thread::Exception : public std::exception
 { public:
	Exception(const std:string& msg) : msg(msg)
	virtual const char* what() const noexcept {return msg.c_str()}
} */
