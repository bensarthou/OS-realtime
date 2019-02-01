#ifndef INCR_H
#define INCR_H

#include "Mutex.h"

class Incr
{
	protected:

		bool doStop; // stop the loop when true
		double* counter; // pointer to a counter which will be incremented

	public:

		/* Constructor */
		Incr();
		/* Constructor with passage of reference to the counter*/
		Incr(double* counter_);


		/* Destructor */
		~Incr();

		/* run a certain number of loops */

		double* runLoop(double nLoops);

		/* gets the current number of counter without stopping it */
		double* getSample();

		/* gets the current number of counter and stop the execution */
		double* stopLoop();

};


class ProtectedIncr : public Incr
{

	private:
		Mutex& mutex;

	public:

		/* Constructor with passage of reference to the counter, and mutex */
		ProtectedIncr(double* counter_, Mutex& mutex);


		/* run a certain number of loops, with mutex protecting the counter */
		double* runLoop(double nLoops);

};


#endif
