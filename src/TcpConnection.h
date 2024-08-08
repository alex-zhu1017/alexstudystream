#ifndef ALEX_NET_TCPCONNECTION_H
#define ALEX_NET_TCPCONNECTION_H

#include "Channel.h"

namespace alex
{

class EventLoop;

class TcpConnection
{
public:
    TcpConnection(EventLoop* loop, int fd) ;
    ~TcpConnection();

private:
    void handleRead();
    /* data */
    ChannelPtr channel_; 
    int fd_;

};

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    
}

#endif