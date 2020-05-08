#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 200
#define THRESHOLD 7
#define MAXSVR 5
#define MINSVR 3
typedef struct 
{
    int id;
    int wtime;
}CustType;
static CustType Cqueue[MAXSIZE];
static int Cfront=0;
static int Crear=-1;
static int Cnum=0;
int Winnum=MINSVR;
void updateCustqueue();
void enCustqueue(CustType c);
CustType deCustqueue();
int getCustnum();
int isFull();
int isEmpty();
void arriveCust();
int service();
int main()
{
    int clock,simulationtime;
    scanf("%d",&simulationtime);
    for(clock=1;;clock++)
    {
        updateCustqueue();
        if(clock<=simulationtime)
            arriveCust();
        if(service()==0&&clock>simulationtime)
            break;
    }
    return 0;
}
void arriveCust()
{
    int i,n;
    static int count=1;
    CustType c;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        c.id=count++;c.wtime=0;
        enCustqueue(c);
    }
    while((getCustnum()/Winnum)>=THRESHOLD&&Winnum<MAXSVR)
        Winnum++;
}
int service()
{
    int i;
    CustType c;
    for(i=0;i<Winnum;i++)
    {
        if(isEmpty())return 0;
        else{
            c=deCustqueue();
            printf("%d : %d\n",c.id,c.wtime);
        }
    }
    if((getCustnum()/Winnum)<THRESHOLD&&Winnum>MINSVR)
        Winnum--;
    return 1;
}
void enCustqueue(CustType c)
{
    if(isFull())
    {
        printf("Full queue!");
        exit(-1);
    }
    else
    {
        Crear =(Crear+1)%MAXSIZE;
        Cqueue[Crear]=c;
        Cnum++;
    } 
}
CustType deCustqueue()
{
    CustType c;
    if(isEmpty())
    {
        printf("Empty queue!");exit(-1);
    }
    else
    {
        c=Cqueue[Cfront];
        Cnum--;
        Cfront=(Cfront+1)%MAXSIZE;
        return c;
    }
}
void updateCustqueue()
{
    int i;
    for(i=0;i<Cnum;i++)
        Cqueue[(Cfront+i)%MAXSIZE].wtime++;
}
int isEmpty(){return Cnum==0;}
int isFull(){return Cnum==MAXSIZE;}
int getCustnum(){return Cnum;}