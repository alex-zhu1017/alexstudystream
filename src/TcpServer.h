#ifndef ALEX_NET_TCPSERVER_H
#define ALEX_NET_TCPSERVER_H

#include <memory>

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

};

    
}

#endif