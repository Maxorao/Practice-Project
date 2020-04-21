#include<stdio.h>
#include<stdlib.h>
int cal(int temp1,int temp2,char op)
{
    switch(op)
    {
        case '+':
        {
            return temp1+temp2;
        }
        case '-':
        {
            return temp1-temp2;
        }
        case '*':
        {
            return temp1*temp2;
        }
        case '/':
        {
            return temp1/temp2;
        }
    }
}
int main()
{ 
    char s[10000],op[200];
    int temp[1000]={0},sum=0,i=0,k=0,j=0;
    gets(s);
    op[j]=' ';
    while(op[j]!='=')
    {
        j++;
        while(s[i]==' ')
                i++;
        while(s[i]>='0'&&s[i]<='9')
            temp[k]=temp[k]*10+s[i++]-'0';
        while(s[i]==' ')
                i++;
        op[j]=s[i++];
        while(op[j]=='*'||op[j]=='/')
        {
            while(s[i]==' ')
                i++;
            while(s[i]>='0'&&s[i]<='9')
                temp[k+1]=temp[k+1]*10+s[i++]-'0';
            temp[k]=cal(temp[k],temp[k+1],op[j]);
            while(s[i]==' ')
                i++;
            op[j]=s[i++];
        }
        k++;
    }
    j=1;
    sum=temp[0];
    k=1;
    while(op[j]!='=')
    {
        sum=cal(sum,temp[k],op[j]);
        j++;k++;
    }
    printf("%d\n",sum);
}