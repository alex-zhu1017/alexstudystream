
#include "EventLoop.h"
#include <functional>
#include "Poller.h"

using namespace alex;

const int kPollTimeMs = 10000;

EventLoop::EventLoop()
    :poller_(Poller::newDefaultPoller(this))
{
    thread_ = std::make_shared<std::thread>(std::bind(&EventLoop::threadfunc ,this));
}

EventLoop::~EventLoop()
{
    if(thread_->joinable())
        thread_->join();
}

void EventLoop::loop()
{
    looping_ = true;
    quit_ = false;
    while(!quit_)
    {
        poller_->poll(kPollTimeMs);
    }
}

void EventLoop::quit()
{
    quit_ = true;
}

void EventLoop::threadfunc()
{
    this->loop();
}

void EventLoop::updateChannel(Channel* channel)
{
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
    poller_->removeChannel(channel);
}