#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "Calibrator.h"

class CpuLoop : public Looper
{
	private:

		/* Calibrator, already calibrate the loop with a and b*/
		Calibrator& calibrator_;

	public:

		/* Constructor */
		CpuLoop(Calibrator& calibrator);


		/* Destructor */
		~CpuLoop();

		/* run a loop for a duration_ms time, with the help of the calibrator coefficients*/
		void runTime(double duration_ms);
};

#endif
