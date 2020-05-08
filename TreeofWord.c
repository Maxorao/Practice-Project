#include"stdio.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct node
{
    char word[30];
    int count;
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
        root=p;
        return;
    }
    
    TreeNode* q=root;
    while(1)
    {
        int cmp=strcmp(p->word,q->word);
        if(cmp>0)
        {
            if(q->rchild==NULL)
            {
                q->rchild=p;
                return;
            }
            q=q->rchild;
            continue;
        }
        if(cmp==0)
        {
            q->count++;
            return;
        }
        if(q->lchild==NULL)
        {
            q->lchild=p;
            return;
        }
        q=q->lchild;
        continue;
    }
}
int GetWord(char word[30],FILE* in)
{
    char alpha;
    int i=0,flag;
    while((flag=fscanf(in,"%c",&alpha))!=-1)
    {
        if(isalpha(alpha))
            break;
    }
    if(flag==-1)
        return 0;
    word[i++]=tolower(alpha);
    while(~fscanf(in,"%c",&alpha))
    {
        if(!isalpha(alpha))
            break;
        word[i++]=tolower(alpha);
    }
    word[i]='\0';
    return 1;
}
void creatTree()
{
    FILE *in;
    if((in=fopen("article.txt","r"))==NULL)
    {
        perror("Can't open the file");
        exit(-1);
    }
    else
    {
        while(1)
        {
            TreeNode* p=(TreeNode*)malloc(sizeof(TreeNode));
            p->count=1;
            p->lchild=NULL;
            p->rchild=NULL;
            if(!GetWord(p->word,in))
                break;
            else
            {
                 insertTree(p);
            } 
        }
    }
    return;
}
void printTheLeaves(TreeNode* p)
{
    if(p->lchild==NULL&&p->rchild==NULL)
    {
        printf("%s %d\n",p->word,p->count);
        return;
    }
    if(p->lchild!=NULL)
    {
        printTheLeaves(p->lchild);
    }
    printf("%s %d\n",p->word,p->count);
    if(p->rchild!=NULL)
    {
        printTheLeaves(p->rchild);
    }
    return;
}
int main()
{
    init();
    creatTree();
    printf("%s",root->word);
    if(root->rchild!=NULL)
        printf(" %s",root->rchild->word);
    else
    {
        printf("\n");
    }
    if(root->rchild->rchild!=NULL)
        printf(" %s\n",root->rchild->rchild->word);
    else
    {
        printf("\n");
    }
    printTheLeaves(root);
    return 0;
}