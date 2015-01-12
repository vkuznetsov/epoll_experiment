#include <iostream>
#include "EpollPool.h"

int main()
{
    EpollPool epoll_pool = EpollPool();

    try {
        epoll_pool.run(10);
    }
    catch (...)
    {
        exit(-1);
    }

    return 0;
}
