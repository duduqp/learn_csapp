#pragma once
#include "ddserver/util.h"
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int recv_varientrecord(int sockfd,void * dest,size_t target_len)
{
    uint32_t recordlen;
    ssize_t retn=readn(sockfd,(void *)&recordlen,sizeof(recordlen));

    if(retn<target_len)
    {
        //even header len field is too large for passin len
        //discard
        while(retn>0)
        {
            int ret=readn(sockfd,dest,target_len);
            if(ret<0)
            {
                return ret;//ret==-1=>error ret==0 => eof
            }
            retn-=ret;
            if(retn<target_len)
            {
                target_len=retn;//读完零头
            }
        }
        //set errno here
        
        return -1;
    }

    //enough
    int ret=readn(sockfd,dest,recordlen);
    return ret;
}
