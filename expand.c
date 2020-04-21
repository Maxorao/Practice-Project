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
int main()
{
    char t1,t2;
    while(~scanf("%c",&t1))
    {
        if(t1!='-')
        {
            t2=t1;
            putchar(t1);
        }
        else
        {
            char t3;
            t3=getchar();
            if(ju(t2,t3)>0)
                while(t2<t3)
                {
                    t2++;
                    putchar(t2);
                }
            else
            {
                putchar(t1);
                putchar(t3);
            }
        }
    }
    return 0;
}