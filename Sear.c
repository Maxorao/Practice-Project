#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char st[250];
    int stli[250];
    int top;
}stack;
stack sta;
char a[250];
FILE *in;
int line=1;
void init()
{
    memset(sta.st,0,sizeof(char));
    memset(a,0,sizeof(char));
    sta.top=-1;
}
int le(char c)
{
    if(c=='('||c=='{')
        return 1;
    else 
        return 0;
}
int ri(char c)
{
    if(c==')'||c=='}')
        return 1;
    else 
        return 0;
}
int cmp(char d,char c)
{
    if(d=='('&&c==')')
        return 1;
    else if(d=='{'&&c=='}')
        return 1;
    else 
        return 0;
}
char EscapeL()
{
    char c;
    fscanf(in,"%c",&c);
    if(c=='/')
    {
        while(c!='\n')
            fscanf(in,"%c",&c);
        return c;
    }
    else if(c=='*')
    {
        fscanf(in,"%c",&c);
        while(c!='*')
        {
            fscanf(in,"%c",&c);
            if(c=='\n')
            {
                line++;
                while(c=='\n'&&(~fscanf(in,"%c",&c)));
            }
        }
        fscanf(in,"%c",&c);
        if(c=='/')
            return c;
        
    }
    else
    {
        return c;
    }
    return '/';
}
char EscapeConst()
{
    char c;
    fscanf(in,"%c",&c);
    while(c!='"')
        fscanf(in,"%c",&c);
    return c;
}
// char ChangeLine()
// {
//     line++;
//     char c='\n';
//     while(c=='\n'&&(~fscanf(in,"%c",&c)));
//     if(c!='\n')
//     {
//         if(c=='/')
//             return EscapeL();
//         if(c=='"')
//             return 
//     }
//     else(c)
// }
int main()
{
    init();
    if((in=fopen("example.c","r"))==NULL)
    {
        perror("Can't open the file");
        exit(0);
    }
    else
    {
        int i=0;
        char c,d;
        while(~fscanf(in,"%c",&c))
        {
            if(c=='/')
                c=EscapeL();
            if (c=='"')
                c=EscapeConst();
            // if(c=='\n')
            //     c=ChangeLine();
            while(c=='\n'&&(~fscanf(in,"%c",&c)))
            {
                line++;
                while(c=='\n'&&(~fscanf(in,"%c",&c)));
                if(c=='/')
                    c=EscapeL();
                if (c=='"')
                    c=EscapeConst();
            }
            if(le(c))
            {
                if(c=='{'&&sta.st[sta.top]=='(')
                {
                    printf("without maching '(' at line %d\n",sta.stli[sta.top]);
                    return 0;
                }
                sta.st[++sta.top]=c;
                sta.stli[sta.top]=line;
                a[i++]=c;
                continue;
            }
            else if(ri(c))
            {
                if(sta.top==-1)
                {
                    printf("without maching '%c' at line %d\n",c,line+1);
                    return 0;
                }   
                else
                {
                    d=sta.st[sta.top--];
                    if(!cmp(d,c))
                    {
                        printf("without maching '%c' at line %d\n",c,line);
                        return 0;
                    }
                    else
                        a[i++]=c;
                }
            }
        }
        if(sta.top>-1)
        {
            printf("without maching '%c' at line %d\n",sta.st[0],sta.stli[0]);
            return 0;
        }
        else
        {
            printf("%s\n",a);
            return 0;
        } 
    }
    return 0;
}