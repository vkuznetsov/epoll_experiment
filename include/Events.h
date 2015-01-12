#ifndef EVENTS_H
#define EVENTS_H

#include <string>

class Events
{
    public:
        Events();
        virtual ~Events();
        void error(std::string);
        void message(std::string);
    protected:
    private:
};

#endif // EVENTS_H
