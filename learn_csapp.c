#include <stdio.h>
#include <stdlib.h>


int main()
{
    int i = 0x80000001;
    //shift left 
    //shift a large num
    int s_left_i = i << 2;
    int s_large = i >> 3;
    printf("%80x\n%80x\n%80x",i,s_left_i,s_large);
    return 0;
}

