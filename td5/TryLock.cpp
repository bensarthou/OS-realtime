#include "TryLock.h"

TryLock::TryLock(Mutex& m): m(m)
{
	if(!(m.trylock()))
	{
		throw Exception("Mutex couldnt been locked");
	}
}
