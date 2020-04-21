#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    int coe;
    int exp;
    struct node* link;
}poly;
poly *ha,*hb,*hc;
void eslinklist(poly** h)
{
    int n;
    poly *p,*q;
    p=(poly*)malloc(sizeof(poly));
    q=(poly*)malloc(sizeof(poly));
    *h=p;
    char temp[30],c;
    scanf("%s",temp);
    n=atoi(temp);
    q->coe=n;
    scanf("%s",temp);
    n=atoi(temp);
    q->exp=n;
    q->link=NULL;
    p->link=q;
    p=q;
    *h=q;
    while((c=getchar())!='\n')
    {
        q=(poly*)malloc(sizeof(poly));
        q->link=NULL;
        scanf("%s",temp);
        n=atoi(temp);
        q->coe=n;
        scanf("%s",temp);
        n=atoi(temp);
        q->exp=n;
        p->link=q;
        p=p->link;
    }
}
poly* multi(poly* ha,poly* hb)
{
    poly *p,*q,*l,*hc,*t;
    p=ha;
    q=hb;
    hc=(poly*)malloc(sizeof(poly));
    hc->link=NULL;
    hc->exp=0;
    t=hc;
    l=(poly*)malloc(sizeof(poly));
    l->link=NULL;
    while(p!=NULL)
    {
        while(q!=NULL)
        {
            l->coe=(p->coe)*(q->coe);
            l->exp=p->exp+q->exp;
            if(hc->link==NULL&&hc->exp==0)
            {
                hc=l;
                hc->link=NULL;
            }
            else
            {
                while(t->link!=NULL&&l->exp<t->link->exp)
                    t=t->link;
                if(t->link==NULL)
                {
                    t->link=l;
                    t=t->link;
                    t->link=NULL;
                }
                else if(l->exp>t->link->exp)
                {
                    l->link=t->link;
                    t->link=l;
                }
                else if(l->exp==t->link->exp)
                {
                    t->link->coe+=l->coe;
                }
            }
            q=q->link;
            t=hc;
            l=(poly*)malloc(sizeof(poly));
            l->link=NULL;
        }
        p=p->link;
        t=hc;
        q=hb;
    }
    return hc;
}
int main()
{
    eslinklist(&ha);
    eslinklist(&hb);
    hc=multi(ha,hb);
    poly* p;
    p=hc;
    while(p->link!=NULL)
    {
        printf("%d %d ",p->coe,p->exp);
        p=p->link;
    }
    printf("%d %d\n",p->coe,p->exp);
    return 0;
}