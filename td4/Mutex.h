#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
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

    protected:

    private:
        pthread_mutex_t posixId;
        pthread_cond_t posixCondId; // TODO: ça sert à quoi ??
};

#endif
