#include<stdio.h>
#define Maxsize 1000
typedef struct
{
    int fro;
    int rear;
    int count;
    int line[Maxsize];
}queue;
queue TheQ;
void init()
{
    TheQ.fro=1;
    TheQ.rear=1;
    TheQ.count=0;
}
void GetIn()
{
    int num,i;
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        TheQ.line[TheQ.rear]=0;
        TheQ.rear++;
        TheQ.count++;
    }
}
void GetOff()
{
    printf("%d : %d\n",TheQ.fro,TheQ.line[TheQ.fro]);
    TheQ.fro++;
    TheQ.count--;
}
void Wait()
{
    int i;
    for(i=TheQ.fro;i<TheQ.rear;i++)
    {
        TheQ.line[i]++;
    }
}
void Windows(int n)
{
    int i;
    for(i=0;i<n&&TheQ.count>0;i++)
    {
        GetOff();
    }
    if(TheQ.count<=0)
    {
        return;
    }
    Wait();
    return;
}
void Serve(int flag)
{
    if(flag==1)
    {
        if(TheQ.count>=21)
        {
            if(TheQ.count>=28)
            {
                Windows(5);
                return;
            }
            Windows(4);
            return;
        }
        Windows(3);
        return;
    }
    if(flag==0)
    {
        if(TheQ.count<35)
        {
            if(TheQ.count<28)
            {
                Windows(3);
                return;
            }
            Windows(4);
            return;
        }
        Windows(5);
        return;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    init();
    while(n--)
    {
        GetIn();
        Serve(1);
    }
    while(TheQ.count>0)
    {
        Serve(0);
    }
    return 0;
}