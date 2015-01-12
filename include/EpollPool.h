#ifndef EPOLLPOOL_H
#define EPOLLPOOL_H

class EpollPool
{
    public:
        EpollPool();
        virtual ~EpollPool();
        void run(int);
    protected:
    private:
        void serve(int);
        void error(std::string);
        void message(std::string);
};

#endif // EPOLLPOOL_H
