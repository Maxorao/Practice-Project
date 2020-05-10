//文件压缩-Huffman实现
#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>

#define  MAXSIZE  32

struct  tnode  {                        //Huffman树结构
        char  c;                
        int  weight;                //树节点权重，叶节点为字符和它的出现次数
        struct  tnode  *left,*right;
}  ;  
int  Ccount[128]={0};                //存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数  
struct  tnode  *Root=NULL;          //Huffman树的根节点
char  HCode[128][MAXSIZE]={{0}};  //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）  
int  Step=0;                        //实验步骤  
FILE  *Src,  *Obj;
        
void  statCount();                //步骤1：统计文件中字符频率
void  createHTree();                //步骤2：创建一个Huffman树，根节点为Root  
void  makeHCode();                //步骤3：根据Huffman树生成Huffman编码
void  atoHZIP();                  //步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void  print1();                        //输出步骤1的结果
void  print2(struct  tnode  *p);        //输出步骤2的结果  
void  print3();                        //输出步骤3的结果
void  print4();                        //输出步骤4的结果

int  main()
{
                if((Src=fopen("input.txt","r"))==NULL)  {
                        fprintf(stderr,  "%s  open  failed!\n",  "input.txt");
                return  1;  
        }
        if((Obj=fopen("output.txt","w"))==NULL)  {
                fprintf(stderr,  "%s  open  failed!\n",  "output.txt");
                return  1;
        }
        scanf("%d",&Step);                //输入当前实验步骤  
        
        statCount();                        //实验步骤1：统计文件中字符出现次数（频率）
        (Step==1)?print1():1;              //输出实验步骤1结果        
        createHTree();                        //实验步骤2：依据字符频率生成相应的Huffman树
        (Step==2)?print2(Root):2;          //输出实验步骤2结果        
        makeHCode();                //实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
        (Step==3)?print3():3;              //输出实验步骤3结果
        (Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果        

        fclose(Src);
        fclose(Obj);
                return  0;
}  

//【实验步骤1】开始  
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




//【实验步骤1】结束

//【实验步骤2】开始
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





//【实验步骤2】结束

//【实验步骤3】开始
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






//【实验步骤3】结束

//【实验步骤4】开始
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




//【实验步骤4】结束

void  print1()
{
        int  i;
        printf("NUL:1\n");
        for(i=1;  i<128;  i++)
                if(Ccount[i]  >  0)
                        printf("%c:%d\n",  i,  Ccount[i]);
}

void  print2(struct  tnode  *p)
{
        if(p  !=  NULL){
                if((p->left==NULL)&&(p->right==NULL))  
                        switch(p->c){
                                case  0:  printf("NUL  ");break;
                                case  '  ':    printf("SP  ");break;
                                case  '\t':  printf("TAB  ");break;
                                case  '\n':    printf("CR  ");break;
                                default:  printf("%c  ",p->c);  break;
                        }
                print2(p->left);
                print2(p->right);
        }
}

void  print3()
{
        int  i;
        
        for(i=0;  i<128;  i++){
                if(HCode[i][0]  !=  0){
                        switch(i){
                                case  0:  printf("NUL:");break;
                                case  '  ':    printf("SP:");break;
                                case  '\t':  printf("TAB:");break;
                                case  '\n':    printf("CR:");break;
                                default:  printf("%c:",i);  break;
                        }
                        printf("%s\n",HCode[i]);
                }
        }
}  

void  print4()
{
        long  int  in_size,  out_size;
        
        fseek(Src,0,SEEK_END);
        fseek(Obj,0,SEEK_END);
        in_size  =  ftell(Src);
        out_size  =  ftell(Obj);
        
        printf("\n原文件大小：%ldB\n",in_size);
        printf("压缩后文件大小：%ldB\n",out_size);
        printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
