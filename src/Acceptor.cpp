#include "Acceptor.h"
#include "SocketUtil.h"

using namespace alex;

Acceptor::Acceptor(EventLoop* loop)
    :loop_(loop),
    acceptSocket_(new Socket())
{

}

Acceptor::~Acceptor()
{
    acceptChannel_->disableAll();
    acceptChannel_->remove();
}

void Acceptor::Listen(const char* ip, int port)
{
    int fd = acceptSocket_->create();
    SocketUtil::setNoBlockSocket(fd);
    SocketUtil::setCloseOnExecSocket(fd);
	SocketUtil::setRequsePort(fd);
	SocketUtil::setReuseAddr(fd);
    acceptChannel_.reset(new Channel(loop_, fd));
    acceptSocket_->bind(ip,port);
    acceptSocket_->listen();
    
    acceptChannel_->setReadCallback(std::bind(&Acceptor::handleRead, this));
    acceptChannel_->enableReading();

}

void  Acceptor::handleRead()
{
    int connfd = acceptSocket_->accept();
    if(connfd > 0)
    {
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd);
        }
        else
        {
            SocketUtil::close(connfd);
        }
    }
    else
    {
        SocketUtil::close(connfd);
    }
}