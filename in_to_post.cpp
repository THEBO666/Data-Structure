#include <iostream>
#include <stdio.h>
#include <stack>
#include <string>

using namespace std;

int getPriority(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return 0;
}
string in_to_post(string &str)
{
    string res;
    stack<char> op;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            res.push_back(str[i]);
        else
        {
            // 先处理括号问题，再处理符号
            if (op.empty() || str[i] == '('||op.top()=='(')
            {
                op.push(str[i]);
            }
            else if (str[i] == ')')
            {
                while (!op.empty() && op.top() != '(')
                {
                    res.push_back(op.top());
                    op.pop();
                }
                op.pop();
            }
            else if (getPriority(str[i]) > getPriority(op.top()))
            {
                op.push(str[i]);
            }
            else if (getPriority(str[i]) <= getPriority(op.top()))
            {
                while (!op.empty() && getPriority(str[i]) <= getPriority(op.top()))
                {
                    res.push_back(op.top());
                    op.pop();
                }
                op.push(str[i]);
            }
            
        }
    }
    while (!op.empty())
    {
        res.push_back(op.top());
        op.pop();
    }
    return res;
}
int main()
{
    string str;
    cin >> str;
    cout << in_to_post(str);
}