#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100
int edges[MAX]={0};
static int cmp(const void * pa,const void * pb)
{ 
   int * a = (int *) pa;
   int * b = (int *) pb;
    return (*a)-(*b);
}
int main()
{
    int n;
    //read edge number
    scanf("%d",&n);

    for(int i = 0;i<n;++i)
    {
        //read loop
        scanf("%d",&edges[i]);
    }

    qsort(edges,n,sizeof(edges[0]),cmp);
    
    //after qsort
    for(int i = 0;i<n;++i)
    {
        printf("%d ",edges[i]);
    }


    int i = n-1;
    int j = i-1;
    int k = j-1;
    for(;k>0;)
    {
        if(edges[j]+edges[k]>edges[i])
        {
            printf("max c:%d",edges[j]+edges[k]+edges[i]);
            return 0;
        }else{
            j--;k--;i--;
        }
    }
    
    return 0;
}

