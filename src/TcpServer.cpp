#include "TcpServer.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include <functional>
#include <iostream>
using namespace alex;


void connection(int fd)
{

}
TcpServer::TcpServer(EventLoop* loop)
    :loop_(loop),
    acceptor_(new Acceptor(loop))
{
    acceptor_->SetNewConnectCallback(
      std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}

TcpServer::~TcpServer()
{
}

void TcpServer::start(const char* ip, int port)
{
    acceptor_->Listen(ip, port);
}
void TcpServer::newConnection(int sockfd)
{
    std::cout << "recv connection fd  " << sockfd <<  std::endl;
}