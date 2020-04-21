#include<stdio.h>
#include<string.h>
char a[82],b[82],c[82];
void fuc(char s[]){
	gets(s);
	while(s[0]=='0')
		for(int i=0;i<=strlen(s)-1;i++)
			s[i]=s[i+1];
}

int main(){
	
	fuc(a);
	fuc(b);
	if(strlen(a)>=strlen(b)){
		for(int i=strlen(a)-1,j=strlen(b)-1,k=0;i>=0&&j>=0&&k<=82;i--,j--,k++){
			if(a[i]>b[j])
				c[k]=a[i]-b[j]+48;
			if(a[i]<b[j]){
				a[i-1]--;
				c[k]=a[i]+10-b[j]+48;
					
			}	
		}
		printf("%s\n",c); 
		for(int i=0;i<=strlen(a)-strlen(b)-1;i++)
			printf("%c",a[i]);
		for(int i=strlen(c)-1;i>=0;i--)
			printf("%c",c[i]);	
	}
	else{
		for(int i=strlen(a)-1,j=strlen(b)-1,k=0;i>=0,j>=0,k<=82;i--,j--,k++){
			if(b[j]>=a[i])
				c[k]=b[j]-a[i]+48;
			if(b[j<a[i]]){
				b[j-1]--;
				c[k]=b[j]+10-a[i]+48;
					
			}	
		}
		printf("%s",c); 
		printf("-");		
		for(int i=0;i<=strlen(b)-strlen(a)-1;i++)
			printf("%c",b[i]);	
		for(int i=strlen(c)-1;i>=0;i--)
			printf("%c",c[i]);
	}
	
	return 0;
} 
