#include "Calibrator.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
	double duration_ms = 1000.;
	unsigned int n_samples=10;

	cout << "Starting calibration!" << endl;
	cout << "Duration of one period is 1s, for 10 samples." << endl;
	Calibrator calibrator(duration_ms,n_samples);

	cout << "Last value of loop is: " << calibrator.getLastValue() << endl;
	cout << "Estimated last value for 1s: " << calibrator.nLoops(duration_ms) << endl;
	cout << "So we see that everything works fine." << endl;

}
