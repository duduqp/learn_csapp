#include <stdio.h>
#include "../header/wrap.h"
#include <stdlib.h>
#include <string.h>
FILE * Fopen(const char * path,const char * mode)
{

        FILE * stream=NULL;
    if(strcmp(mode,"r")==0)
    {
        stream=NULL;
        if((stream=fopen(path,"r"))==NULL)
        {
            perror("fopen read error");
            exit(-1);
        }
        return stream;
    }
    if(strcmp(mode,"w")==0)                
    {                                      
        stream=NULL;                
        if((stream=fopen(path,"w"))==NULL) 
        {                                  
            perror("fopen write error");         
            exit(-1);                      
        }                                  
        return stream;                     
    }
 if(strcmp(mode,"a")==0)                
 {                                      
     stream=NULL;                
     if((stream=fopen(path,"a"))==NULL) 
     {                                  
         perror("fopen append error");         
         exit(-1);                      
     }                                  
 }                            

 if(strcmp(mode,"w+")==0)                
 {                                      
     stream=NULL;                
     if((stream=fopen(path,"w+"))==NULL) 
     {                                  
         perror("fopen read write error");         
         exit(-1);                      
     }                                  
 }
 return stream;
}
