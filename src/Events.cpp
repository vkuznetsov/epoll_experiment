#include <iostream>
#include <unistd.h>

#include "Events.h"

using namespace std;

Events::Events()
{
    message("Hello");
}

Events::~Events()
{
    message("Goodbye");
}

void Events::error(string msg)
{
    cerr << getpid() << ": " << msg << endl;
    exit(-1);
}

void Events::message(string msg)
{
    cout << getpid() << ": " << msg << endl;
}
