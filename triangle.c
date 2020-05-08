#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int x;
    int y;
    struct node* xup;
    struct node* yup;
}dot;
dot pool[110];
int cmp(const void* a,const void *b)
{
    dot* c = (dot*)a;
    dot* d = (dot*)b;
    if(c->x!=d->x)
        return c->x-d->x;
    else
        return c->y-d->y;
}
dot* head;
void init()
{
    head=&pool[0];
}
void ForXrange(int n)
{
    dot* p;
    p=(dot*)malloc(sizeof(dot));
    head=p;
    int i;
    for(i=0;i<n-1;i++)
    {
        if(pool[i].x==pool[i+1].x)
        {
            p->yup=&pool[i+1];
            p=p->yup;
        }
    }
}
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d%d",&pool[i].x,&pool[i].y);
    qsort(pool,n,sizeof(pool[0]),cmp);
    init();
    ForXrange(n);
    ForYrange();
    return 0;
}