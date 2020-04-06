#include <iostream>
#include "util.h"
#include "Packet.h"
#include <sys/socket.h>

int Send(const Packet & p)
{
    
}

int main()
{
    RULE & rule=RULE::GetRULE();
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0)
    {
        Default_Error_Handler();
    }

    Packet p("hello dudu");
    int ret=Send(p);
    std::cout << "Hello world" << std::endl;
    return 0;
}

