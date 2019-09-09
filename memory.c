#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    //get current heap top addr
    //param:intptr_t increment
    //return:void *
    void * heap_addr = sbrk(0);
    printf("current heap location: %p \n",heap_addr);

    //lib-func malloc 
    //mult-thread usable
    //param:size_t
    //return: void *
    //error NULL and errno     note :lways check
    //free(void *ptr)
    //note : will not decrease the prog_brk ,only attach the recycled page to a sys_level_list
    typedef struct{
        int num; 
    } mystruct ;

    mystruct st;
    mystruct * p_st;

    p_st= (mystruct *)calloc(1000,sizeof(st));

    if(p_st == NULL)
    {
        printf("error calloc");
        exit(0);
    }

    printf("%p",p_st);

    //mystruct * p_mst = (mystruct *) p_struct; 
    //access p_struct 
    //fprintf(stdout,"use ptr_alloc_in_heap : num %d  string %s \n",*p_mst.num,*p_mst.str);
 
    
    //illustration for realloc behavior,low-efficient
    void * pp = malloc(100);
    void * new_pp = realloc(pp,10e5);
    printf("before realloc %p after realloc %p",pp,new_pp);
    
    free(pp);
    free(new_pp);
    free(p_st); 
    
    
    
    
    
    
    
    
    
    exit(0);
}

