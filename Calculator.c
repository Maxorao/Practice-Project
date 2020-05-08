#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
    int top1;
    int top2;
    int NuPool[2000];
    char OpPool[1000];
}stack;
stack a;
int prior[150];
void init()
{
    a.top1=-1;
    a.top2=-1;
    memset(a.OpPool,0,sizeof(char));
    prior['(']=0;
    prior[')']=0;
    prior['=']=0;
    prior['+']=1;
    prior['-']=1;
    prior['*']=2;
    prior['/']=2;
    prior['%']=2;
}
int cal(char op,int a,int b)
{
    switch (op)
    {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    case '/':
        return a/b;
    case '%':
        return a%b;
    default:
        break;
    }
    return -1;
}
int pushNu(int b)
{
    if(a.top1>=2000)
        return 0;
    else
    {
        a.NuPool[++a.top1]=b;
        return 1;
    }
}
int popNu()
{
    if(a.top1<=-1)
        return -1;
    else 
    {
        return a.NuPool[a.top1--];
    }
}
int pushOp(char b)
{
    if(a.top2>=2000)
        return 0;
    else
    {
        a.OpPool[++a.top2]=b;
        return 1;
    }
}
int popOp()
{
    if(a.top2<=-1)
        return -1;
    else 
    {
        return a.OpPool[a.top2--];
    }
}
int getTop()
{
    if(a.top2>=0)
        return a.OpPool[a.top2];
    else
        return 0;
}
int gra(char c,char d)
{
    return prior[c]-prior[d];
}
int march(char d,char c)
{
    if(d==40&&c==')')
        return 1;
    else return 0;
}
int main()
{
    init();
    char c;
    while(~scanf("%c",&c))
    {
        if(c>='0'&&c<='9')
        {
            int temp=0;
            while(c>='0'&&c<='9')
            {
                temp=c-'0'+temp*10;
                scanf("%c",&c);
            }
            pushNu(temp);
        }
        if(c==' ')
            continue;
        if(a.top2==-1||c=='(')
        {
            pushOp(c);
            continue;
        }
        else 
        {
            int d=getTop();
            int n=gra(c,d);
            if(n>0)
            {
                pushOp(c);
                continue;
            }
            while(n<=0)
            {
                d=popOp();
                int num1=popNu();
                int num2=popNu();
                pushNu(cal(d,num2,num1));
                d=getTop();
                if(d==0||march(d,c))
                    break;
                n=gra(c,d);
            }
            if(march(d,c))
            {
                popOp();
                continue;
            }
            pushOp(c);
        }
        if(c=='=')
        {
            printf("%d\n",a.NuPool[a.top1]);
            return 0;
        }
    }
    return 0;
}