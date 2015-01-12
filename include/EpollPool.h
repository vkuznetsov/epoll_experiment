#ifndef EPOLLPOOL_H
#define EPOLLPOOL_H

#include "Events.h"

class EpollPool
{
    public:
        EpollPool();
        virtual ~EpollPool();
        void start(int);
    protected:
    private:
        const int MAX_EVENTS = 1000;
        Events* events;
        void serve(int);
};

#endif // EPOLLPOOL_H
