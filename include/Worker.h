#ifndef WORKER_H
#define WORKER_H

#include "Events.h"

class Worker
{
    public:
        Worker(int, Events*);
        virtual ~Worker();
        void work();
    protected:
    private:
        int fd;
        Events* events;
};

#endif // WORKER_H
