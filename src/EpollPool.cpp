#include <iostream>
#include <sys/epoll.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>

#include "EpollPool.h"

using namespace std;

EpollPool::EpollPool()
{
    message("hello");
}

EpollPool::~EpollPool()
{
    message("goodbye");
}

void EpollPool::run(int count)
{
    int epfd = epoll_create(count);
    if (epfd == -1)
        error("epoll_create error");

    while (--count >= 0)
    {
        int pipefd[2];

        if (pipe(pipefd) == -1)
            error("pipe error");

        if (fork() == 0)
        {
            close(pipefd[1]);
            serve(pipefd[0]);
            return;
        }
        else
        {
            close(pipefd[0]);

            static struct epoll_event ev;
            ev.events = EPOLLOUT;
            ev.data.fd = pipefd[1];

            if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipefd[1], &ev) == -1)
                error("epoll_ctl error");
        }
    }

    for(;;)
    {
        struct epoll_event events[1000];

        int nfds = epoll_wait(epfd, events, 1000, -1);

        if (nfds == 1)
            error("epoll_wait error");

        for (auto i = 0; i < nfds; ++i)
        {
            auto fd = events[i].data.fd;
            int random_number = 1 + rand() % 10000;
            write(fd, &random_number, sizeof(random_number));
        }
    }
}

void EpollPool::serve(int fd)
{
    message("started");
    for(;;)
    {
        int value;
        switch (read(fd, &value, sizeof(value)))
        {
            case 0:
                error("EOF");
                break;
            case -1:
                error("read error");
                break;
            default:
                message("do " + to_string(value));
                usleep(value);
        }
        message("done " + to_string(value));
    }
}

void EpollPool::error(string msg)
{
    cerr << getpid() << ": " << msg << endl;
    exit(-1);
}

void EpollPool::message(string msg)
{
    cout << getpid() << ": " << msg << endl;
}
