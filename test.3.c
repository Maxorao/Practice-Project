#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i=0;
    FILE *fp;
    if((fp=fopen("demo.txt","r"))==NULL)
    {
        perror("error:");
        exit(0);
    }
    else
    {
        char key[20];
        scanf("%s",key);
        char word[100];
        while(~fscanf(fp,"%s",word))
        {
            
        }
    }
    fclose(fp);
    return 0;
}