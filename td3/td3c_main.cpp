#include <cstdlib>
#include <iostream>
#include <time.h>

#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"

using namespace std;

int main()
{
	double duration_ms = 1000.;
	unsigned int n_samples=10;

	cout << "Duration of one period is " << duration_ms << " ms, we run "<< n_samples << " samples." << endl;
	cout << "Starting calibrator... " << endl;

	Calibrator calibrator(duration_ms, n_samples);

	cout << "Last value of loop is: " << calibrator.getLastValue() << endl;
	cout << "Estimated last value from calibration: " << calibrator.nLoops(duration_ms) << endl;

	cout << "If the two are equal, then we have successfully calibrated our loop" << endl;

	cout << "--------------------------" << endl;

	CpuLoop cpuloop_obj(calibrator);
	double duration_loop = 5000.;

	cout << "We will ask a " << duration_loop << " ms loop" << endl;

	// start a chrono to measure time
	Chrono chrono;

	// ask the cpu loop object to run the loop according to the calibration
	cpuloop_obj.runLoop(duration_loop);

	// measure and print loop execution time
	chrono.stop();
	cout<<"Chrono stops, timer is at "<< chrono.stopTime()<<" ms."<<endl;


}

/* class Thread::Exception : public std::exception
 { public:
	Exception(const std:string& msg) : msg(msg)
	virtual const char* what() const noexcept {return msg.c_str()}
} */
