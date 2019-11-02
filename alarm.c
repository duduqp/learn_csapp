#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

static loop_count = 0;
static void alrm_handler(int sig)
{

}
int main()
{
    alarm(10);
    signal(alrm_handler,)
    printf("Hello world\n");
    return 0;
}

