#include <stdio.h>
#include <stdlib.h>


int main()
{
    //int i = 0x80000001;
    //shift left 
    //shift a large num
    //int s_left_i = i << 2;
    //int s_large = i >> 3;
    //printf("%80x\n%80x\n%80x",i,s_left_i,s_large);

    //signed num will be cast to unsigned 
    //note that size_t is a type of unsigned int ssize_t is a signed one
    
    //size_t ui = 0;
    //int si = 0;
    /*
     if((ui-1)<i)
    {
        fprintf(stdout,"unsigned ui smaller than 0");
    }else
    {
        fprintf(stdout,"unsigned ui larger than 0");
    }*/

    //bit-pattern will remains ,but the way how to explain it changed
    //bit-pattern all 1 will be considered as -1 for integer
    
    //unsigned ui = 4294967295u;
    //int si = ui;
    //fprintf(stdout,"%d",si);


    //logical(0 fill always) or arithmatic shift(sign fill) 
    //arith-expansion or logic-expansion depends on the short operand type
     short ss = -250;
     unsigned short us = 1;

     int si = ss;
     int i = us;


     fprintf(stdout,"signed short expansion : %d\n",si);
     fprintf(stdout,"unsigned short expansion : %d\n",i);
    exit(0);
}

