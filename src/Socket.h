#ifndef ALEX_NET_SOCKET_H
#define ALEX_NET_SOCKET_H


namespace alex
{

class Socket
{
public:
    // 修饰只有一个参数的类构造函数，以表明该构造函数是显式的，而非隐式的
    Socket(int sockfd = -1):sockfd_(sockfd){}

    ~Socket();

    int create();

    void bind(const char* ip ,int port);

    void listen();

    int accept();

    int connect();

    void close();

    int fd() {return sockfd_;}

private:
    int sockfd_;

};

}

#endif 