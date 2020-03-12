#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int number;//max number of queue fd
    int * fd;//fd array
    int front;
    int rear;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
}block_queue;

void block_queue_init(block_queue * blockQ,int number)
{
    blockQ->number=number;
    blockQ->fd=(int *)calloc(number,sizeof(int));
    blockQ->front=blockQ->rear=0;
    pthread_mutex_init(&blockQ->mutex,NULL);
    pthread_cond_init(&blockQ->cond,NULL);
}

//put a fd in queue
void block_queue_push(block_queue * blockQ,int fd)
{
    pthread_mutex_lock(&blockQ->mutex);
    blockQ->fd[blockQ->rear++]=fd;
    if(blockQ->rear==blockQ->number)
    {
        blockQ->rear=0;//round back
    }

    printf("push %d\n",fd);

    pthread_cond_signal(&blockQ->cond);
    pthread_mutex_unlock(&blockQ->mutex);
}


int block_queue_pop(block_queue * blockQ)
{
    int ret;
    pthread_mutex_lock(&blockQ->mutex);

    while(blockQ->front==blockQ->rear)
    {
        pthread_cond_wait(&blockQ->cond,&blockQ->mutex);
    }

    ret=blockQ->fd[blockQ->front++];
    if(blockQ->front==blockQ->number)
    {
        blockQ->front=0;
    }

    printf("pop %d",ret);
    pthread_mutex_unlock(&blockQ->mutex);
    return ret;
}



