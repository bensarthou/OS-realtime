#include "ThreadConsumer.h"

void ThreadConsumer::run(){
    while (!stop) {
        if (sem->take(timeout_ms)) {
            approved++;
        }
        else{
            denied++;
        }
    }
}

int ThreadConsumer::getApproved() {
    return(approved);
}

int ThreadConsumer::getDenied() {
    return(denied);
}

int ThreadConsumer::getID() {
    return(tid);
}

void ThreadConsumer::setStop(bool s) {
    stop = s;
}

ThreadConsumer::ThreadConsumer(Semaphore* sem, double timeout_ms): Thread(SCHED_OTHER), sem(sem), timeout_ms(timeout_ms), stop(false){
}
