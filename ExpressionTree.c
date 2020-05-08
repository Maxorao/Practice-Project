#include<stdio.h>
#include<stdlib.h>
#define MainStream 1
#define Maxsize 100
typedef struct tree
{
    union {char op;int number;};
    struct tree* lchild;
    struct tree* rchild;
}TreeNode;
typedef struct node
{
    int top;
    TreeNode* Tstack[Maxsize];
}Stack;
Stack MainStack;
Stack SubStack;
TreeNode* root;
int BackExpression[100][2];
void init();
int getNum();
void SinglePush(int data);
TreeNode* popup();
void Combine(char op);
TreeNode* getNode();
void CreatTree();
void BackTransition();
void myprint(TreeNode p);
void printleaves();
int calculate(TreeNode* p);
int main()
{
    init();
    BackTransition();
    CreatTree();
    printleaves();
    return 0;
}
void init()
{
    MainStack.top=0;
    SubStack.top=0;
    root=(TreeNode*)malloc(sizeof(TreeNode));
}
void SinglePush(int data)
{
    MainStack.Tstack[MainStack.top]=(TreeNode*)malloc(sizeof(TreeNode));
    (MainStack.Tstack[MainStack.top])->lchild=NULL;
    (MainStack.Tstack[MainStack.top])->rchild=NULL;
    (MainStack.Tstack[MainStack.top])->number=data;
    MainStack.top++;
}
void pushTree(TreeNode* third)
{
    MainStack.Tstack[MainStack.top]=third;
    MainStack.top++;
}
void Combine(char op)
{
    TreeNode* First;
    TreeNode* Second;
    TreeNode* Third=(TreeNode*)malloc(sizeof(TreeNode));
    Second=popup();
    First=popup();
    Third->op=op;
    Third->lchild=First;
    Third->rchild=Second;
    pushTree(Third);
}
TreeNode* popup()
{
    MainStack.top--;
    return MainStack.Tstack[MainStack.top];
}
void CreatTree()
{
    int i;
    for(i=0;BackExpression[i][1]!=-1;i++)
    {
        if(BackExpression[i][1]==0)
        {
            SinglePush(BackExpression[i][0]);
            continue;
        }
        if(BackExpression[i][1]==1)
        {
            Combine(BackExpression[i][0]);
            continue;
        }
    }
}
void BackTransition()
{

    char temp;
    char stack[100]={0};
    int top1=0,top2=-1,prior[150]={0};
    prior['(']=0;
    prior[')']=0;
    prior['=']=0;
    prior['+']=1;
    prior['-']=1;
    prior['*']=2;
    prior['/']=2;
    prior['%']=2;
    while(~scanf("%c",&temp)&&stack[top2]!='=')
    {
        if(temp>='0'&&temp<='9')
        {
            int num=0;
            while(temp>='0'&&temp<='9')
            {
                num=num*10+temp-'0';
                scanf("%c",&temp);
            }
            BackExpression[top1++][0]=num;
        }
        if(temp==' ')
            continue;
        if(top2==-1||temp=='(')
        {
            stack[++top2]=temp;
            continue;
        }
        else
        {
            int d=stack[top2];
            int n=prior[temp]-prior[d];
            if(n>0)
            {
                stack[++top2]=temp;
                continue;
            }
            while(n<=0)
            {
                d=stack[top2--];
                BackExpression[top1][1]=1;
                BackExpression[top1++][0]=d;
                if(top2==-1)
                    break;
                d=stack[top2];
                if(d=='('&&temp==')')
                    break;
                n=prior[temp]-prior[d];
            }
            if(d=='('&&temp==')')
            {
                top2--;
                continue;
            }
            stack[++top2]=temp;
            continue;
        }
    }
    BackExpression[top1][1]=-1;
    return;
}
void printleaves()
{
    root=MainStack.Tstack[0];
    if(root!=NULL)
    {
        myprint(*root);
    }
    if(root->lchild!=NULL)
    {
        printf(" ");
        myprint(*(root->lchild));
    }
    else
    {
        printf("\n");
    }
    if(root->rchild!=NULL)
    {
        printf(" ");
        myprint(*(root->rchild));
        printf("\n");
    }
    printf("%d\n",calculate(root));
    return;
}
int calculate(TreeNode* p)
{
    if(p->lchild==NULL&&p->rchild==NULL)
    {
        return p->number;
    }
    int a=calculate(p->lchild);
    int b=calculate(p->rchild);
    switch (p->op)
    {
    case '+':
        {
            return a+b;
        }
    case '-':
        {
            return a-b;
        }
    case '*':
        {
            return a*b;
        }
    case '/':
        {
            return a/b;
        }
    }
}
void myprint(TreeNode p)
{
    if(p.lchild!=NULL)
    {
        printf("%c",p.op);
        return;
    }
    else
    {
        printf("%d",p.number);
        return;
    }
}