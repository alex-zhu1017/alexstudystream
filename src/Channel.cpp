
#include "Channel.h"
#include "EventLoop.h"
#include <poll.h>
#include <iostream>
using namespace alex;


const int Channel::kNoneEvent =0;
const int Channel::kReadEvent = POLLIN |POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd)
    :loop_(loop)
    ,fd_(fd)
    ,events_(0)
    ,index_(-1)
{
}

Channel::~Channel()
{
}

void Channel::handleEvent(int events)
{
    if(events & POLLHUP) 
    {
        if(closeCallback_)
        {
            closeCallback_();
            return ;
        }
           
    }

    if(events & (POLLERR | POLLNVAL))
    {
        if (errorCallback_) errorCallback_();
    }

    if (events & (POLLIN | POLLPRI | POLLRDHUP))
    {
        std::cout << "recv read info " << std::endl;
        if (readCallback_) readCallback_();
    }

     if (events & POLLOUT)
    {
        if (writeCallback_) writeCallback_();
    }


}

void Channel::update()
{
    loop_->updateChannel(this);
}

void Channel::remove()
{
    loop_->removeChannel(this);
}