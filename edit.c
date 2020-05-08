#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Stack
{
    int op[100];
    int pos[100];
    int top;
    char *sour[100];
}sta;
sta stack;
void mycat(char **des,char **sour)
{
    int a=strlen(*des);
    int b=strlen(*sour);
    int i=0;
    while(i<=b)
    {
        *(*des+a+i)=*(*sour+i);
        i++;
    }
}
void insert(int pos,char **des,char **sour)
{
    if(pos==0)
    {
        mycat(sour,des);
        strcpy(*des,*sour);
        return;
    }
    else if(pos==strlen(*des))
    {
        strcat(*des,*sour);
        return;
    }
    else
    {
        int i,j,a=strlen(*des),b=strlen(*sour);
        char temp[600];
        for(i=0;i<pos;i++)
            temp[i]=*(*des+i);
        for(j=0;j<b;j++,i++)
            temp[i]=*(*sour+j);
        for(j=pos;j<a;j++,i++)
            temp[i]=*(*des+j);
        temp[i]='\0';
        strcpy(*des,temp);
        return;
    }
    
}
void delete(int pos,int num,char **des)
{
    int i,a=strlen(*des);
    if(pos+num>=a)
    {
        *(*des+pos)='\0';
        return;
    }
    char *temp;
    int j=0;
    temp=(char*)malloc((a-pos-num+2)*sizeof(char));
    for(i=pos+num;i<=a;i++,j++)
    {
        *(temp+j)=*(*des+i);
    }
    for(j=0,i=pos;*(temp+j)!='\0';j++,i++)
    {
        *(*des+i)=*(temp+j);
    }
    *(*des+i)='\0';
    return;
}
void TurnBack(char **des)
{
    stack.top--;
    switch (stack.op[stack.top])
    {
        case 1:
        {
            int num=strlen(stack.sour[stack.top]);
            delete(stack.pos[stack.top],num,des);
            break;
        }
        case 2:
        {
            insert(stack.pos[stack.top],des,&stack.sour[stack.top]);
            break;
        }
        default:
            break;
    }
}
void Onepush(int op,int pos,char *sour)
{
    stack.op[stack.top]=op;
    stack.pos[stack.top]=pos;
    stack.sour[stack.top]=(char*)malloc(100*sizeof(char));
    strcpy(stack.sour[stack.top],sour);
    stack.top++;
}
void Twopush(int op,int pos,int num,char **des)
{
    int i,a=strlen(*des);
    stack.op[stack.top]=op;
    stack.pos[stack.top]=pos;
    stack.sour[stack.top]=(char*)malloc(100*sizeof(char));
    for(i=0;i<num&&i+pos<a;i++)
    {
        *(stack.sour[stack.top]+i)=*(*des+i+pos);
    }
    *(stack.sour[stack.top]+i)='\0';
    stack.top++;
}
int main()
{
    int n,i,op; 
    char* text;
    text=(char*)malloc(600*sizeof(char));
    gets(text);
    scanf("%d",&n);
    for(stack.top=0;stack.top<n;stack.top++)
    {
        scanf("%d",&stack.op[stack.top]);
        switch(stack.op[stack.top])
        {
            case 1:
            {
                stack.sour[stack.top]=(char*)malloc(100*sizeof(char));
                scanf("%d%s",&stack.pos[stack.top],stack.sour[stack.top]);
                break;
            }
            case 2:
            {
                stack.sour[stack.top]=(char*)malloc(100*sizeof(char));
                scanf("%d%s",&stack.pos[stack.top],stack.sour[stack.top]);
                break;
            }
            case 3:
            {
                break;
            }
        }
    }
    scanf("%d",&op);
    while(op!=-1)
    {
        int flag=0;
        switch(op)
        {
            case 1:
            {
                int pos;
                char* sour;
                sour=(char*)malloc(600*sizeof(char));
                scanf("%d%s",&pos,sour);
                Onepush(op,pos,sour);
                insert(pos,&text,&sour);
                break;
            }
            case 2:
            {
                int pos,num;
                scanf("%d%d",&pos,&num);
                Twopush(op,pos,num,&text);
                delete(pos,num,&text);
                break;
            }
            case 3:
            {
                TurnBack(&text);
                break;
            }
            case -1:
            {
                flag=-1;
                break;
            }
            default:
                break;
        }
        if(flag==-1)
        {
            break;
        }
        printf("%s\n",text);
        scanf("%d",&op);
    }
    printf("%s\n",text);
    return 0;
}