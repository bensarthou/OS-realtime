#include <cstdlib>
#include <iostream>
#include <time.h>

#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"

using namespace std;

int main()
{
	double duration_ms = 100.;
	unsigned int n_samples=1000;

	cout << "Duration of one period is " << duration_ms << " ms, we run "<< n_samples << " samples." << endl;
	cout << "Starting calibrator... " << endl;

	Calibrator calibrator(duration_ms, n_samples);

	cout << "Last value of loop is: " << calibrator.getLastValue() << endl;
	cout << "Estimated last value from calibration: " << calibrator.nLoops(n_samples*duration_ms) << endl;

	cout << "If the two are approximately equal, then we have successfully calibrated our loop" << endl;

	cout << "--------------------------" << endl;

	CpuLoop cpuloop_obj(calibrator);
	double duration_loop = 5000.;

	cout << "We will ask a " << duration_loop << " ms loop" << endl;

	// start a chrono to measure time
	Chrono chrono;
    cout<<"Chrono starts, timer is at "<< chrono.lap()<<" ms. Running "<< duration_loop << "ms loop" <<endl;

	// ask the cpu loop object to run the loop according to the calibration
	cpuloop_obj.runTime(duration_loop);

	// measure and print loop execution time
	chrono.stop();
	cout<<"Chrono stops, timer is at "<< chrono.lap()<<" ms."<<endl;


}
