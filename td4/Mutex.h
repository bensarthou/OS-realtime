#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include <exception>
#include <string>

using namespace std;


/*!
* Mutex class: object that encapsulate the pthread mutex object and its condition
*/

class Mutex
{

	private:
		pthread_mutex_t posixId; /*!< mutex ID of the object*/
		pthread_cond_t posixCondId; /*!< condition ID associated with the mutex at posixId */

	public:

		//! Constructor by default
		/*!
		\brief Set a mutex with its attribute (SCHED_RR by default) and initialize the mutex and the condition
		*/
		Mutex();

		//! Destructor
		/*!
		\brief Destroy the pthread mutex with the object
		*/
		~Mutex();

		//! lock
		/*!
		\brief Lock the phtread mutex, block if mutex is not lockable
		*/
		void lock();

		//! lock
		/*!
		\brief Lock the mutex, with a timeout. Method return false if mutex hasn't been locked at
		the end of timeout
		\param timeout_ms: double, time to timeout in ms
		\return bool: true if the mutex has been locked, false if not.
		*/
		bool lock(double timeout_ms);

		//! trylock
		/*!
		\brief Try to lock the mutex, return false if failure, true if success
		\return bool: true if the mutex has been locked, false if not
		*/
		bool trylock();

		//! unlock
		/*!
		\brief Unlock the mutex
		*/
		void unlock();

	public:
		class Lock; /*!< nested class, to lock the mutex*/
		class TryLock; /*!< nested class, to try to lock the mutex*/
};



/*!
* Lock class: object uses and lock a mutex during initialization, and unlock it at destruction
*/
class Mutex::Lock
{
	/*!
	* exception to be used in case of timeout when locking the mutex
	*/
	class TimeoutException : public exception
	{
		public:
			//! Constructor (string msg as param)
			TimeoutException(const std::string& msg) : msg(msg){}
			//! method to be called when catching exception
			virtual const char* what() const noexcept {return msg.c_str();}
		public:
			const std::string msg; /*!< string: msg to be displayed at exception*/
	};

	public:

		//! Constructor
		/*!
		\brief Lock the mutex attribute, with a blocking call to void lock()
		*/
		Lock(Mutex& m);

		//! Constructor with timeout
		/*!
		\brief lock the mutex attribute with a timeout lock, and raise TimeoutException if it failed
		*/
		Lock(Mutex& m, double timeout_ms);

		//! Destructor
		/*!
		\brief unlock the mutex
		*/
		~Lock();

		//! wait
		/*!
		\brief Ask the condition of the Mutex to wait a signal, to unlock the condition
		*/
		void wait();

		//! wait
		/*!
		\brief Ask the condition of the Mutex to wait a signal, to unlock the condition. Can timeout
		\param timeout_ms: double, time to timeout in milliseconds
		\return bool: status of wait, true if successful, false if not
		*/
		bool wait(double timeout_ms);

		//! notify
		/*!
		\brief notify the thread that the condition has freed
		*/
		void notify();

		//! notifyAll
		/*!
		\brief notify all threads that the condition has freed
		*/
		void notifyAll();

	protected:

		Mutex& m; /*!< Mutex object, that the class will (try to) lock when instanciated */

		//! Useless constructor, for use in TryLock(), without locking the mutex in constructor Lock()
		Lock(Mutex& m, bool useless);
};


/*!
* TryLock class: object uses and try to lock a mutex during initialization, and unlock it at destruction
*/
class Mutex::TryLock : public Mutex::Lock
{
	public:

		//! Constructor
		/*!
		\brief Try to lock the mutex attribute raise a timeout exception if it failed
		*/
		TryLock(Mutexy & m);

	public:
		/*!
		* exception to be used in case of timeout when locking the mutex
		*/
		class TimeoutException : public exception
		{
			public:
				//! Constructor (string msg as param)
				TimeoutException(const std::string& msg) : msg(msg){}
				//! method to be called when catching exception
				virtual const char* what() const noexcept {return msg.c_str();}
			public:
				const std::string msg; /*!< string: msg to be displayed at exception*/
		};

};


#endif
