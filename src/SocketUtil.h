#ifndef ALEX_NET_SOCKETUTIL_H
#define ALEX_NET_SOCKETUTIL_H

namespace alex
{
class SocketUtil
{
public:

static void bind(int sockfd, const char* ip, int port);

static void listen(int sockfd);

static void connect(int sockfd, const char* ip, int port);

static void close(int sockfd);

static void setNoBlockSocket(int sockfd);

static void setCloseOnExecSocket(int sockfd);

    // TCP_NODELAY
static void setTcpNoDelay(int sockfd);

    // SO_REUSEADDR
static void setReuseAddr(int sockfd);

    // SO_REUSEPORT
static void setRequsePort(int sockfd);

    // SO_KEEPALIVE
static void setKeepAlive(int sockfd);


};

}
#endif