#include "Poller.h"

using namespace alex;

Poller::Poller(EventLoop* loop)
    : ownerLoop_(loop)
{
    
}
Poller::~Poller() = default;