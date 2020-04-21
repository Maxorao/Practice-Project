#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct node
{
    char s[30];
    int cou;
    struct node* link;
}table;
table* h;
table* p;
void search(char *c)
{
    p=h;
    if(p->cou==-1)
    {
        strcpy(p->s,c);
        p->cou=1;
        p->link=NULL;
        return;
    }
    while(p!=NULL)
    {
        int temp=strcmp(c,p->s);
        if(temp>0)
        {
            if(p->link!=NULL)
            {
                int temp1=strcmp(c,p->link->s);
                if(temp1>0)
                {
                    p=p->link;
                    continue;
                }
                else if(temp1==0)
                {
                    p->link->cou++;
                    return;
                }
                else
                {
                    table* q=(table*)malloc(sizeof(table));
                    strcpy(q->s,c);
                    q->cou=1;
                    q->link=p->link;
                    p->link=q;
                    return;
                }
            }
            else
            {
                p->link=(table*)malloc(sizeof(table));
                p=p->link;
                strcpy(p->s,c);
                p->cou=1;
                p->link=NULL;
                p=p->link;
                return;
            }
            continue;
        }
        else if(temp==0)
        {
            p->cou++;
            return;
        }
        else if(temp<0)
        {
            table* q=(table*)malloc(sizeof(table));
            strcpy(q->s,c);
            q->cou=1;
            q->link=p;
            h=q;
            return;
        }
    }
}
int main()
{
    char *test;
    FILE *in;
    h=(table*)malloc(sizeof(table));
    h->cou=-1;
    test=(char*)malloc(30*sizeof(char));
    if((in=fopen("article.txt","r"))==NULL)
    {
        perror("Can't open the file:");
        exit(0);
    }
    else
    {
        char c;
        int i;
        while(~fscanf(in,"%c",&c))
        {
            if(!isalpha(c))
                continue;
            else
            {
                i=0;
                memset(test,0,sizeof(char));
                do{
                    c=tolower(c);
                    *(test+(i++))=c;
                    fscanf(in,"%c",&c);
                }while(isalpha(c));
                *(test+i)='\0';
                search(test);
            }
        }
        while(h!=NULL)
        {
            printf("%s %d\n",h->s,h->cou);
            h=h->link;
        }
    }
    return 0;
}