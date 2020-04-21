#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
    char a[27];
    int d[27];
    memset(d,0,27*sizeof(d[0]));
    scanf("%s",a);
    char b,c;
    int i=0,j=0;
    while((c=a[i++])!='\0')
    {
        d[c-'a']=1;
        b=a[i];
        if(d[b-'a']==1)
        {
            while(d[b-'a']==1)
            {
                for(j=i;j<strlen(a);j++)
                    a[j]=a[j+1];
                b=a[i];
            }  
        }
        else
            d[b-'a']=1;
    }
    i=strlen(a);
    for(j=25;j>-1;j--)
    {
        if(d[j]==0)
        {
            a[i]=j+'a';
            i++;
        }
    }
    a[26]='\0';
    FILE *in,*out;
    if((in=fopen("encrypt.txt","r"))==NULL)
    {
        perror("encrypt.txt");
        exit(0);
    }
    else
    {
        if((out=fopen("output.txt","w"))==NULL)
        {
            perror("output.txt");
            exit(0);
        }
        while((c=fgetc(in))!=EOF)
        {
            if(isalpha(c)!=0)
            {
                fprintf(out,"%c",a[c-'a']);
            }
            else
            {
                fprintf(out,"%c",c);
            }
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}