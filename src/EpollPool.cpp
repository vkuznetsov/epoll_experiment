#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdlib.h>

#include "Events.h"
#include "EpollPool.h"
#include "Worker.h"

using namespace std;

EpollPool::EpollPool()
{
    events = new Events();
}

EpollPool::~EpollPool()
{
    delete events;
}

void EpollPool::start(int count)
{
    int epfd = epoll_create(count);
    if (epfd == -1)
        events->error("epoll_create error");

    while (--count >= 0)
    {
        int pipefd[2];

        if (pipe(pipefd) == -1)
            events->error("pipe error");

        if (fork() == 0)
        {
            close(pipefd[1]);
            Worker(pipefd[0], events).work();
            return;
        }
        else
        {
            close(pipefd[0]);

            static struct epoll_event ev;
            ev.events = EPOLLOUT;
            ev.data.fd = pipefd[1];

            if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipefd[1], &ev) == -1)
                events->error("epoll_ctl error");
        }
    }

    for(;;)
    {
        struct epoll_event epoll_events[MAX_EVENTS];

        int nfds = epoll_wait(epfd, epoll_events, MAX_EVENTS, -1);

        if (nfds == 1)
            events->error("epoll_wait error");

        for (int i = 0; i < nfds; ++i)
        {
            int fd = epoll_events[i].data.fd;
            int random_number = 1 + rand() % 10000;
            write(fd, &random_number, sizeof(random_number));
        }
    }
}
