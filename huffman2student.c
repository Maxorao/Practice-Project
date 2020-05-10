//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode(Root);					//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 
char Text[10000]={'\0'};
void statCount()
{
	char c;
	int i=0;
	while(~fscanf(Src,"%c",&c))
	{
		if(c=='\n')
			continue;
		Ccount[(int)c]++;
		Text[i++]=c;
	}
	Ccount[0]=1;
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

typedef struct Node
{
	struct tnode* self;
	struct Node* next;
}List;
List* Forest;
void init()
{
	Forest=NULL;
}
void insert(struct tnode* p,int state)
{
	if(Forest==NULL)
	{
		Forest=(List*)malloc(sizeof(List));
		Forest->self=p;
		Forest->next=NULL;
		return;
	}
	List* Backward=NULL;
	List* Forward=Forest;
	while(Forward!=NULL)
	{
		if(p->weight<Forward->self->weight)
		{
			List* temp=(List*)malloc(sizeof(List));
			temp->self=p;
			temp->next=Forward;
			if(Backward==NULL)
			{
				Forest=temp;
				return;
			}
			Backward->next=temp;
			return;
		}
		if(p->weight==Forward->self->weight&&state==1)
		{
			if(p->c<Forward->self->c)
			{
				List* temp=(List*)malloc(sizeof(List));
				temp->self=p;
				temp->next=Forward;
				if(Backward==NULL)
				{
					Forest=temp;
					return;
				}
				Backward->next=temp;
				return;
			}
		}
		Backward=Forward;
		Forward=Forward->next;
	}
	Forward=(List*)malloc(sizeof(List));
	Forward->self=p;
	Forward->next=NULL;
	Backward->next=Forward;
	return;
}

void createHTree()
{
	int i;
	for(i=0;i<128;i++)
		if(Ccount[i]>0)
		{
			struct tnode* p=(struct tnode *)malloc(sizeof(struct tnode));
			p->c=i;p->weight=Ccount[i];
			p->left=p->right=NULL;
			insert(p,1);
		}
	while(Forest->next!=NULL)
	{
		struct tnode* p=(struct tnode *)malloc(sizeof(struct tnode));
		p->c='\0';p->weight=Forest->self->weight+Forest->next->self->weight;
		p->left=Forest->self;p->right=Forest->next->self;
		Forest=Forest->next->next;
		insert(p,0);
	}
	Root=Forest->self;
}


//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

char Code[9]={'\0'};
void GetCode(char c,char Code[])
{
	strcpy(HCode[(int)c],Code);
	return;
}

void GetHCode(struct tnode* p,char Code[],int top)
{
	if(p==NULL)
	{
		return;
	}
	if(p->right==NULL&&p->left==NULL)
	{
		GetCode(p->c,Code);
		return;
	}
	if(p->right!=NULL)
	{
		Code[top]='1';
		GetHCode(p->right,Code,top+1);
		Code[top]='\0';
	}
	if(p->left!=NULL)
	{
		Code[top]='0';
		GetHCode(p->left,Code,top+1);
		Code[top]='\0';
	}
	return;

}

void makeHCode()
{
	GetHCode(Root,Code,0);
} 



//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ



void atoHZIP()
{
	int i=0,j=0,k=0;
    unsigned char c='\0';
    while(Text[i]!='\0')
    {
        for(;HCode[Text[i]][k]!='\0'&&j<8;k++,j++)
        {
            c=(c<<1)|(HCode[Text[i]][k]-'0');
        }
        if(HCode[Text[i]][k]=='\0')
        {
            i++;
            k=0;
        }
        if(j==8)
        {
            printf("%x",c);
            fprintf(Obj,"%c",c);
            j=0;
            c=0;
        }
        if(Text[i]=='\0')
        {
            for(;HCode['\0'][k]!='\0'&&j<8;k++,j++)
            {
                c=(c<<1)|(HCode['\0'][k]-'0');
            }
            if(HCode['\0'][k]=='\0')
            {
                for(;j<8;j++)
                {
                    c=c<<1;
                }
                printf("%x\n",c);
                fprintf(Obj,"%c",c);
                return;
            }
            if(j==8)
            {
                printf("%x",c);
                fprintf(Obj,"%c",c);
                for(j=0;HCode['\0'][k]!='\0'&&j<8;k++,j++)
                {
                    c=(c<<1)|(HCode['\0'][k]-'0');
                }
                for(;j<8;j++)
                {
                    c=c<<1;
                }
                printf("%x\n",c);
                fprintf(Obj,"%c",c);
                return;
            }
        }
    }

	
}

//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
