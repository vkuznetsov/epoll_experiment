#include <unistd.h>

#include "Events.h"
#include "Worker.h"

Worker::Worker(int fd, Events * events)
{
    this->fd = fd;
    this->events = events;
}

Worker::~Worker()
{
    //dtor
}

void Worker::work()
{
    events->message("started");
    for(;;)
    {
        int value;
        switch (read(fd, &value, sizeof(value)))
        {
            case 0:
                events->error("EOF");
                break;
            case -1:
                events->error("read error");
                break;
            default:
                events->message("do " + std::to_string(value));
                usleep(value);
        }
        events->message("done " + std::to_string(value));
    }
}
