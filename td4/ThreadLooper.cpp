#include "ThreadLooper.h"


//constructeur
ThreadLooper::ThreadLooper(Looper* looper, double nLoops)  : Thread(SCHED_OTHER), looper(looper),nLoops(nLoops){}

void ThreadLooper::run()
{
	(*looper).runLoop(nLoops);
}
