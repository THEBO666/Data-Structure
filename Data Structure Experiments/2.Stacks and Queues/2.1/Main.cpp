#include <iostream>
#include "SeqStack.hpp"
#include <stack>
#include <cstdio>

int main()
{
    SeqStack<int> st;
    std::cout<<"这里为顺序存储实现栈, 请输入:";
    while(1)
    {
        int x;
        scanf("%d",&x);
        st.push(x);
        if(getchar()!=' ') break;
    }
    std::cout << "Stack的size为: " << st.size() << std::endl;
    std::cout << "top: " << st.top() << std::endl;
    std::cout<<"Stack的出栈顺序为: ";
    while (!st.empty())
    {
        std::cout<<st.top()<<" ";
        st.pop();
    }
}