#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

int Operator_Priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case 'x':
    case '/':
    case '*':
        return 2;
    }
    return 0;
}
bool isNum(char ch)
{
    return '0' <= ch && ch <= '9';
}
std::string in_to_post_expression(const std::string &s)
{
    std::stack<char> op;
    std::string res;
    for (int i = 0; i < s.size();)
    {
        if (s[i] == ' ') // 跳过空格
        {
            i++;
            continue;
        }
        else if (isNum(s[i]))
        {
            // 将数字写入结果字符串
            while (i < s.size() && (isNum(s[i]) || s[i] == '.'))
            {
                res.push_back(s[i++]);
            }
            res.push_back(' ');
        }
        else
        {
            if (s[i] == '(')
            {
                op.push(s[i]);
            }
            else if (s[i] == ')')
            {
                while (!op.empty() && op.top() != '(')
                {
                    res.push_back(op.top());
                    res.push_back(' ');
                    op.pop();
                }
                op.pop(); // 弹出 '('
            }
            else
            {
                // 对于运算符
                while (!op.empty() && Operator_Priority(s[i]) <= Operator_Priority(op.top()))
                {
                    res.push_back(op.top());
                    res.push_back(' ');
                    op.pop();
                }
                op.push(s[i]);
            }
            i++;
        }
    }
    // 将栈中剩余的运算符全部弹出
    while (!op.empty())
    {
        res.push_back(op.top());
        res.push_back(' ');
        op.pop();
    }
    return res;
}

std::string in_to_pre_expression(const std::string &s)
{
    std::stack<char> op;
    std::string res;
    for (int i = s.size() - 1; i >= 0;)
    {
        if (s[i] == ' ')
        {
            i--;
            continue;
        }
        else if (isNum(s[i]))
        {
            while (i < s.size() && (isNum(s[i]) || s[i] == '.'))
            {
                res.push_back(s[i--]);
            }
            res.push_back(' ');
        }
        else
        {
            if (s[i] == ')')
            {
                op.push(s[i]);
            }
            else if (s[i] == '(')
            {
                while (!op.empty() && op.top() != ')')
                {
                    res.push_back(op.top());
                    res.push_back(' ');
                    op.pop();
                }
                op.pop(); // 弹出(
            }
            else
            {
                while (!op.empty() && Operator_Priority(s[i]) < Operator_Priority(op.top()))
                {
                    res.push_back(op.top());
                    op.pop();
                    res.push_back(' ');
                }
                op.push(s[i]);
            }
            i--;
        }
    }
    while (!op.empty()) 
    {
        res.push_back(op.top());
        res.push_back(' ');
        op.pop();
    }
    
    std::reverse(res.begin(), res.end());
    return res;
}