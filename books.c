#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
    char name[120];
    char au[120];
    char pre[120];
    int age;
}ele;
int cmp(const void*a,const void*b)
{
    ele*c=(ele*)a;
    ele*d=(ele*)b;
    return strcmp((*c).name,(*d).name);
}
void insert(ele books[500],ele book,int i,int n)
{
    strcpy(books[n].name,books[n-1].name);
    strcpy(books[n].au,books[n-1].au);
    strcpy(books[n].pre,books[n-1].pre);
    books[n].age=books[n-1].age;
    int j;
    for(j=n-1;j>i;j--)
    {
        char s[1000];
        strcpy(s,books[j].name);
        strcpy(books[j].name,books[j-1].name);
        strcpy(books[j-1].name,s);
        strcpy(s,books[j].au);
        strcpy(books[j].au,books[j-1].au);
        strcpy(books[j-1].au,s);
        strcpy(s,books[j].pre);
        strcpy(books[j].pre,books[j-1].pre);
        strcpy(books[j-1].pre,s);
        int a=books[j].age;
        books[j].age=books[j-1].age;
        books[j-1].age=a;
    }
    strcpy(books[i].name,book.name);
    strcpy(books[i].au,book.au);
    strcpy(books[i].pre,book.pre);
    books[i].age=book.age;
}
int position(ele books[500],ele book,int n,int l,int r)
{
    if(l==r||r==l+1)
        return r;
    while(r>l)
    {
        int a=strcmp(book.name,(*(books+l)).name);
        int b=strcmp(book.name,(*(books+r)).name);
        if(a<=0)
            return 0;
        else
        {
            if(b>=0)
                return n;
            else
            {
                int c=strcmp(book.name,books[(l+r)/2].name);
                if(c>=0)
                    return position(books,book,n,(l+r)/2,r);
                else
                    return position(books,book,n,l,(l+r)/2);
            }
        }
        
    }
    return 0;
}
int search(char s[],char key[],int next[])
{
    int i,j;
    for(i=0;i<strlen(s);i++)
    {
        for(j=0;j<strlen(key);j++)
        {
            if(s[i]==key[j])
            {
                if(j==strlen(key)-1)
                    return 1;
                i++;
            }
            else
            {
                if(j==0||next[j]==0)
                {
                    break;
                }else
                {
                    j=next[j];
                }
            }
        }
    }
    return 0;
}
void esnext(char key[120],int next[120])
{
    int n=strlen(key);
    next[0]=-1;next[1]=0;
    int i=2,j;
    while(i<n)
    {
        j=next[i-1];
        while(key[j]!=key[i-1]&&j>0)
            j=next[j];
        if(j>-1)
            next[i]=j;
        else
            next[i]=0;
        i++;
    }
}
int delete(ele* books,int i,int n)
{
    int j;
    for(j=i;j<n-1;j++)
    {
        strcpy(books[j].name,books[j+1].name);
        strcpy(books[j].au,books[j+1].au);
        strcpy(books[j].pre,books[j+1].pre);
        books[j].age=books[j+1].age;
    }
}
int main()
{
    ele books[500];
    ele book;
    int i=0,op,n;
    FILE *in,*out;
    if((in=fopen("books.txt","r"))==NULL)
    {
        perror("books.txt");
        exit(0);
    }
    else
    {
        while(~fscanf(in,"%s",books[i].name))
        {
            fscanf(in,"%s",books[i].au);
            fscanf(in,"%s",books[i].pre);
            fscanf(in,"%d",&books[i++].age);
        }
            
    }
    qsort(books,i,sizeof(books[0]),cmp);
    n=i;
    scanf("%d",&op);
    while(op)
    {
        switch (op)
        {
        case 1:
        {
            scanf("%s",book.name);
            scanf("%s",book.au);
            scanf("%s",book.pre);
            scanf("%d",&book.age);
            i=position(books,book,n,0,n-1);
            insert(books,book,i,n);
            n++;
            break;
        }
        case 2:
        {
            char s[120];
            scanf("%s",s);
            int next[120];
            esnext(s,next);
            for(i=0;i<n;i++)
            {
                int sign = search(books[i].name,s,next);
                if(sign!=0)
                    printf("%-50s%-20s%-30s%-10d\n",books[i].name,books[i].au,books[i].pre,books[i].age);
            }
            break;
        }   
        case 3:
        {
            char s[120];
            scanf("%s",s);
            int next[120];
            esnext(s,next);
            for(i=0;i<n;i++)
            {
                int sign = search(books[i].name,s,next);
                if(sign!=0)
                {
                    delete(books,i,n);
                    n--;i--;
                }
            }
            break;
        }
        default:
            break;
        }
        scanf("%d",&op);
    }
    if((out=fopen("ordered.txt","w"))==NULL)
    {
        perror("ordered.txt");
        exit(0);
    }
    else
    {
        for(i=0;i<n;i++)
            fprintf(out,"%-50s%-20s%-30s%-10d\n",books[i].name,books[i].au,books[i].pre,books[i].age);
    }
    fclose(in);
    fclose(out);
    return 0;
}