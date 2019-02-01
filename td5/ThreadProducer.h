#ifndef THREADPRODUCER_H
#define THREADPRODUCER_H

#include "Thread.h"
#include "Semaphore.h"

class ThreadProducer : public Thread
{
    protected:
        int tokens;
        int tokens_left;
        Semaphore* sem;
        void run();

    public:
        threadProd(int tokens, Semaphore* sem);
        int getRemaining();
};

#endif
