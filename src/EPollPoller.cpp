#include "EPollPoller.h"
#include <unistd.h>
#include <iostream>
#include "Channel.h"
#include  <assert.h>
#include <string.h>

using namespace alex;

namespace
{
const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;
}

EPollPoller::EPollPoller(EventLoop* loop)
    :Poller(loop),
     events_(kInitEventListSize)
{
    epollfd_ = ::epoll_create1(EPOLL_CLOEXEC);
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}


void EPollPoller::updateChannel(Channel* channel)
{
    const int index = channel->index();
    if(index == kNew || index == kDeleted)
    {
        // a new one, add with EPOLL_CTL_ADD
        int fd = channel->fd();
        if (index == kNew)
        {
            assert(channels_.find(fd) == channels_.end());
            channels_[fd] = channel;
        }
        else // index == kDeleted
        {
            assert(channels_.find(fd) != channels_.end());
            assert(channels_[fd] == channel);
        }

        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        // update existing one with EPOLL_CTL_MOD/DEL
        int fd = channel->fd();
        (void)fd;
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] == channel);
        assert(index == kAdded);
        if(channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPollPoller::removeChannel(Channel* channel)
{
    // 判断是否在当前loop线程
    int fd = channel->fd();
    //LOG_TRACE << "fd = " << fd;
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    assert(channel->isNoneEvent());
    int index = channel->index();
    assert(index == kAdded || index == kDeleted);

    size_t n = channels_.erase(fd);
    (void)n;
    assert(n == 1);

    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

void EPollPoller::poll(int timeoutMs)
{
    struct epoll_event events[512] = {0};
    int numEvnets = ::epoll_wait(epollfd_, events, 512, timeoutMs);
    //int numEvnets = ::epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeoutMs);
    int savedErrno = errno;
    if(numEvnets > 0)
    {
        // 暂时不考虑有很多事件触发
        // for(int i = 0; i < numEvnets; ++i)
        // {
        //     Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        //     channel->handleEvent(events_[i].events);
            
        // }
        std::cout<< "recv events happend" << std::endl;
         for(int i = 0; i < numEvnets; ++i)
        {
            Channel* channel = static_cast<Channel*>(events[i].data.ptr);
            channel->handleEvent(events[i].events);
            
        }
    }
    else if(numEvnets == 0)
    {
        std::cout<< "nothing happend" << std::endl;
    }
    else
    {
        if (savedErrno != EINTR)
        {
            errno = savedErrno;
            std::cout << "EPollPoller::poll()" << std::endl;
        }
    }
}

void EPollPoller::update(int operation, Channel* channel)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.ptr= channel;
    event.events = channel->events();
    int fd = channel->fd();
    int ret = ::epoll_ctl(epollfd_, operation, fd, &event);
    if(ret < 0)
    {
         if (operation == EPOLL_CTL_DEL)
        {
            std::cout << "epoll_ctl op =" << operationToString(operation) << " fd =" << fd;
        }
        else
        {
            std::cout << "epoll_ctl op =" << operationToString(operation) << " fd =" << fd;
        }
    }
    else
    {
        std::cout << "epoll_ctl op =" << operationToString(operation) << " fd =" << fd;
    }

}

const char* EPollPoller::operationToString(int op)
{
  switch (op)
  {
    case EPOLL_CTL_ADD:
      return "ADD";
    case EPOLL_CTL_DEL:
      return "DEL";
    case EPOLL_CTL_MOD:
      return "MOD";
    default:
      assert(false && "ERROR op");
      return "Unknown Operation";
  }
}