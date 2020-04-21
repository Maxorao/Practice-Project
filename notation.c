#include<stdio.h>
#include<string.h>
int main()
{
    char a[150],temp[150];
    memset(a,0,150*sizeof(char));
    memset(temp,0,150*sizeof(char));
    scanf("%s",temp);
    int i=0,cou=0;
    for(;i<strlen(temp);i++)
        a[i]=temp[i];
    memset(temp,0,150*sizeof(char));
    if(a[0]>='1'&&a[0]<='9')
    {
        while(a[cou]!='.')
        {
            temp[cou]=a[cou];
            cou++;
        }
        printf("%c.",temp[0]);
        for(i=1;i<cou;i++)
            putchar(temp[i]);
        i=cou;
        cou++;
        for(;cou<strlen(a);cou++)
            putchar(a[cou]);
        printf("e%d\n",i-1);
    }else if(a[0]=='0')
    {
        i=2;
        while(a[i]=='0')i++;
        putchar(a[i]);
        if(i==strlen(a)-1)
        {
            printf("e-%d\n",i-1);
            return 0;
        }
        putchar('.');
        for(cou=i+1;cou<strlen(a);cou++)
            putchar(a[cou]);
        printf("e-%d\n",i-1);
    }
        
    
    return 0;
}