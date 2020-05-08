#include<stdio.h>
#include<stdlib.h>
typedef struct charInt
{
    int freq;
    char letter;
    struct charInt* next;
    struct charInt* lchild;
    struct charInt* rchild;
}Letterlist;
int HuffmanTable[200]={0};
Letterlist* TreeHead;
Letterlist* ListHead;
char Text[10000]={'\0'};
void CreateHuffmanTree();
void CreateHuffmanTable();
void CreateFrequenceTree();
void CreateList(Letterlist* p);
void StatisticFrequency(char c);
void EncryptText();
void OutPutInX();
void InsertList(Letterlist* p);
void init();
void mycmp(const void* a,const void* b);
int main()
{
    init();

    CreateFrequenceTree();

    CreateList(TreeHead);

    CreateHuffmanTree();

    CreateHuffmanTable();

    EncryptText();

    OutPutInX();

    return 0;
}
void init()
{
    TreeHead=NULL;
    ListHead=NULL;
}
void CreateFrequenceTree()
{
    FILE* in;
    if((in=fopen("input.txt","r"))==NULL)
    {
        perror("Can't open the file");
        exit(-1);
    }
    else
    {
        char c;
        while(fscanf(in,"%c",&c))
        {
            if(c=='\n')
            {
                continue;
            }
            if(c=='\0')
            {
                StatisticFrequency(c);
                return;
            }
            StatisticFrequency(c);
        }
    }
}
void StatisticFrequency(char c)
{
    if(TreeHead!=NULL)
    {
        Letterlist* p;
        p=TreeHead;
        while(p!=NULL)
        {
            if(c>p->letter)
            {
                p=p->rchild;
            }
            else if(c<p->letter)
            {
                p=p->lchild;
            }
            else if(c==p->letter)
            {
                p->freq++;
            }
        }
        p=(Letterlist*)malloc(sizeof(Letterlist));
        p->letter=c;
        p->freq=1;
        p->lchild=NULL;
        p->rchild=NULL;
        return;
    }
    else if(TreeHead==NULL)
    {
        TreeHead->letter=c;
        TreeHead->freq=1;
        TreeHead->lchild=NULL;
        TreeHead->rchild=NULL;
    }
    return;
}
void CreateHuffmanTable()
{

}
void CreateHuffmanTree()
{
    while(ListHead->next!=NULL)
    {
        Letterlist* p=(Letterlist*)malloc(sizeof(Letterlist));
        p->freq=ListHead->freq+ListHead->next->freq;
        p->lchild=ListHead;
        p->rchild=ListHead->next;
        ListHead=ListHead->next->next;
        if(ListHead==NULL)
        {

        }
    }
}
void CreateList(Letterlist* p)
{
    if(p==NULL)
    {
        return;
    }
    if(p->lchild==NULL&&p->rchild==NULL)
    {
        insert(p);
        return;
    }
    insert(p);
    CreateList(p->rchild);
    CreateList(p->lchild);
    return;
}
void InsertList(Letterlist* p)
{
    if(ListHead==NULL)
    {
        ListHead=(Letterlist*)malloc(sizeof(Letterlist));
        ListHead=p;
        ListHead->next=NULL;
    }
    Letterlist* Forward=ListHead;
    Letterlist* BackWard=NULL;
    while(Forward!=NULL)
    {
        if(p->freq<=Forward->freq)
        {
            Letterlist* temp=(Letterlist*)malloc(sizeof(Letterlist));
            temp->next=Forward;
            temp=p;
            if(BackWard!=NULL)
            {
                BackWard->next=temp;
            }
            return;
        }
        BackWard=Forward;
        Forward=Forward->next;
    }
    Forward=(Letterlist*)malloc(sizeof(Letterlist));
    Forward->next=NULL;
    Forward=p;
    BackWard->next=Forward;
    return;
}
void EncryptText()
{

}