#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* link;
}dot;
dot* head,*rear;
void init()
{
    head=(dot*)malloc(sizeof(dot));
    rear=head;
    head->link=NULL;
    rear->link=NULL;
}
void front(int a)
{
    dot* p=(dot*)malloc(sizeof(dot));

    p->data=a;

    if(head->link==NULL)
    {
        head->link=p;
        rear=p;
        rear->link=NULL;
        return;
    }

    p->link=head->link;
    head->link=p;
    return;
}
void end(int a)
{
    dot* p=(dot*)malloc(sizeof(dot));

    p->data=a;
    rear->link=p;
    rear=rear->link;
    rear->link=NULL;
}
void delete(int x,int k)
{
    int i=0;
    dot* p=head->link;
    dot* q=head;
    for(i=0;i<k;i++)
    {
        while(p->data!=x)
        {
            p=p->link;
            q=q->link;
        }
        if(i==k-1)
            break;
        p=p->link;
        q=q->link;
    }
    q->link=p->link;
    free(p);
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

    dot* p;
    p=head->link;
    while(p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->link;
    }

    return 0;
}