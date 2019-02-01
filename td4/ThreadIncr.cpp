#include "ThreadIncr.h"
#include "Mutex.h"

//constructeur
ThreadIncr::ThreadIncr(Incr* incr_, double nLoops_)
{
	incr = incr_;
	nLoops = nLoops_;
}

void ThreadIncr::run()
{
	(*incr).runLoop(nLoops);
}
