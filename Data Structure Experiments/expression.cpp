#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int Operator_Priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case 'x':
    case '/':
        return 2;
    }
    return 0;
}
void in_to_pre_expression(string s)
{
    stack<char> s1, s2; // s1运算符
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] >= '0' && s[i] <= '9')
            s2.push(s[i]);
        else
        {
            if (s[i] != '(')
            {
                if (s1.empty() || s[i] == ')' || s1.top() == ')')
                    s1.push(s[i]);
                else if (Operator_Priority(s[i]) >= Operator_Priority(s1.top()))
                {
                    s1.push(s[i]);
                }
                else if (Operator_Priority(s[i]) < Operator_Priority(s1.top()))
                {
                    while (!s1.empty() && Operator_Priority(s[i]) < Operator_Priority(s1.top()))
                    {
                        s2.push(s1.top());
                        s1.pop();
                    }
                    s1.push(s[i]);
                }
            }
            else
            {
                while (s1.top() != ')')
                {
                    s2.push(s1.top());
                    s1.pop();
                }
                s1.pop();
            }
        }
    }
    while (!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
    string res;
    while (!s2.empty())
    {
        res.push_back(s2.top());
        s2.pop();
    }
    //cout<<res.rbegin();
}
void in_to_post_expression(string s)
{
    stack<char> s1, s2; // s1运算符
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            s2.push(s[i]);
        else
        {
            if (s[i] != ')')
            {
                if (s1.empty() || s1.top() == '(' || s[i] == '(')
                    s1.push(s[i]);
                else if (Operator_Priority(s[i]) >= Operator_Priority(s1.top()))
                    s1.push(s[i]);
                else if (Operator_Priority(s[i]) < Operator_Priority(s1.top()))
                {
                    while (!s1.empty() && Operator_Priority(s[i]) < Operator_Priority(s1.top()))
                    {
                        s2.push(s1.top());
                        s1.pop();
                    }
                    s1.push(s[i]);
                }
            }
            else
            {
                while (!s1.empty() && s1.top() != '(')
                {
                    s2.push(s1.top());
                    s1.pop();
                }
                s1.pop();
            }
        }
    }
    while (!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
    while (!s2.empty())
    {
        std::cout << s2.top() << " ";
        s2.pop();
    }
}
int main()
{
    string str;
    cin >> str;
    //in_to_pre_expression(str);
    cout << endl;
    in_to_post_expression(str);
}