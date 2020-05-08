#include"stdio.h"
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* rchild;
    struct node*  lchild;
}TreeNode;
TreeNode* root;
void init()
{
    root=NULL;
}
void insertTree(TreeNode* p)
{
    if(root==NULL)
    {
        root=(TreeNode*)malloc(sizeof(TreeNode));
        root->data=p->data;
        root->lchild=NULL;
        root->rchild=NULL;
        return;
    }
    
    TreeNode* q=root;
    while(1)
    {
        if(p->data>=q->data)
        {
            if(q->rchild==NULL)
            {
                q->rchild=p;
                p->rchild=NULL;
                p->lchild=NULL;
                return;
            }
            q=q->rchild;
            continue;
        }
        if(q->lchild==NULL)
        {
            q->lchild=p;
            p->rchild=NULL;
            p->lchild=NULL;
            return;
        }
        q=q->lchild;
        continue;
    }
}
void creatTree()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        TreeNode* p=(TreeNode*)malloc(sizeof(TreeNode));
        scanf("%d",&p->data);
        insertTree(p);
    }
    return;
}
void printTheLeaves(TreeNode* p,int cou)
{
    int cou1=cou,cou2=cou;
    if(p->lchild==NULL&&p->rchild==NULL)
    {
        printf("%d %d\n",p->data,cou);
        return;
    }
    if(p->lchild!=NULL)
    {
        cou1++;
        printTheLeaves(p->lchild,cou1);
    }
    if(p->rchild!=NULL)
    {
        cou2++;
        printTheLeaves(p->rchild,cou2);
    }
    return;
}
int main()
{
    init();
    creatTree();
    printTheLeaves(root,1);
    return 0;
}