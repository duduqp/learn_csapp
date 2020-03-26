#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc ,char ** argv)
{
    //1.create socket
    //can use non-blocking or ...
    int listenfd=socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK,0);
    if(listenfd<0) 
    



    return 0;
}


