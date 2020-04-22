#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int istar(char c)
{
    if(c=='{'||c=='}'||c=='('||c==')')
        return 1;
    else 
        return 0;
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
typedef struct node
{
    char t[201];
    int  tline[201];
    int top;
}stack;
stack an;
int march(char a,char b)
{
    if(a=='('&&b==')')
        return 1;
    if(a=='{'&&b=='}')
        return 1;
    return 0;
}
char b[300];
int i=0,line=1;
int main()
{
    an.top=0;
    memset(an.t,0,sizeof(char));
    memset(b,0,sizeof(char));
    FILE *in;
    if((in=fopen("example.c","r"))==NULL)
    {
        perror("Can't open the file:");
        exit(0);
    }
    else
    {
        char c;
        int cou=0;
        i=0;
        while(~fscanf(in,"%c",&c))
        {
            if(c=='/')
            {
                fscanf(in,"%c",&c);
                if(c=='/')
                    while(~fscanf(in,"%c",&c))
                        if(c=='\n')
                            break; 
                if(c=='*')
                    while(~fscanf(in,"%c",&c))
                    {
                        if(c=='*')
                        {
                            fscanf(in,"%c",&c);
                            if(c=='/')
                                break;  
                        }
                    }
            }
            if(c=='\n')
            {
                while(c=='\n')
                    fscanf(in,"%c",&c);
                line++;
                continue;
            }
            if(le(c))
            {
                an.tline[an.top]=line;
                an.t[an.top++]=c;
                b[i++]=c;
                
            }
            else if(ri(c))
            {
                b[i++]=c;
                if(an.top==0)
                {
                    printf("without maching '%c' at line %d\n",c,line);
                    return 0;
                }
                else
                {
                    char temp=an.t[--an.top];
                    if(!march(temp,c))
                    {
                        printf("without maching '%c' at line %d\n",c,line);
                        return 0;
                    }   
                }
            }
        }
        i=0;
        if(an.top==0)
        {
            while(b[i]!='\0')
                printf("%c",b[i++]);
            printf("\n");
        }
        else
            printf("without maching '%c' at line %d\n",an.t[0],an.tline[0]);
    }
    return 0;
}