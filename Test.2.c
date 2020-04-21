#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int ju(char a,char b)
{
    if(a>='0'&&(a<='9'))
        if(b>a&&(b<='9'))
            return 1;
        else
        {
            return -1;
        }      
    else if(a>='a'&&(a<='z'))
        if(b>a&&(b<='z'))
            return 1;
        else
        {
            return -1;
        }
    else if(a>='A'&&(a<='Z'))
        if(b>a&&(b<='Z'))
            return 1;
        else 
            return -1;
    else
    {
        return -1;
    }
    
}
    char s[100000];
    char ex[200000];
int main()
{
    memset(ex,'\0',200000*sizeof(char));
    gets(s);
    int i=0,j=0;
    for(;i<strlen(s);i++)
    {
        if(s[i]!='-')
        {
            ex[j++]=s[i];
            continue;
        }
        else
        {
            if(ju(s[i-1],s[i+1])>0)
            {
                ex[j]=s[i-1]+1;
                while(ex[j]<s[i+1]-1)
                    ex[++j]=ex[j]+1;
            }else
            {
                ex[j++]=s[i];
            }
        }
    }
    printf("%s\n",ex);
    return 0;
}