#include "SocketUtil.h"
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace alex;

void SocketUtil::bind(int sockfd, const char* ip, int port)
{
    struct sockaddr_in addr_{0};
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip);
    addr_.sin_port = htons(port);

    int ret = ::bind(sockfd, (sockaddr*)(&addr_), sizeof(addr_));
    if(ret < 0)    
    {
        std::cout << "SocketUtil::bind" << std::endl;
    }

}

void SocketUtil::listen(int sockfd)
{
    int ret = ::listen(sockfd, SOMAXCONN);
    if(ret < 0)
    {
         std::cout << "SocketUtil::listen" << std::endl;
    }
}

void SocketUtil::connect(int sockfd, const char* ip, int port)
{
    struct sockaddr_in addr_{0};
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip);
    addr_.sin_port = htons(port);

    int ret = ::connect(sockfd, (sockaddr*)(&addr_), sizeof(addr_));
    if(ret < 0)
    {
         std::cout << "SocketUtil::connect" << std::endl;
    }
}

void SocketUtil::close(int sockfd)
{
    ::close(sockfd);
}

void SocketUtil::setNoBlockSocket(int sockfd)
{
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(sockfd, F_SETFL, flags);
}

void SocketUtil::setCloseOnExecSocket(int sockfd)
{
    int flags = ::fcntl(sockfd,F_GETFD, 0);
    flags |= FD_CLOEXEC;
    int ret = ::fcntl(sockfd, F_SETFD, flags);
}

    // TCP_NODELAY
void SocketUtil::setTcpNoDelay(int sockfd)
{
    int optval = 1;  // 1 , 0 
    ::setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY , &optval,sizeof(optval));
}

    // SO_REUSEADDR
void SocketUtil::setReuseAddr(int sockfd)
{
    int optval = 1;  // 1 , 0 
    ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

    // SO_REUSEPORT
void SocketUtil::setRequsePort(int sockfd)
{
    int optval = 1;  // 1 , 0 
    ::setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

    // SO_KEEPALIVE
void SocketUtil::setKeepAlive(int sockfd)
{
    int optval = 1;  // 1 , 0 
    ::setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}