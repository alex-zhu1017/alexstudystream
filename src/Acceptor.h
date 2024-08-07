#ifndef ALEX_NET_ACCEPTOR_h
#define ALEX_NET_ACCEPTOR_H

#include <functional>
#include "Socket.h"
#include <memory>
#include "Channel.h"

namespace alex
{

class EventLoop;


class Acceptor
{
public:
    typedef std::function<void(int)> NewConnectionCallback;

    Acceptor(EventLoop* loop);
    ~Acceptor();

    void SetNewConnectCallback(const NewConnectionCallback& cb)
    {
        newConnectionCallback_ = cb;
    }

    void Listen(const char* ip, int port);


private:
    void  handleRead();

    /* data */
    EventLoop* loop_;
    std::unique_ptr<Socket> acceptSocket_;
    ChannelPtr acceptChannel_;
    NewConnectionCallback newConnectionCallback_;

};



}


#endif