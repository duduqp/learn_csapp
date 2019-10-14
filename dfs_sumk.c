#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
int target;
struct  arr_elem{
    int index;
    int value;
}arr[MAX];
static int cmp(const void * a,const void * b)
{
    struct arr_elem * aa = (struct arr_elem *) a;
    struct arr_elem * bb = (struct arr_elem *) b;
    return (aa->value)-(bb->value);
}

int solution[MAX] = {0};
void dfs_sumk(struct arr_elem * a,int cur,int size,int k)
{
    //find int array a ,each combination of elements that sum up to k
    if(cur>size-1||a[cur].value>k)
    {
        if(k==0)
        {
            //if reach target
            for(int i=0;i<=cur;++i)
            {
                if(solution[i]==1){
                    printf(" arr[%d] ",i);
                }
                
            }
            puts("\n");
            fflush(NULL);
        }
        //both reach tail but fail and found a combination need to clear 
        return ;
    }
    if(a[cur].value<=k){
        solution[a[cur].index] = 1;//set
        dfs_sumk(a,cur+1,size,k-a[cur].value);
        solution[a[cur].index] = 0;
        dfs_sumk(a,cur+1,size,k);
    }
}
int main()
{
    int n;
    scanf("%d %d",&n,&target);

    for(int i = 0;i<n;++i)
    {
        scanf("%d",&arr[i].value);
        arr[i].index = i;
    }

    //sort
    qsort(arr,n,sizeof(arr[0]),cmp);

    for(int i = 0;i<n;++i)
    {
        printf("no.%d value:%d\n",arr[i].index,arr[i].value);
    }
    
    dfs_sumk(arr,0,n,target);
    return 0;
}

