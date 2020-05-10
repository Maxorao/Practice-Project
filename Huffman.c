#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct charInt
{
    int freq;
    char letter;
    struct charInt* next;
    struct charInt* lchild;
    struct charInt* rchild;
}Letterlist;
char HuffmanTable[128][20];
char Code[9]={'\0'};
Letterlist* TreeHead;
Letterlist* ListHead;
char Text[10000]={'\0'};
void CreateHuffmanTree();
void CreateHuffmanTable(Letterlist* p,char Code[9],int top);
void CreateFrequenceTree();
void CreateList(Letterlist* p);
void StatisticFrequency(char c);
void EncryptText();
void InsertList(Letterlist* p,int state);
void GetCode(char c,char Code[]);
void init();
void mycmp(const void* a,const void* b);
int main()
{
    init();

    CreateFrequenceTree();

    CreateList(TreeHead);

    CreateHuffmanTree();

    CreateHuffmanTable(TreeHead,Code,0);

    EncryptText();

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
    int i=0;
    if((in=fopen("input.txt","r"))==NULL)
    {
        perror("Can't open the file");
        exit(-1);
    }
    else
    {
        char c;
        while(~fscanf(in,"%c",&c))
        {
            if(c=='\n')
            {
                continue;
            }
            Text[i++]=c;
            StatisticFrequency(c);
        }
        StatisticFrequency('\0');
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
                if(p->rchild==NULL)
                {
                    p->rchild=(Letterlist*)malloc(sizeof(Letterlist));
                    p=p->rchild;
                    break;
                }
                p=p->rchild;
                continue;
            }
            else if(c<p->letter)
            {
                if(p->lchild==NULL)
                {
                    p->lchild=(Letterlist*)malloc(sizeof(Letterlist));
                    p=p->lchild;
                    break;
                }
                p=p->lchild;
                continue;
            }
            else if(c==p->letter)
            {
                p->freq++;
                return;
            }
        }
        p->letter=c;
        p->freq=1;
        p->lchild=NULL;
        p->next=NULL;
        p->rchild=NULL;
        return;
    }
    else if(TreeHead==NULL)
    {
        TreeHead=(Letterlist*)malloc(sizeof(Letterlist));
        TreeHead->letter=c;
        TreeHead->freq=1;
        TreeHead->lchild=NULL;
        TreeHead->rchild=NULL;
    }
    return;
}
void CreateHuffmanTable(Letterlist* p,char Code[9],int top)
{
    if(p->lchild!=NULL)
    {
        Code[top]='0';
        CreateHuffmanTable(p->lchild,Code,top+1);
    }
    if(p->rchild!=NULL)
    {
        Code[top]='1';
        CreateHuffmanTable(p->rchild,Code,top+1);
        Code[top]=0;
    }
    if(p->rchild==NULL&&p->lchild==NULL)
    {
        GetCode(p->letter,Code);
        return;
    }
    return;
}
void GetCode(char c,char Code[])
{
    strcpy(HuffmanTable[c],Code);
    return;
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
        InsertList(p,0);
    }
    TreeHead=ListHead;
}
void CreateList(Letterlist* p)
{
    if(p==NULL)
    {
        return;
    }
    if(p->lchild==NULL&&p->rchild==NULL)
    {
        InsertList(p,1);
        return;
    }
    CreateList(p->rchild);
    CreateList(p->lchild);
    InsertList(p,1);
    return;
}
void InsertList(Letterlist* p,int state)
{
    if(state==1)
    {
        p->lchild=NULL;
        p->rchild=NULL;
    }
    if(ListHead==NULL)
    {
        ListHead=p;
        ListHead->next=NULL;
        return;
    }
    Letterlist* Forward=ListHead;
    Letterlist* BackWard=NULL;
    while(Forward!=NULL)
    {
        if(p->freq<Forward->freq)
        {
            p->next=Forward;
            if(BackWard!=NULL)
            {
                BackWard->next=p;
                return;
            }
            else
            {
                ListHead=p;
                return;
            }
        }
        if(p->freq==Forward->freq&&state==1)
        {
            if(p->letter<Forward->letter)
            {
                p->next=Forward;
                if(BackWard!=NULL)
                {
                    BackWard->next=p;
                    return;
                }
                else
                {
                    ListHead=p;
                    return;
                }
            }
        }
        BackWard=Forward;
        Forward=Forward->next;
    }
    Forward=p;
    Forward->next=NULL;
    BackWard->next=Forward;
    return;
}
void EncryptText()
{
    FILE* out;
    out=fopen("output.txt","w");
    int i=0,j=0,k=0;
    unsigned char c='\0';
    while(Text[i]!='\0')
    {
        for(;HuffmanTable[Text[i]][k]!='\0'&&j<8;k++,j++)
        {
            c=(c<<1)|(HuffmanTable[Text[i]][k]-'0');
        }
        if(HuffmanTable[Text[i]][k]=='\0')
        {
            i++;
            k=0;
        }
        if(j==8)
        {
            printf("%x",c);
            fprintf(out,"%c",c);
            j=0;
            c=0;
        }
        if(Text[i]=='\0')
        {
            for(;HuffmanTable['\0'][k]!='\0'&&j<8;k++,j++)
            {
                c=(c<<1)|(HuffmanTable['\0'][k]-'0');
            }
            if(HuffmanTable['\0'][k]=='\0')
            {
                for(;j<8;j++)
                {
                    c=c<<1;
                }
                printf("%x\n",c);
                fprintf(out,"%c",c);
                return;
            }
            if(j==8)
            {
                printf("%x",c);
                fprintf(out,"%c",c);
                for(j=0;HuffmanTable['\0'][k]!='\0'&&j<8;k++,j++)
                {
                    c=(c<<1)|(HuffmanTable['\0'][k]-'0');
                }
                for(;j<8;j++)
                {
                    c=c<<1;
                }
                printf("%x\n",c);
                fprintf(out,"%c",c);
                return;
            }
        }
    }
}