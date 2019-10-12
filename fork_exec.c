#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    int ret;
    ret=execl("./stat","stat","file_b","hello_b",NULL);
    if(ret == -1)
    {
        perror("execl");
    }
    printf("this line only print if execl error\n");
    return 0;
}

