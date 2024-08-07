#include <stdio.h>
#include "EventLoop.h"
#include "TcpServer.h"
#

using namespace alex;
int main()
{
    EventLoop loop;
    TcpServer server(&loop);
    printf("start server ip 172.29.14.100");
    server.start("0.0.0.0", 55555);

    return 0;
}