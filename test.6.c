#include<stdio.h>
#include<string.h>
void swap(char a[])
{
    int n=strlen(a),i;
    char* p=a;
    for(i=0;i<n/2;i++)
    {
        char temp=*(p+i);
        *(p+i)=*(p+n-1-i);
        *(p+n-1-i)=temp;
    }
}
void fuc(char s[]){
	
	if(s[0]=='0'&&strlen(s)==1)
		s[0]='0';
	else{
		while(s[0]=='0')
		for(int i=0;i<=strlen(s)-1;i++)
			s[i]=s[i+1];
	}	
}
void cal(char a[],char b[]){
	int i;
	char c[100];
	memset(c,0,100*sizeof(char));
	for(i=0;i<=strlen(b)-1;i++){
		if(a[i]>=b[i])
			c[i]=a[i]-b[i]+48;
		if(a[i]<b[i]){
			c[i]=a[i]+10-b[i]+48;
			while(1){
				int j=0;
				if(a[i+1+j]>'0'){
					a[i+1+j]--;
					break;
				}						
			else{
				a[i+1+j]='9';
				j++;
				}
			}	
		}
	}
	for(;i<=strlen(a)-1;i++)
		c[i]=a[i];
	swap(c);
	fuc(c);
	i=0;
    for(;i<strlen(c);i++)
        printf("%c",c[i]);
    printf("\n");
}
	
int main(){
	char a[82],b[82],c[82];
	gets(a);
	gets(b);
	fuc(a);
	fuc(b);
	
	
	if(strlen(a)>strlen(b)){
		swap(a);
		swap(b);
		cal(a,b);	
	}
	else if(strlen(a)==strlen(b)&&strcmp(a,b)>0)
	{
		swap(a);
		swap(b);
		cal(a,b);
	}
	else if(strlen(a)==strlen(b)&&strcmp(a,b)==0)
		printf("0\n");
	else{
		swap(a);
		swap(b);
		printf("-");
		cal(b,a);
	}
	
	return 0;
} 
