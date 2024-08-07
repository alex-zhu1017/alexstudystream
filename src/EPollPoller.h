#ifndef ALEX_NET_POLLER_EPOLLPOLLER_H
#define ALEX_NET_POLLER_EPOLLPOLLER_H

#include "Poller.h"
#include <sys/epoll.h>
#include <vector>

namespace alex
{
class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop* loop);
    ~EPollPoller() override ;

    void updateChannel(Channel* channel) override;

    void removeChannel(Channel* channel) override;

    void poll(int timeoutMs) override;

private:
    void update(int operation, Channel* channel);
    
    static const int kInitEventListSize = 1024;

    typedef std::vector<struct epoll_event> EventList;
    int epollfd_;
    EventList events_;
};

}

#endif