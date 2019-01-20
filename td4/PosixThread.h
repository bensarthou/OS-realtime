#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

#include <pthread.h>
#include <cstdlib>

class PosixThread
{
	private:

		pthread_t posixId;
		pthread_attr_t posixAttr;
		bool thread_started;

	public:
		/* Constructor, initialise the thread in posixId*/
		PosixThread();

		/* Copy constructor, use arg posixId to initalise the object thread*/
		PosixThread(pthread_t posixId);

		/* Destructor */
		~PosixThread();

		/* Start the thread with the function as arg*/
		void start(void* (*) (void *)threadFunc, void* threadArg);

		/* join the thread when done*/
		void join();

		/* join the thread after a certain timeout in ms*/
		bool join(double timeout_ms);

		/* Set scheduling param for the thread */
		bool setScheduling(int schedPolicy, int priority);

		/* get Scheduling param for the thread */
		bool getScheduling(int* p_schedPolicy=nullptr, int* p_priority=nullptr);
};




class Posix::Exception : public std::exception
{   public:
		Exception(const std:string& msg) : msg(msg)
		virtual const char* what() const noexcept {return msg.c_str()}
};

#endif
