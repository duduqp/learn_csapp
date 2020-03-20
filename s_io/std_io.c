#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main()
{

    //char
    int val,ch;
    while((ch=getchar())!=EOF)
    {
        if(isdigit(ch))
        {
            putchar(ch);
            putchar('\n');
        }
    }
    printf("end while\n");
    int end=getchar();
    putchar(end);
    putchar('\n');
    
    return 0;
}

