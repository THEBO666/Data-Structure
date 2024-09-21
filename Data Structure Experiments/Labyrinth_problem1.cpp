#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int maze[6][6] =
    {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}

};

struct Point{
    int x;
    int y;
    Point(){}
};

bool FindPath(stack<Point> &path)
{
    
}
int main()
{
    stack<Point> path;
    FindPath(path);
    while (!path.empty())
    {
        cout<<path.top().x<<" "<<path.top().y<<endl;
    }
    
    return 0;
}