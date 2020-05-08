#include<stdio.h>
#include<stdlib.h>
int or(int a[],int n)
{
    int i,T=0;
    for(i=0;i<n;i++)
        T|=a[i];
    return T;
}
int main()
{
    int n,i,k,x;
    scanf("%d%d%d",&n,&k,&x);
    int* a=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    while(k--)
    {
        for
    }
    return 0;
}