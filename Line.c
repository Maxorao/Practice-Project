#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int x1,y1;
    int x2,y2;
    struct Node* link;
}Line;
Line an[100];
int cmp(const void* a,const void *b)
{
    Line* c =(Line*)a;
    Line *d = (Line*)b;
    if(c->x1!=d->x1)
        return (c->x1-d->x1);
    else
        return (c->y1-d->y1);
}
int Max(int a,int b)
{
    if(a>b)
        return a;
    else
    {
        return b;
    }
}
int main()
{
    int n,i,j,cou=0,max=0,flag;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&an[i].x1,&an[i].y1,&an[i].x2,&an[i].y2);
    }
    qsort(an,n,sizeof(an[0]),cmp);
    for(i=0;i<n;i++)
        an[i].link=NULL;
    for(i=0;i<n-1;i++)
        for(j=0;j<n;j++)
        {
            if(j==i&&i!=0)
                continue;
            else
            {
                if(an[j].x1==an[i].x2&&an[j].y1==an[i].y2)
                    an[i].link=&an[j];
            }
        }
    for(i=0;i<n-1;i++)
    {
        cou=0;
        Line* p=&an[i];
        while(p->link!=0)
        {
            cou++;
            p=p->link;
        } 
        max=Max(max,cou);
        if(max==cou&&max!=0)
            flag=i;
    }
    printf("%d %d %d\n",max+1,an[flag].x1,an[flag].y1);
    return 0;
}