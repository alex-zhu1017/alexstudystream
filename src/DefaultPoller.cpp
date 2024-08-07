#include "Poller.h"
#include "EPollPoller.h"

using namespace alex;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    return new EPollPoller(loop);
}