#include <iostream>
#include <pthread.h>
#include <cstring>


static void* dummyFunction(void*)
{
	return nullptr;
}

pthread_t get_INVALID_PTHREAD()
{
	static pthread_t INVALID_PTHREAD = 0;
	if (INVALID_PTHREAD == 0)
	{
		pthread_create(&INVALID_PTHREAD, nullptr, dummyFunction, nullptr);
		pthread_join(INVALID_PTHREAD, nullptr);
	}
	return INVALID_PTHREAD;
}


int main()
{
  // pthread_t myThread1;
  pthread_t myThread1 = get_INVALID_PTHREAD();
  int schedPolicy1;
  struct sched_param schedParam1;
  std::cout << "thread 1" << std::endl;
  int status1 = pthread_getschedparam(myThread1, &schedPolicy1, &schedParam1);
  // std::cout << "pthread_getschedparam() status : " << status1
  //           << " (" << std::strerror(status1) << ")" << std::endl;

  // pthread_t myThread2;
  pthread_t myThread2 = get_INVALID_PTHREAD();
  int schedPolicy2;
  struct sched_param schedParam2;
  std::cout << std::endl << "thread 2" << std::endl;
  int status2 = pthread_getschedparam(myThread2, &schedPolicy2, &schedParam2);
  // std::cout << "pthread_getschedparam() status : " << status2
  //           << " (" << std::strerror(status2) << ")" << std::endl;

  return 0;
}
