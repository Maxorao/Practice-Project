#include<stdio.h>
#include<stdlib.h>
#define Maxsize 1000
typedef struct node
{
    int id;
    struct node* link;
}Node;
Node* h;
void esNode(int n)
{
    h->id=1;
    Node* p,*q;
    p=(Node*)malloc(sizeof(Node));
    q=(Node*)malloc(sizeof(Node));
    p=h;
    int i;
    for(i=2;i<=n;i++)
    {
        q=(Node*)malloc(sizeof(Node));
        q->id=i;
        p->link=q;
        p=p->link;
    }
    p->link=h;
}
int main()
{
    h=(Node*)malloc(sizeof(Node));
    Node* p,*q;
    p=(Node*)malloc(sizeof(Node));
    p=h;
    int n,i,k,l;
    scanf("%d",&n);
    scanf("%d",&k);
    scanf("%d",&l);
    if(n>Maxsize)
    {
        printf("The data is too huge!\n");
        return 0;
    }
    else
        esNode(n);
    for(i=0;i<l-1;i++,p=p->link);
    for(i=0;i<n-1;i++)
    {
        int temp=i;
        for(i=0;i<k-2;i++)
            p=p->link;
        q=p->link;
        p->link=(p->link)->link;
        p=p->link;
        i=temp;
    }
    printf("%d\n",p->id);
    return 0;
}