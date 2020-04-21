#include<stdio.h>
void perm(int a[110],int b[110],int n,int k)
{
    int i,j;
    if(k==n)
    {
        for(i=1;i<=n;i++)
        {
            if(b[i]==1)
                continue;
            else
            {
                b[i]=1;
                a[k]=i;
            }
        }
        for(i=1;i<=n;i++)
            printf("%d ",a[i]);
        printf("\n");
        return;
    } 
    for(i=1;i<=n;i++)
    {
        if(b[i]==1)
            continue;
        else
        {
            int c[110];
            for(j=1;j<=n;j++)
                c[j]=b[j];
            c[i]=1;
            a[k]=i;
            perm(a,c,n,k+1);
        }
    }
}
int main()
{
    int n,i;
    int a[110],b[110];
    for(i=1;i<=110;i++)
        a[i]=b[i]=0;
    scanf("%d",&n);
    perm(a,b,n,1);
    return 0;
}