#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
typedef struct ele
{
    char name[30];
    char num[30];
}book[],p;
int compare(const void*a,const void*b)
{
    struct ele*c=(struct ele*)a;
    struct ele*d=(struct ele*)b;
    if(strcmp((*c).name,(*d).name)!=0)
    {
        return strcmp((*c).name,(*d).name);
    }
    return 0;
}
void attach(char a[],int n)
{
    if(n>0)
    {
        int i;
        i=strlen(a);
        a[i]='_';
        a[i+1]='0'+n;
        a[i+2]='\0';
    }
    else
    {
        return;
    }
}
void exchange(char a[],char b[])
{
    char temp[10000];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
}
void cutoff(struct ele* a,int po,int to)
{
    int i;
    for(i=po;i<to-1;i++)
    {
        exchange(a[i].name,a[i+1].name);
        exchange(a[i].num,a[i+1].num);
    }
}
int main()
{
    int n,i;
    scanf("%d",&n);
    struct ele* book=(struct ele*)malloc(n*sizeof(p));
    for(i=0;i<n;i++)
    {
        scanf("%s",book[i].name);
        scanf("%s",book[i].num);
    }
    qsort(book,n,sizeof(book[0]),compare);
    for(i=0;i<n-1;i++)
    {
        int l=0;
        while(strcmp(book[i].name,book[i+1].name)==0&&i<n-1)
        {
            int f,e;
            f=atoi(book[i].num);
            e=atoi(book[i+1].num);
            if(e==f)
            {
                cutoff(book,i+1,n);
                n--;
                continue;
            }
            attach(book[i].name,l);
            l++;i++;
        }
        attach(book[i].name,l);
    }
    for(i=0;i<n;i++)
            printf("%s %s\n",book[i].name,book[i].num);
    return 0;
}