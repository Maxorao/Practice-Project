#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int fro;
    int rear;
    int que[500000][2];
}dot;
dot queue;
int numx[100000][100];
void init()
{
    queue.fro=250000;
    queue.rear=250001;
}
void front(int a)
{
    int i=0;
    while(numx[a][i]!=0)
        i++;
    numx[a][i]=queue.fro;
    queue.que[queue.fro][0]=a;
    queue.que[queue.fro--][1]=1;
    return;
}
void end(int a)
{
    int i=0;
    while(numx[a][i]!=0)
        i++;
    numx[a][i]=queue.rear;
    queue.que[queue.rear][0]=a;
    queue.que[queue.rear++][1]=1;
    return;
}
void delete(int x,int k)
{
    int temp=numx[x][k-1];
    queue.que[temp][1]=0;
    return;
}
int main()
{
    int n,op,k,x;
    scanf("%d",&n);

    init();

    while(n--)
    {
        scanf("%d",&op);
        switch (op)
        {
        case 1:
        {
            int temp;
            scanf("%d",&temp);
            front(temp);
            break;
        }

        case 2:
        {
            int temp;
            scanf("%d",&temp);
            end(temp);
            break;
        }
        
        case 3:
        {
            scanf("%d%d",&x,&k);
            delete(x,k);
            break;
        }

        default:
            break;
        }
    }

    int i;
    for(i=queue.fro+1;i<queue.rear;i++)
    {
        if(queue.que[i][1]==1)
            printf("%d\n",queue.que[i][0]);
    }

    return 0;
}