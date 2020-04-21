#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char code;
    struct node* link;
}Node;
int dex[200];
Node* eskey(char key[])
{
    Node* h=(Node*)malloc(sizeof(Node));
    Node* p=(Node*)malloc(sizeof(Node));
    Node* q=(Node*)malloc(sizeof(Node));
    p=h;
    p->code=key[0];
    int i,n=strlen(key);
    for(i=1;i<n;i++)
    {
        q->code=key[i];
        p->link=q;
        p=p->link;
        q=(Node*)malloc(sizeof(Node));
    }
    free(q);
    p->link=h;
    return h;
}
int main()
{
    FILE *in;
    if((in=fopen("in.txt","r"))==NULL)
    {
        perror("Can't open the file:");
        exit(0);
    }
    else
    {
        int i,n,temp,code[200]={0};
        char key[100],c;
        while((c=getchar())!='\n')
        {
            if(dex[c]==0)
            {
                key[i++]=c;
                dex[c]=1;
            }
        }
        n=strlen(key);
        for(i=32;i<=126;i++)
        {
            if(dex[i]==0)
            {
                key[n++]=i;
            }
        }
        key[n]='\0';
        Node* q = (Node*)malloc(sizeof(Node));
        Node* p = (Node*)malloc(sizeof(Node));
        p=eskey(key);
        for(q=p;q->link!=p;q=q->link);
        n=p->code;
        while(p->link!=q)
        {
            temp=p->code;
            q->link=p->link;
            p=p->link;
            for(i=0;i<temp-1;i++)
            {
                p=p->link;
                q=q->link;
            }
            code[temp]=p->code;
        }
        temp=p->code;
        code[temp]=q->code;
        code[q->code]=n;
        FILE *out;
        if((out=fopen("in_crpyt.txt","w"))==NULL)
        {
            perror("Can't open the file:");
            exit(0);
        }
        else
        {
            while(fscanf(in,"%c",&c)!=-1)
            {
                if(c>=32&&c<=126)
                    fprintf(out,"%c",code[c]);
                else
                {
                    fprintf(out,"%c",c);
                }
            }
        }
    }
    return 0;
}