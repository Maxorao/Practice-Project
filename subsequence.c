#include<stdio.h>
#include<math.h>
int SubStatic(int A[],int Left,int Right)
{
    int MaxLeftSum,MaxRightSum;
    int MaxLeftBorderSum,MaxRightBorderSum;
    int LeftBorderSum,RightBorderSum;
    int Center,i;

    if(Left == Right)
        return 1;

    Center =(Left+Right) / 2;
    MaxLeftSum = SubStatic(A,Left,Center);
    MaxRightSum = SubStatic(A,Center+1,Right);

    if(abs(A[Center]-A[Center+1])<=2)
    {
        MaxLeftBorderSum = 1; LeftBorderSum = 1;
        for(i=Center; i>Left; i--)
        {
            if(abs(A[i]-A[i-1])<=2)
                LeftBorderSum++;
            else
            {
                break;
            }
            
            if(LeftBorderSum>MaxLeftBorderSum)
                MaxLeftBorderSum = LeftBorderSum;
        }

        MaxRightBorderSum = 1; RightBorderSum = 1;
        for(i=Center+1; i<Right; i++)
        {
            if(abs(A[i]-A[i+1])<=2)
                RightBorderSum++;
            else
            {
                break;
            }
            
            if(RightBorderSum>MaxRightBorderSum)
                MaxRightBorderSum = RightBorderSum;
        }

        return Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
    }
    return Max3(MaxLeftSum,MaxRightSum,1);
}
int Max3(int a,int b,int c)
{
    if(a>=b)
    {
        if(c>=a)
            return c;
        else
        {
            return a;
        }
        
    }
    else
    {
        if(c>=b)
            return c;
        else
        {
            return b;
        }
        
    }
    
}
int main()
{
    int i,n;
    scanf("%d",&n);
    int * a=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    int MaxSubStatic = SubStatic(a,0,n-1);
    printf("%d\n",MaxSubStatic);
    return 0;
}