#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>
#include <string.h>
#define  FOOD  "█"//我们把蛇身子和食物，以及地图用黑框框表示，定义为宏
//蛇初始位置的坐标
#define  INIT_X 24F
#define  INIT_Y 2
//设置光标位置，之后会使用这个函数来进行打印蛇身子，食物，地图等
void SetPos(int x,int y){
	HANDLE handle =  GetStdHandle(STD_OUTPUT_HANDLE);//把标准输出的句柄得到，并交给变量handle，
	COORD pos = {0};
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);//设置handle的输出位置，
}
//画地图
void DrawMap(void){
	int i;
	for (i=0;i<58;i+=2)//画出地图的上边界，在控制界面每一个汉字，占两位，所以每次i+2
 
	{
		SetPos(i,0);
		printf(FOOD);
	}
	for (i=0;i<58;i+=2)//画出地图的下边界
	{
		SetPos(i,26);
		printf(FOOD);
	}
	for (i=0;i<26;i++)//画出地图的左边界
	{
		SetPos(0,i);
		printf(FOOD);
	}
	for (i=0;i<=26;i++)//画出地图的右边界
	{
		SetPos(58,i);
		printf(FOOD);
	}
} 
// 蛇身子节点，因为我们要打印蛇身子的每一个节点在地图上显示，所以结构体里面要有蛇身子结点的x,y坐标，
 typedef struct node{
 	int x;
	int y;
	struct node* next;//因为使用链表的结构，所以我们要储存每一个结点下一个结点的地址，构成一条链表
}SnakeNode,*pSnakeNode;
// 蛇的行走方向
enum DIRECTION{ UP=1,DOWN,LEFT,RIGHT};
//蛇的状态
enum  Status{OK,KILL_BY_SELF,KILL_BY_WALL,ESC};
 
// 蛇本身
typedef struct snake{
	pSnakeNode _pSnake;//蛇头指针
	pSnakeNode _pFood;//食物
	enum DIRECTION _Dir;//蛇行走的方向
	enum Status _Status;//蛇的当前状态
	int _SleepTime;//每走一步停留的时间
}Snake,*pSnake;
 
void Welcome();//我们在游戏开始之前做一个欢迎界面
void InitSnake(pSnake ps){//因为蛇是一条链表，所以在开始的时候我们要初始化它
	pSnakeNode cur = NULL;//这是我们设置的蛇身子结点
	int i = 0;
	cur = malloc(sizeof(SnakeNode));
	memset(cur,0x00,sizeof(SnakeNode));
	cur->next = NULL;
	cur->x = INIT_X;//设置蛇身子第一个人结点的位置
	cur->y = INIT_Y;
	for (i=1;i<=4;i++)//这个循环使用头插的方法最后一次出循环的时候，cur就指向第一个结点，也就是蛇头结点
	{
		ps->_pSnake = malloc(sizeof(SnakeNode));
		ps->_pSnake->next = cur;
		ps->_pSnake->x =INIT_X+i*2;
		ps->_pSnake->y = INIT_Y;
		cur = ps->_pSnake;
	}
	while (cur!=NULL)//按照每一个蛇身子结点里面的x,y坐标打印出整条蛇
	{
		SetPos(cur->x,cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	ps->_Dir = RIGHT;//设置初始蛇的朝向向右
	ps->_SleepTime = 500;
	ps->_Status = OK;//设置蛇的初始状态是OK，不然就没法玩了
}
void CreatFood(pSnake ps){//食物是蛇结构体的其中一种状态，我们把食物拿到单独函数中初始化
	pSnakeNode cur = NULL;
	pSnakeNode food = NULL;//食物也是一个结点，所以用蛇结点的结构体定义
	food = malloc(sizeof(SnakeNode));
again:
	memset(food,0x00,sizeof(SnakeNode));
	do{
		food->x = rand()%56+2;//因为我们横着的墙的最后一个设置在58的位置，一个食物的标致占两位，所以我们%56+2控制食物的x坐标不会越界
	}while(food->x %2 != 0);
	food->y = rand()%25+1;//因为我们竖着的墙的最下的位置设置在26，所以%25+1
	cur = ps->_pSnake;
	while (cur!=NULL)//这个循环判断随机产生的食物有没有和蛇的位置重叠，如果有重叠，那就使用goto语句返回，重新产生一个
	{
		if(cur->x == food->x && cur->y == food->y)
		{
			goto again;
		}
		cur = cur->next;
	}
	ps->_pFood = food;
	SetPos(food->x,food->y);//设置好食物的坐标之后，再在屏幕的相应位置输出
	printf(FOOD);
}
void EatFood(pSnakeNode nNode,pSnake ps){
	pSnakeNode cur = ps->_pSnake;//创建一个结点，当作食物，蛇吃掉之后把它当作结点插入到蛇身子里面
	nNode->next = cur;
	ps->_pSnake = nNode;
	cur = ps->_pSnake;
	while (cur!=NULL)//结点插入之后在把整个链表，也就是蛇打印一遍
	{
		SetPos(cur->x,cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	CreatFood(ps);//食物吃掉之后，在产生一个新食物
}
void NoFood(pSnakeNode nNode,pSnake ps){//如果移动的下一步没有食物，那么就把蛇在新的位置打印一遍
	pSnakeNode cur = ps->_pSnake;
	nNode->next = cur;
	ps->_pSnake = nNode;
	cur = ps->_pSnake;
	while (cur->next->next!=NULL)//因为蛇的长度是一定的，所以在新的位置打印之后，最后一个结点用空格代替，就产生了一条新蛇
	{
		SetPos(cur->x,cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	SetPos(cur->x,cur->y);
	printf(FOOD);
	SetPos(cur->next->x,cur->next->y);//设置好最后一个位置的结点
	printf("  ");//用空格代替，那么在屏幕显示就是蛇向前走了一步
	free(cur->next);
	cur->next = NULL;
}
int NextHasFood(pSnakeNode nNode,pSnake ps){
	return ps->_pFood->x == nNode->x  && ps->_pFood->y == nNode->y;
}
void SnakeMove(pSnake ps){
	pSnakeNode  nNode = malloc(sizeof(SnakeNode));// 定义一个结点，赋给他蛇头结点的值，再根据下一步要走的方向，确定结点真正的值
	memset(nNode,0x00,sizeof(SnakeNode));
	nNode->x = ps->_pSnake->x;
	nNode->y = ps->_pSnake->y;
	switch (ps->_Dir)
	{
	case UP:
		nNode->y-=1;
		break;
	case DOWN:
		nNode->y+=1;
		break;
	case LEFT:
		nNode->x-=2;
		break;
	case RIGHT:
		nNode->x+=2;
		break;
	default:
		break;
	}
	if (NextHasFood(nNode,ps))//判断下一步有没有食物，
	{
		EatFood(nNode,ps);//有的话，就进入吃食物的操作函数
	} 
	else
	{
		NoFood(nNode,ps);//没有的话，就进入没有食物的操作
	}
}
int KillBySelf(pSnake ps){//用遍历判断蛇头是否和蛇身子的结点的坐标重合，重合就是吃到了自己
	pSnakeNode cur= ps->_pSnake->next;
	while (cur!=NULL)
	{
		if (cur->x == ps->_pSnake->x  && cur->y == ps->_pSnake->y)
		{
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}
int KillByWall(pSnake ps){//如果蛇头结点的坐标和墙重合了，那就是撞墙了
	if(ps->_pSnake->x == 0  || ps->_pSnake->x == 58 || ps->_pSnake->y == 0 || ps->_pSnake->y == 26)
		return 1;
	return 0;
}
void SnakeRun(pSnake ps){
	do 
	{
		if(GetAsyncKeyState(VK_UP) && ps->_Dir != DOWN){//判断键盘输入的如果是↑键，且蛇的方向没有向下，那就进入循环，把蛇的方向的状态改成向上
			ps->_Dir = UP;
		}
		if(GetAsyncKeyState(VK_DOWN) && ps->_Dir != UP){//判断键盘输入的如果是↓键，且蛇的方向没有向上，那就进入循环，把蛇的方向的状态改成向下
 
			ps->_Dir = DOWN;
		}
		if(GetAsyncKeyState(VK_LEFT) && ps->_Dir != RIGHT){//判断键盘输入的如果是左键，且蛇的方向没有向右，那就进入循环，把蛇的方向的状态改成向左
 
			ps->_Dir = LEFT;
		}
		if(GetAsyncKeyState(VK_RIGHT) && ps->_Dir != LEFT){//判断键盘输入的如果是右键，且蛇的方向没有向左，那就进入循环，把蛇的方向的状态改成向右
 
			ps->_Dir = RIGHT;
		}
		if(GetAsyncKeyState(VK_ESCAPE)){//如果键盘输入ESC键，那就状态改成退出
			ps->_Status = ESC;
		}
		SnakeMove(ps);//蛇的方向改了之后，那就向当前方向行走一步
		if (KillBySelf(ps))//判断当前是否会被自己咬死
		{
			ps->_Status = KILL_BY_SELF;
			SetPos(30,12);
			printf("自己你都想吃，你咋不上天！\n");
		} 
		if(KillByWall(ps))//判断是否会被墙撞死
		{
			ps->_Status = KILL_BY_WALL;
			SetPos(30,12);
			printf("不是吧！看见墙还往上撞！\n");
		}
		if(ps->_Status == ESC){
			printf("你竟然退出？\n");
		}
		Sleep(ps->_SleepTime);
	} while (ps->_Status == OK);//如果蛇的状态是OK那就一直进入判断，
}
void SnakeStart(pSnake ps){//开始之前的准备工作
	srand(time(NULL));
	system("mode con cols=100 lines=30");
	system("cls");
	DrawMap();//画地图
	InitSnake(ps);//初始化蛇。并画出
	CreatFood(ps);//创建一个食物
}
void Welcome(void){//欢迎界面
	system("mode con cols=100 lines=30");
	system("cls");
	SetPos(38,6);
	printf("welcome come to SnakeGame\n");
	SetPos(38,8);
	printf("↑↓←→control direction\n");
	SetPos(45,10);
	printf("ESC For Exit\n");
	SetPos(42,12);
	printf("宇哥科技倾情奉献\n");
	getchar();
	system("cls");
}
int main(){
	Snake s;
	memset(&s,0x00,sizeof(Snake));
	Welcome();
	SnakeStart(&s);
	SnakeRun(&s);
	return 0;
}