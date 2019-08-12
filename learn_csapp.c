#include <stdio.h>
#include <stdlib.h>


int main()
{
    int i = 0x80000001;
    //shift left 
    //shift a large num
    int sleft_i = i << 2;
    int slarge = i >> 33;
    printf("%d %d",&i,&sleft_i,&slarge);
    return 0;
}

