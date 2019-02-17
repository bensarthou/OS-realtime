#ifndef LOOPER_H
#define LOOPER_H

/*!
* Looper class: Run a loop that increments a value
*/

class Looper
{
	private:

		bool doStop; /*!< stop the loop when true*/
		double iLoop; /*!< stores the number of loops executed*/

	public:

		/*!
		\brief Constructor
		*/
		Looper();

		/*!
		\brief Destructor
		*/
		~Looper();

		/*!
		\brief run a specific number of loops
		\param nLoops: range of the loop to be run
		*/
		double runLoop(double nLoops);

		/*!
		\brief Getter to iLoop: the current number of executed loops without stopping it
		\return current value of iLoop
		*/
		double getSample();

		/*!
		\brief Gets the current number of executed loops and stop the execution
		\return value of iLoop after ending loop
		*/
		double stopLoop();

};
#endif
