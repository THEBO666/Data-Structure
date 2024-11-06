#include <iostream>
#include <string>
#include <stack>

/*
* 四则运算计算器
* 这里使用的思路类似于前中后缀表达式（波兰式、逆波兰式）
* 正常输入为中缀
*/
typedef struct TreeNode{
    char val;
    Node *left;
    Node *right;
    TreeNode(char c):val(c),left(nullptr),right(nullptr){}
}Node;
Node *CreateExpressionTree(std::string &str)
{
    
}
int main()
{



    return 0;
}