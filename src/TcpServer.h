#ifndef ALEX_NET_TCPSERVER_H
#define ALEX_NET_TCPSERVER_H

#include <memory>
#include <map>
#include "TcpConnection.h"

namespace alex
{

class EventLoop;
class Acceptor;

class TcpServer
{

public:
    TcpServer(EventLoop* loop);
    ~TcpServer();

    void start(const char* ip, int port);

    void newConnection(int sockfd);

private:
    std::unique_ptr<Acceptor> acceptor_;
    EventLoop* loop_;

    typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;
    ConnectionMap connections_;

};

    
}

#endif