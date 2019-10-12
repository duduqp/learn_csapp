#include <stdio.h>
#include <stdlib.h>

void my_func_a(void)
{
    fprintf(stdout,"my_first hook func\n");
}
void my_func_b(void)
{
    fprintf(stdout,"my_second hook func\n");
}
int main()
{
    if(atexit(my_func_b)!=0||atexit(my_func_a)!=0)
    {
        fprintf(stderr,"error with atexit");
        exit(EXIT_FAILURE);
    }

    printf("next will call hooks reversely\n");
    exit(EXIT_SUCCESS);
}

