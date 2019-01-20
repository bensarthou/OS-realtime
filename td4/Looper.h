#ifndef LOOPER_H
#define LOOPER_H

class Looper
{
	private:

		bool doStop; // stop the loop when true
		double iLoop; // stores the number of loops

	public:

		/* Constructor */
		Looper();

		/* Destructor */
		~Looper();

		/* run a certain number of loops */

		double runLoop(double nLoops);

		/* gets the current number of executed loops without stopping it */
		double getSample();

		/* gets the current number of executed loops and stop the execution */
		double stopLoop();

};
#endif
