#include<stdio.h>
int main()
{
    int i;
    char c=0;
    for(i=0;i<3;i++)
    {
        c=(c<<1)|1;
    }
    for(i=0;i<5;i++)
    {
        c<<=1;
    }
    printf("%x\n",c);
    return 0;
}