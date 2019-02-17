#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include "PeriodicTimer.h"
#include "Looper.h"

#include <vector>

/*!
* Calibrator class: Use a periodic timer to calibrate a loop: compute the parameters making the
* relation between number of loop and exec time
*/


class Calibrator : public PeriodicTimer
{
	private:
		// l(t) = a*t+b
		double a; /*!< slope factor of the relationship between time and number of loop */
		double b; /*!< intercept factor of the relationship  between time and number of loop*/


		double r; /*!< regression factor*/

		std::vector<double> times; /*!< vector storing times at wich values are sampled*/

		std::vector<double> samples; /*!< Vector storing all sampled values*/

		Looper looper; /*!< Looper object to be calibrated */
		unsigned int remainingSamples; /*!< remaining number of loops to be done */

	protected:

		/*!
		\brief Measures parameters a and b of Looper::runLoop during time t:
		called function is getSample if there are still samples to do,
		Looper::stopLoop() if not.
		*/
		void callback();

	public:

		//! Constructor:
		/*!
		\brief Runs a periodic timer with samplingPeriod_ms / nSamples period, and
		compute a and b values from it.
		\param samplingPeriod_ms: double, period for the timer
		\param nSamples: int, number of samples to do in the loop
		*/
		Calibrator(double samplingPeriod_ms, unsigned int nSamples);

		//! Destructor
		~Calibrator();

		/*!
		\brief Convert a duration in milliseconds onto a number of loops with l(t) = a*t+b
		\param duration_ms: time duration in milliseconds
		\return number of loops to do, to reach the exec duration
		*/
		double nLoops(double duration_ms);

		/*!
		\brief Getter for last value of loop
		\return last value stored in samples
		*/
		double getLastValue();
};
#endif
