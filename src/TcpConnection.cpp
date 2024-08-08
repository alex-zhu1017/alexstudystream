#include "TcpConnection.h"
#include "SocketUtil.h"
#include <functional>
#include <iostream>
#include "EventLoop.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

using namespace alex;
TcpConnection::TcpConnection(EventLoop* loop, int fd)  
{
    SocketUtil::setNoBlockSocket(fd);
    SocketUtil::setCloseOnExecSocket(fd);
	SocketUtil::setRequsePort(fd);
	SocketUtil::setReuseAddr(fd);
    channel_.reset(new Channel(loop, fd));
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this));
    channel_->enableReading();

    fd_ = fd;
}

TcpConnection::~TcpConnection()
{
    channel_->disableAll();
    channel_->remove();
}

void TcpConnection::handleRead()
{
    char buf[1024];
    memset(buf ,0x00, 1024);
    size_t ret = ::read(fd_, buf, 1024);

    std::cout << "msg : " << buf << " size: " << ret <<  std::endl;
}