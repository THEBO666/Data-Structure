#include <iostream>
#include <malloc.h>
using namespace std;
#define MAXSIZE 100
typedef struct
{
    int x;
    int y;
}Coordinate;//迷宫
typedef struct
{
    Coordinate position;
    int direction;
}CoordinateDir;
typedef struct
{
    CoordinateDir *top;
    CoordinateDir *base;
    int stacksize;
}SqStack;
void InitStack(SqStack &S)
{//初始化
    S.base = new CoordinateDir[MAXSIZE];
    if(!S.base){
        cout<<"存储分配错误"<<endl;
    }
    S.top = S.base;
    S.stacksize = MAXSIZE;
}
bool isEmpty(SqStack &S)
{
    if(S.base == S.top)
    {
        return true;
    }
    return false;
}
void Push(SqStack &S, CoordinateDir &e)
{//插入栈顶元素
    if(S.top-S.base == S.stacksize){
        cout<<"栈满"<<endl;
    }
    *S.top++ = e;
}
void Pop(SqStack &S, CoordinateDir &e)
{//删除
    if(S.base == S.top){
        cout<<"空栈"<<endl;
    }
    e = *--S.top;
}
Coordinate R_position;
Coordinate C_position;
bool isPass(int **a, Coordinate &Coo)//判断是否是墙
{
    if(a[Coo.x][Coo.y] == 0)
    {
        return false;
    }
    return true;
}
void signRoad(int **a, Coordinate &Coo)//设置走过的路为2
{
    a[Coo.x][Coo.y] = 2;
}
void SetWall(int **a, Coordinate &Coo)//设置为墙
{
    a[Coo.x][Coo.y] = 1;
}
CoordinateDir isGo(int **a, CoordinateDir &Dir)//判断是否走过是否为死路
{
    switch(Dir.direction)
    {
        case 1: Dir.position.x++;//向下走
                if((a[Dir.position.x][Dir.position.y] != 2) && (a[Dir.position.x][Dir.position.y] != 1))
                    break;//继续寻找
                Dir.position.x--;
        case 2: Dir.direction = 2;
                Dir.position.y++;//向右走
                if((a[Dir.position.x][Dir.position.y] != 2) && (a[Dir.position.x][Dir.position.y] != 1))
                    break;//继续寻找
                Dir.position.y--;
        case 3: Dir.direction = 3;
                Dir.position.x--;//向上走
                if((a[Dir.position.x][Dir.position.y] != 2) && (a[Dir.position.x][Dir.position.y] != 1))
                    break;//继续寻找
                Dir.position.x++;
        case 4: Dir.direction = 4;
                Dir.position.y--;//向左走 最后一个方向 若为2 说明这个点为死路，则将此点设置为墙
                if((a[Dir.position.x][Dir.position.y] == 2) && (a[Dir.position.x][Dir.position.y] == 1))
                {
                    SetWall(a, Dir.position);//设置为墙
                    Dir.position.y++;
                }
                break;
    }
    return Dir;
}

void create_Maze(int **&a)//若不传引用就应该传***a
{
    int n, m, load;
    cout<<"请输入迷宫的长和宽：";cin>>n>>m;
    cout<<"请输入迷宫（通路由0表示，障碍由1表示）："<<endl;
     a= new int *[50];

    //a = (int **)malloc(sizeof(int *) *n);
    for(int i = 1; i <= n; i++)
    {a[i] = new int[50];

        //a[i] = (int *)malloc(sizeof(int) *m);
        for(int j = 1; j <= m; j++)
        {
            cin>>load;
            a[i][j] = load;
        }
    }
    cout<<"请输入入口坐标： "; cin>>R_position.x>>R_position.y;
    cout<<"请输入出口坐标： "; cin>>C_position.x>>C_position.y;
    cout<<"迷宫创建成功!"<<endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}
void go_Maze(SqStack &S, int **a)
{
    CoordinateDir Dir;
    Dir.position.x = R_position.x;
    Dir.position.y = R_position.y;

    do
    {
        if(isPass(a, Dir.position) == false)//若不是障碍
        {
            Dir.direction = 1;//默认向下找
            Push(S, Dir);//走过的点放进栈
            signRoad(a, Dir.position);//标记此路已走过
            if(Dir.position.x == C_position.x && Dir.position.y == C_position.y)//判断是否为迷宫出口
            {
                break;
            }
            Dir = isGo(a, Dir);//寻找是否为死路
        }
        else//如果是墙
        {
            if(!isEmpty(S))
            {
                Pop(S, Dir);//返回上一条路
                while(Dir.direction == 4 && !isEmpty(S))
                {
                    SetWall(a, Dir.position);
                    Pop(S, Dir);
                }
                if(Dir.direction < 4)
                {
                    Dir.direction++;//这个路还有其他方向没有走过
                    Push(S, Dir);//这个点入栈
                    Dir = isGo(a, Dir);
                }
            }
        }
        if(Dir.direction == 4 && isEmpty(S))
        {
            cout<<"迷宫没有出路！"<<endl;
            break;
        }
    }while(true);
}
void showPath(int **&a, SqStack &S)
{
    SqStack s;
    InitStack(s);
    CoordinateDir Dir;
    while(!isEmpty(S))
    {
        Pop(S, Dir);
        Push(s, Dir);
    }
    while(!isEmpty(s))
    {
        Pop(s, Dir);
        cout<<"(" <<Dir.position.x<<", "<<Dir.position.y<<")";
    }
}
int main()
{
    SqStack S;
    InitStack(S);
    int **a = NULL;
    create_Maze(a);
    go_Maze(S, a);
    showPath(a, S);
    return 0;
}
/*
1 1 1 0 1
1 1 0 0 1
1 1 0 1 1
1 0 0 1 1
1 0 1 1 1

1 1 1 0 1
1 1 0 0 1
1 1 1 1 1
1 1 1 1 0
1 1 1 1 1

1 1 1 1 1 1 1
1 1 1 0 0 1 1
1 1 0 0 1 1 1
1 1 0 1 1 1 1
1 0 0 1 1 1 1
1 1 0 0 1 1 1
1 1 1 1 1 1 1


1 1 1 1 1 1 1 1 1 1
1 0 0 1 0 0 0 1 0 1
1 0 0 1 0 0 0 1 0 1
1 0 0 0 0 1 1 0 0 1
1 0 1 1 1 0 0 0 0 1
1 0 0 0 1 0 0 0 0 1
1 0 1 0 0 0 1 0 0 1
1 0 1 1 1 0 1 1 0 1
1 1 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1
*/

