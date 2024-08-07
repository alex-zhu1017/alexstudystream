#ifndef ALEX_NET_CHANNEL_H
#define ALEX_NET_CHANNEL_H

#include <functional>
#include <memory>

namespace alex
{

class EventLoop;

///
/// A selectable I/O channel.
///
/// This class doesn't own the file descriptor.
/// The file descriptor could be a socket,
/// an eventfd, a timerfd, or a signalfd

class Channel
{
public:
    typedef std::function<void()>  EventCallback;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    // 事件就绪处理函数
    void handleEvent(int events);

    int fd() const { return fd_; }

    void setReadCallback(EventCallback cb)
    {
        readCallback_ = std::move(cb);
    }

    void setWriteCallback(EventCallback cb)
    {
         writeCallback_ = std::move(cb);
    }

    void setCloseCallback(EventCallback cb)
    {
         closeCallback_ = std::move(cb);
    }

    void setErrorCallback(EventCallback cb)
    {
         errorCallback_ = std::move(cb);
    }

    void enableReading(){ events_ |= kReadEvent; update();}
    void disableReading(){events_ |=~kReadEvent; update();}
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isReading() const { return events_ & kReadEvent; }

    void update();

    void remove();

    bool isNoneEvent() const { return events_ == kNoneEvent; }

    int events() const { return events_; }
    // for Poller
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    const int  fd_;
    EventLoop* loop_;
    int        events_;
    int        index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

typedef std::shared_ptr<Channel> ChannelPtr;
}

#endif