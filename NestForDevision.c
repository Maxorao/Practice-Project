#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int SerialNumber;
    int degree;
    struct node* MaxChild;
    struct node* MiddleChild;
    struct node* MinChild;
}Nest;
Nest* HashTable[200];
Nest* head;
int SerialHash[110];
int MaxHeight[110]={0};
void init();
void CreateTable();
void SearchNest(Nest* p,int height);
void CreateNest();
void PrintNode();
void gotoZero();
void SearchNestTwice(Nest* p,int height);
int MaxInThree(int,int,int);
int main()
{
    init();
    CreateTable();
    SearchNest(head,1);
    if(MaxHeight[109]==0)
        SearchNestTwice(head,1);
    PrintNode();
    return 0;
}
void init()
{
    head=NULL;
    int i;
    for(i=0;i<200;i++)
    {
        HashTable[i]=NULL;
    }
}
void CreateNest()
{
    int root,Max,Min,Mid;
    Nest* p;
    scanf("%d",&root);
    if(HashTable[root]==NULL)
    {
        p=(Nest*)malloc(sizeof(Nest));
        HashTable[root]=p;
        p->SerialNumber=root;
    }else
    {
        p=HashTable[root];
    }
    scanf("%d%d%d",&Min,&Mid,&Max);
    if(Min!=0)
    {
        p->MinChild=(Nest*)malloc(sizeof(Nest));
        p->MinChild->SerialNumber=Min;
        p->MinChild->MaxChild=NULL;
        p->MinChild->MinChild=NULL;
        p->MinChild->MiddleChild=NULL;
        HashTable[Min]=p->MinChild;
        p->degree=1;
    }
    else
    {
        p->MinChild=NULL;
        p->degree=0;
    }
    if(Max!=0)
    {
        p->MaxChild=(Nest*)malloc(sizeof(Nest));
        p->MaxChild->SerialNumber=Max;
        p->MaxChild->MaxChild=NULL;
        p->MaxChild->MinChild=NULL;
        p->MaxChild->MiddleChild=NULL;
        HashTable[Max]=p->MaxChild;
        p->degree++;
    }
    else
    {
        p->MaxChild=NULL;
    }
    if(Mid!=0)
    {
        p->MiddleChild=(Nest*)malloc(sizeof(Nest));
        p->MiddleChild->SerialNumber=Mid;
        p->MiddleChild->MaxChild=NULL;
        p->MiddleChild->MinChild=NULL;
        p->MiddleChild->MiddleChild=NULL;
        HashTable[Mid]=p->MiddleChild;
        p->degree++;
    }
    else
    {
        p->MiddleChild=NULL;
    }
}
void CreateTable()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        CreateNest();
    }
    head=HashTable[1];
}
void SearchNest(Nest* p,int height)
{
    static int cou=0;
    if(p==NULL)
        return;
    if(p->degree==3)
    {
        if(MaxHeight[109]<height)
        {
            MaxHeight[109]=height;
            gotoZero();
            MaxHeight[p->SerialNumber]=1;
        }
        else if(MaxHeight[109]==height)
        {
            MaxHeight[p->SerialNumber]=1;
        }
    }
    cou++;
    SerialHash[cou]=p->SerialNumber;
    SearchNest(p->MinChild,height+1);
    SearchNest(p->MiddleChild,height+1);
    SearchNest(p->MaxChild,height+1);
}
void SearchNestTwice(Nest* p,int height)
{
    static int cou1=0;
    if(p==NULL)
        return;
    if(p->degree==2)
    {
        if(MaxHeight[109]<height)
        {
            MaxHeight[109]=height;
            gotoZero();
            MaxHeight[p->SerialNumber]=1;
        }
        else if(MaxHeight[109]==height)
        {
            MaxHeight[p->SerialNumber]=1;
        }
    }
    cou1++;
    SerialHash[cou1]=p->SerialNumber;
    SearchNestTwice(p->MinChild,height+1);
    SearchNestTwice(p->MiddleChild,height+1);
    SearchNestTwice(p->MaxChild,height+1);
}
void gotoZero()
{
    int i;
    for(i=0;i<105;i++)
    {
        MaxHeight[i]=0;
    }
}
void PrintNode()
{
    int i;
    for(i=0;i<101;i++)
    {
        if(MaxHeight[SerialHash[i]]==1)
        {
            printf("%d %d\n",SerialHash[i],i);
        }
    }
}