#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

#include <pthread.h>
#include <cstdlib>
#include <exception>
#include <string>


/*!
* PosixThread class: object that encapsulate a pthread with its attribute
*/
class PosixThread
{
	public:
	    class Exception; /*!< nested Exception, to be raised when thread cannot be created */

	private:

    	pthread_t posixId; /*!< pthread attribute, id to the thread encapsulated */
    	pthread_attr_t posixAttr; /*!< pthread parameters to the thread */
    	bool thread_started; /*!<  bool, to check if the thread is running */

	public:

        //! Constructor by default
		/*!
		\brief initialize the pthread attribute and the parameters variable
		*/
    	PosixThread();

        //! Copy constructor
		/*!
		\brief copy a thread (and its parameters) from the id of a thread
        \param posixId: pthread_t, id of the copied thread
		*/
    	PosixThread(pthread_t posixId);

        //! Destructor
		/*!
		\brief destroy the attribute
        */
    	~PosixThread();

        //! Start the thread with the function as arg
		/*!
		\brief create a thread, run the function passed through threadFunc pointer,
                with the threadArg argument if specified
        \param threadFunc: pointer to the function (void *) to run
        \param threadArg: pointer to the arg used by threadFunc
		*/
    	void start(void* (*threadFunc) (void *), void* threadArg);

        //! join the thread when func is done
		/*!
		\brief join the thread by calling pthread_join, will wait that threadFunc has finished
        */
    	void join();

        //! join the thread when func is done, or if exec time is above timeout
		/*!
		\brief join the thread by calling pthread_join, will wait that threadFunc has finished or
                that timeout has passed
        \param timeout_ms: double value in ms of timeout duration
        \return bool: failure (or not) of joining the thread
        */
    	bool join(double timeout_ms);

    	/* Set scheduling param for the thread */
    	bool setScheduling(int schedPolicy, int priority);

    	/* get Scheduling param for the thread */
    	bool getScheduling(int* p_schedPolicy=nullptr, int* p_priority=nullptr);
};




class PosixThread::Exception : public std::exception
{   public:
		Exception(const std::string& msg) : msg(msg){}
		virtual const char* what() const noexcept {return msg.c_str();}
	public:
		const std::string msg;

};

#endif
