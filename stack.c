#include<stdio.h>
typedef struct stack
{
    int an[110];
    int top;
}sk;
sk sta;
int main()
{
    sta.top=0;
    int op,n;
    scanf("%d",&op);
    while(~op)
    {
        
        if(op==1)
        {
            if(sta.top<100)
            {
                scanf("%d",&n);
                sta.an[sta.top++]=n;
            }
            else
            {
                printf("error ");
            }
        }   
        else if(op==0)
        {
            if(sta.top==0)
                printf("error ");
            else
            {
                printf("%d ",sta.an[--sta.top]);
            }
        }
        scanf("%d",&op);
    }
    printf("\n");
    return 0;
}