#include <iostream>
#include <stack>
#include <string>

int getPriority(char ch)
{
    switch (ch)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}
std::string infixTopostfix(std::string &str)
{
    std::string res;
    std::stack<char> st;
    for (auto &x : str)
    {
        if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')')
        {
            if (st.empty() || x == '(')
                st.push(x);
            else
            {
                if (x == ')')
                {
                    while (st.top() != '(')
                    {
                        res.push_back(st.top());
                        st.pop();
                    }
                    st.pop();
                }
                else
                {
                    if (getPriority(st.top()) < getPriority(x))
                    {
                        st.push(x);
                    }
                    else
                    {
                        res.push_back(st.top());
                        st.pop();
                        st.push(x);
                    }
                }
            }
        }
        else
        {
            res.push_back(x);
        }
    }
    if (!st.empty())
    {
        while (!st.empty())
        {
            res.push_back(st.top());
            st.pop();
        }
    }
    return res;
}

int main()
{
    std::string str;
    std::cin >> str;
    str.pop_back();
    std::cout << infixTopostfix(str) << std::endl;
    return 0;
}