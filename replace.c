#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
int equal(char a,char b)
{
    if(a==b||fabs(a-b)==32)
        return 1;
    return 0;
}
int main()
{
    char a[30],b[30];
    scanf("%s",a);
    scanf("%s",b);
    int i=0;
    int j=strlen(a);
    FILE* in,*out;
    if((in=fopen("filein.txt","r"))==NULL)
    {
        perror("filein.txt");
        exit(0);
    }
    else
    {
        if((out=fopen("fileout.txt","w"))==NULL)
        {
            perror("fileout.txt");
            exit(0);
        }
        char temp[30];
        while((temp[0]=getc(in))!=EOF)
        {
            if(equal(temp[0],a[0]))
            {
                for(i=1;i<strlen(a);i++)
                {
                    temp[i]=getc(in);
                    if(!equal(temp[i],a[i]))
                        break;
                }
                if(i==j)
                {
                    fprintf(out,"%s",b);
                    i=0;
                }  
                else
                {
                    int d;
                    for(d=0;d<=i;d++)
                        fputc(temp[d],out);
                }
                
            }
            else
            {
                fputc(temp[0],out);
            }
            
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}