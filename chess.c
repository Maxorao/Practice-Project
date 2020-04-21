#include<stdio.h>
#include<string.h>
#include<math.h>
int ju(int a[21][21])
{
    int i,j;
    int cou1=-1,cou2=0;
    for(i=1;i<20;i++,cou1=-1)
        for(j=1;j<16;j++)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i][j+1]+a[i][j+2]+a[i][j+3]);
            if(12==cou1*cou2&&7==cou1+cou2)
            {
                if(1==a[i][j])
                {
                    if(0==a[i][j-1])
                        printf("1:%d,%d\n",i,j);
                    else 
                        printf("1:%d,%d\n",i,j-1);
                    return 0;
                } 
                else 
                {
                    if(0==a[i][j-1])
                        printf("2:%d,%d\n",i,j);
                    else
                        printf("2:%d,%d\n",i,j-1);
                    return 0;
                }
            }
    }
    for(j=1;j<20;j++,cou1=-1)
        for(i=1;i<16;i++)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i+1][j]+a[i+2][j]+a[i+3][j]);
            if(12==cou1*cou2&&7==cou2+cou1)
            {
                if(1==a[i][j])
                {
                    if(0==a[i-1][j])
                        printf("1:%d,%d\n",i,j);
                    else 
                        printf("1:%d,%d\n",i-1,j);
                    return 0;
                }    
                else 
                {
                    if(0==a[i][j-1])
                        printf("2:%d,%d\n",i,j);
                    else
                        printf("2:%d,%d\n",i-1,j);
                    return 0;
                }
            }
        }
    for(j=16;j>0;j--,cou1=-1)//第一次正斜向扫描
    {
        int temp=j;
        for(i=1;i<17&&j<17;i++,j++)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i+1][j+1]+a[i+2][j+2]+a[i+3][j+3]);
            if(12==cou1*cou2&&7==cou1+cou2)
            {
                if(1==a[i][j])
                {
                    if(0==a[i-1][j-1])
                        printf("1:%d,%d\n",i,j);
                    if(1==a[i-1][j-1])
                        printf("1:%d,%d\n",i-1,j-1);
                    return 0;
                }
                else
                {
                    if(0==a[i-1][j-1])
                        printf("2:%d,%d\n",i,j);
                    if(-1==a[i-1][j-1])
                        printf("2:%d,%d\n",i-1,j-1);
                    return 0;
                }
                
            }
        }
        j=temp;
    }
    for(i=1;i<17;i++,cou1=-1)//第二次正斜向扫描
    {
        int temp=i;
        for(j=1;i<17&&j<17;i++,j++)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i+1][j+1]+a[i+2][j+2]+a[i+3][j+3]);
            if(12==cou1*cou2&&7==cou1+cou2)
            {
                if(1==a[i][j])
                {
                    if(0==a[i-1][j-1])
                        printf("1:%d,%d\n",i,j);
                    if(1==a[i-1][j-1])
                        printf("1:%d,%d\n",i-1,j-1);
                    return 0;
                }
                else
                {
                    if(0==a[i-1][j-1])
                        printf("2:%d,%d\n",i,j);
                    if(-1==a[i-1][j-1])
                        printf("2:%d,%d\n",i-1,j-1);
                    return 0;
                }
                
            }
        }
        i=temp;
    }
    for(j=4;j<20;j++,cou1=-1)//第一次反斜向扫描
    {
        int temp=j;
        for(i=1;i<17&&j>3;i++,j--)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i+1][j-1]+a[i+2][j-2]+a[i+3][j-3]);
            if(12==cou1*cou2&&7==cou1+cou2)
            {
                if(1==a[i][j])
                {
                    if(0==a[i-1][j+1])
                        printf("1:%d,%d\n",i,j);
                    if(1==a[i-1][j+1])
                        printf("1:%d,%d\n",i-1,j+1);
                    return 0;
                }
                else
                {
                    if(0==a[i-1][j+1])
                        printf("2:%d,%d\n",i,j);
                    if(-1==a[i-1][j+1])
                        printf("2:%d,%d\n",i-1,j+1);
                    return 0;
                }
            }
        }
        j=temp;
    }
    for(i=1;i<17;i++,cou1=-1)//第二次反斜向扫描
    {
        int temp=i;
        for(j=19;i<17&&j>3;i++,j--)
        {
            cou2=cou1;
            cou1=fabs(a[i][j]+a[i+1][j-1]+a[i+2][j-2]+a[i+3][j-3]);
            if(12==cou1*cou2&&7==cou1+cou2)
            {
                if(1==a[i][j])
                {
                    if(0==a[i-1][j+1])
                        printf("1:%d,%d\n",i,j);
                    if(1==a[i-1][j+1])
                        printf("1:%d,%d\n",i-1,j+1);
                    return 0;
                }
                else
                {
                    if(0==a[i-1][j+1])
                        printf("2:%d,%d\n",i,j);
                    if(-1==a[i-1][j+1])
                        printf("2:%d,%d\n",i-1,j+1);
                    return 0;
                }
            }
        }
        i=temp;
    }
    return -1;
}

int main()
{
    int a[21][21];
    int i,j;
    for(i=1;i<20;i++)
        for(j=1;j<20;j++)
        {
            scanf("%d",&a[i][j]);
            if(2==a[i][j])
                a[i][j]=-1;
        }
    if(-1==ju(a))
        printf("No\n");
    return 0;
}