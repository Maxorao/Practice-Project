#include<stdio.h>
#include<string.h>
void reverse(char a[])
{
    int n=strlen(a),i;
    char* p=a;
    for(i=0;i<n/2;i++)
    {
        char temp=*(p+i);
        *(p+i)=*(p+n-1-i);
        *(p+n-1-i)=temp;
    }
}
void mius(char a[],char b[])
{
    int i;
    char c[100];
    memset(c,0,100*sizeof(char));
    int n=strlen(b);
    int k=strlen(a);
    for(i=0;i<n;i++)
    {
        if(a[i]<b[i])
        {
            c[i]=10+a[i]-b[i]+'0';
            int j=0;
            while(1)
            {
                if(a[i+1+j]>'0')
                {
                    a[i+1+j]--;
                    break;
                }
                else
                {
                    a[i+1+j]='9';
                    j++;
                }   
            }
        }else if(a[i]>=b[i])
        {
            c[i]=a[i]-b[i]+'0';
        }
    }
    for(;i<k;i++)
    {
        c[i]=a[i];
    }
    reverse(c);
    i=0;
    if(c[0]=='0')
    {
        for(i=0;c[i]=='0';i++);
    }
    for(;i<strlen(c);i++)
        printf("%c",c[i]);
    printf("\n");
}
int main()
{
    char a[100],b[100],temp[100];
    memset(a,0,100*sizeof(char));
    memset(b,0,100*sizeof(char));
    int i=0,k;
    scanf("%s",temp);
    if(temp[0]=='0')
    {
        for(i=0;temp[i]=='0';i++);
        memset(a,0,100*sizeof(char));
        for(k=0;i<strlen(temp);i++)
            a[k++]=temp[i];
    }else
    {
        for(i=0;i<strlen(temp);i++)
            a[i]=temp[i];
    }
    memset(temp,0,100*sizeof(char));
    scanf("%s",temp);
    i=0;
    if(temp[0]=='0')
    {
        for(i=0;temp[i]=='0';i++);
        memset(b,0,100*sizeof(char));
        for(k=0;i<strlen(temp);i++)
            b[k++]=temp[i];
    }
    else
    {
        for(i=0;i<strlen(temp);i++)
            b[i]=temp[i];
    }
    if(strlen(a)>strlen(b))
    {
        reverse(a);
        reverse(b);
        mius(a,b);
    }
    else if(strlen(a)==strlen(b))
    {
        if(strcmp(a,b)>0)
        {
            reverse(a);
            reverse(b);
            mius(a,b);    
        }else if(strcmp(a,b)==0)
        {
            printf("0\n");
        }else
        {
            reverse(a);
            reverse(b);
            printf("-");
            mius(b,a);
        }  
    }
    else
    {
        reverse(a);
        reverse(b);
        printf("-");
        mius(b,a);
    }
    return 0;
}