#include<stdio.h>
int cir(int n,int m)
{
	int p=0;
	for(int i=2;i<=n;i++)
	{
		p=(p+m)%i;
	}
	return p+1;
}
int main()
{
    int m,n;
    scanf("%d",&m);
    scanf("%d",&n);
    if(m<1)
    {
        printf("Invalid variable!\n");
        return 0;
    }
    printf("%d\n",cir(n,m));
    return 0;
}