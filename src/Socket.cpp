#include "Socket.h"

#include <sys/socket.h>
#include <unistd.h> // 包含close 函数
#include <iostream>
#include "SocketUtil.h"
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace alex;


Socket::~Socket()
{
    if(::close(sockfd_) < 0)
    {
        std::cout<< "sockets::close" << std::endl;
    }
}


int Socket::create()
{
    sockfd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return sockfd_;
}

void Socket::bind(const char* ip ,int port)
{
    SocketUtil::bind(sockfd_, ip, port);
}

void Socket::listen()
{
    SocketUtil::listen(sockfd_);
}

int Socket::accept()
{
    struct sockaddr_in addr{0};
	socklen_t addrlen = sizeof addr;

	int connect_fd = ::accept(sockfd_, (struct sockaddr*)&addr, &addrlen);
	return connect_fd;

}