#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include <exception>
#include <string>

using namespace std;

class Mutex
{

	private:
		pthread_mutex_t posixId;
		pthread_cond_t posixCondId;

	public:
		/* Constructor */
		Mutex();

		/* Destructor */
		~Mutex();

		/* lock the mutex */
		void lock();


		bool lock(double timeout_ms);
		bool trylock();
		void unlock();

	public:
		class Lock;
		class TryLock;
};



class Mutex::Lock
{
	class TimeoutException : public exception
	{
		public:
			TimeoutException(const std::string& msg) : msg(msg){}
			virtual const char* what() const noexcept {return msg.c_str();}
		public:
			const std::string msg;
	};

	public:
		/* Constructor */
		Lock(Mutex& m);
		Lock(Mutex& m, double timeout_ms);

		/* Destructor */
		~Lock();

		/* ask the thread to wait depending on the condition in posixCondId */
		void wait();

		/* ask the thread to wait depending on the condition in posixCondId */
		bool wait(double timeout_ms);

		/* notify the thread that the condition has freed */
		void notify();

		/* notify all threads that conditions have freed */
		void notifyAll();

	protected:

		Mutex& m;
};


class Mutex::TryLock : public Mutex::Lock
{
	public:
		TryLock(Mutex& m);

	public:
		class TimeoutException : public exception
		{
			public:
				TimeoutException(const std::string& msg) : msg(msg){}
				virtual const char* what() const noexcept {return msg.c_str();}
			public:
				const std::string msg;
		};

};


#endif
