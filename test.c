//--------- #include<stdio.h>
// #include<stdlib.h>
// typedef Node* nodepo;
// typedef struct 
// {
//     char s[30];
//     Node* next;
// }Node;
// Node* list;
// typedef struct 
// {
//     char s[30];
//     struct DNode* rlink;
//     struct DNode* llink;
// }DNode;
// DNode* head;
// int main()
// {
//     FILE *in;
//     if((in=fopen("test.txt","r"))==NULL)
//     {
//         perror("Can't open the file:");
//         exit(0);
//     }
//     else
//     {
        
//     }
    
//     return 0;
// }
//-------#include<stdio.h>
// long long fi(int n)
// {
//     long long i,sum=0;
//     for(i=3;i<n;i++)
//     {
//         sum+=(i*(i-1)*(i-2))/6;
//     }
//     return sum;
// }
// int main()
// {
//     int n;
//     scanf("%d",&n);
//     printf("%lld\n",fi(n));
//     return 0;
// }
#include<stdio.h>
int max(int a,int b)
{
    if(a>b)
        return a;
    else
    {
        return b;
    }
}
int main()
{
    int m,t,s;
    scanf("%d%d%d",&m,&t,&s);
    if(s%t==0)
    {
        printf("%d\n",max(m-s/t,0));
        return 0;
    }
    else
    {
        printf("%d\n",max(m-s/t-1,0));
        return 0;
    }
}