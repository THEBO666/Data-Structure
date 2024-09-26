#include <iostream>
#include "LinkQueue.hpp"
#include <cstdio>

int main()
{
    LinkQueue<int> q;
    std::cout<<"这里为链式存储实现队列, 请输入:";
    while (true)
    {
        int x;
        scanf("%d", &x);
        q.push(x);
        if (getchar() != ' ') break;
    }
    std::cout << "Queue的size为: " << q.size() << std::endl;
    std::cout << "front: " << q.front() << std::endl;
    std::cout << "back: " << q.back() << std::endl;
    std::cout<<"Queue出队顺序为:";
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }

    return 0;
}