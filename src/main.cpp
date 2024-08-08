#include <stdio.h>
#include "EventLoop.h"
#include "TcpServer.h"
#include <unistd.h>
#include <string>
#include <iostream>

using namespace alex;
int main()
{
    EventLoop loop;
    TcpServer server(&loop);
    printf("start server ip 172.29.14.100");
    server.start("0.0.0.0", 55555);

	std::string str;
	while (std::getline(std::cin, str)) {
		if (str == "exit") {
			break;
		}
        ::sleep(0.1);
	}

    return 0;
}