#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "Calibrator.h"

/*!
* Looper class: Run a loop that increments a value
*/


class CpuLoop : public Looper
{
	private:

		Calibrator& calibrator_; /*!< Loop calibrator object, already calibrated*/

	public:

		/*!
		\brief Constructor, takes an already calibrated calibrator object as attribute
		*/
		CpuLoop(Calibrator& calibrator);


		/*!
		\brief Destructor
		*/
		~CpuLoop();

		/*!
		\brief Run a loop for a duration_ms time, with the help of the calibrator coefficients
		\param duration_ms: duration the loop should run, in milliseconds
		*/
		void runTime(double duration_ms);
};

#endif
