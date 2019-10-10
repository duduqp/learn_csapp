#include <stdio.h>
#include <stdlib.h>
#include <map>
constexpr int MONTHS = 12;
const int months[MONTHS+1] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };//dummy months[0] for convenience
static int isleap(int year)
{
    //return 0 if year is leap ,otherwise -1
    return ((year%4 == 0 && (year%100!=0))||(year% 400 ==0))?0:-1;
}
int main()
{
    //y: yyyy e.g.1 2019 e.g.2 9012
    //m: mm e.g.1 11 e.g.3 20
    //d: dd e.g.1 20 e.g.2 60

    int m,d,y;
    printf("input format: yyyy mm dd\n");
    scanf("%d %d %d",&y,&m,&d);

    //check year month date validity
    if(m<13&&m>0&&d>0&&d<=months[m]&&y<=2012&&y>=1812)
    {

        int year_increment = 0;
        int month_increment = 0;
        int leap_flag = isleap(y);
        if(leap_flag==-1&&m==2&&d==29)
        {
            printf("leap year error\n");
            exit(0);
        }else{
          //compute next date
          //not a leap ,div 28 ,otherwise div months[month]
          if(m == 2 && (leap_flag == -1))
          {
              month_increment = (d+1)/29;
              d = ((d+1) % 28 == 0)? (d+1): ((d+1)%28);
          }else{
              month_increment = (d+1)/(months[m]+1);
              d= ((d+1) % months[m]==0) ? (d+1) : ((d+1)%months[m]);
          }
          year_increment = (m+month_increment) / 12;
          m = (m+month_increment) % 12; 
          y += year_increment;
        }
    }
    else{
        printf("input should satisfies :year_range [1812,2012] month_range [1,12] date_range [1,31]\n");
        exit(0);
    }

    printf("next date : %d %d %d\n",y,m,d);
    exit(0);


/*  
 *  test for isleap()
    printf("is leap? %d\n",isleap(2008));
    printf("is leap? %d\n",isleap(1900));
    printf("is leap? %d\n",isleap(2004));
    exit(0);
*/
}

