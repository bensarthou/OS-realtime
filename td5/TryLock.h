#ifndef TRYLOCK_H
#define TRYLOCK_H

#include "Mutex.h"

class TryLock : public Mutex::Lock
{

    public:
        TryLock(Mutex& m);
        ~TryLock();

    private:
        Mutex m;

    public:
        class Exception : public exception
        {
            public:
                Exception(const std::string& msg) : msg(msg){}
                virtual const char* what() const noexcept {return msg.c_str();}
            public:
                const std::string msg;
        };


};
#endif
