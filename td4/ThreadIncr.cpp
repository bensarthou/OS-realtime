#include "ThreadIncr.h"

//constructeur
ThreadProtectedIncr::ThreadProtectedIncr(ProtectedIncr* incr_, double nLoops_)
{
	incr = incr_;
	nLoops = nLoops_;
}

void ThreadProtectedIncr::run()
{
	(*incr).runLoop(nLoops);
}


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
