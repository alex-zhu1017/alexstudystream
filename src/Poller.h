#ifndef ALEX_NET_POLLER_H
#define ALEX_NET_POLLER_H

#include "EventLoop.h"
#include <unordered_map>

namespace alex
{

class Channel;

class Poller
{
public:
    Poller(EventLoop* loop);
    virtual ~Poller();


    /// Changes the interested I/O events.
    /// Must be called in the loop thread.
    virtual void updateChannel(Channel* channel) = 0;

    /// Remove the channel, when it destructs.
    /// Must be called in the loop thread.
    virtual void removeChannel(Channel* channel) = 0;

    /// Polls the I/O events.
    /// Must be called in the loop thread.
    virtual void poll(int timeoutMs) = 0;

    static Poller* newDefaultPoller(EventLoop* loop);

protected:
    std::unordered_map<int, Channel*> channels_;


private:
    /* data */
    EventLoop* ownerLoop_;

};

}




#endif