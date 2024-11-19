#include <iostream>
#include <string>
#include <stack>
#include "Expression.h" //表达式树
/*
 * 四则运算计算器
 * 这里使用的思路类似于前中后缀表达式（波兰式、逆波兰式）
 * 正常输入为中缀
 */
typedef struct TreeNode
{
    char op; // 表达式树的元素可能是元素也肯是运算符
    double val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() {}
    TreeNode(char c) : op(c), left(nullptr), right(nullptr) {}
    TreeNode(double v) : val(v), left(nullptr), right(nullptr) {}
} Node;

double GetNum(const std::string &s, int &i)
{
    double res = 0; // 初始化 res

    while (isNum(s[i]))
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    if (s[i] == '.')
    {
        double k = 10.0, y = 0;
        i++;
        while (isNum(s[i]))
        {
            y += ((s[i] - '0') / k);
            i++;
            k *= 10;
        }
        res += y;
    }
    return res;
}
void CreateExpTree(TreeNode *&root, const std::string &s, int &i)
{

    while (i < s.size() && (s[i] == ' ' || s[i] == '.'))
        i++;
    if (i >= s.size())
        return;
    if (isNum(s[i]))
    {
        root = new Node(GetNum(s, i));
        return; // 不需要再递增 i
    }
    else
    {
        root = new Node(s[i]);
        i += 2;                          // 跳过运算符与空格
        CreateExpTree(root->left, s, i); // 递归构造
        CreateExpTree(root->right, s, i);
    }
}
void print(Node *p)
{
    // 表达式树的左右子树都为空肯定是数值
    if (!(p->left) && !(p->right))
        std::cout << p->val << " ";
    else
        std::cout << p->op << " ";
}
void PreOrder(Node *root)
{
    if (root == nullptr)
        return;
    print(root);
    PreOrder(root->left);
    PreOrder(root->right);
}

double CalculateTree(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    // 其实就是后序遍历
    if (!(root->left) && !(root->right))
        return root->val;
    double l = CalculateTree(root->left);
    double r = CalculateTree(root->right);
    switch (root->op)
    {
        case '+':
            return l + r;
        case '-':
            return l - r;
        case '*':
        case 'x':
            return l * r;
        case '/':
            if (r != 0)
                return l / r;
            else
            {
                std::cerr << "Error: Can't divide zero!!!" << std::endl;
                return 0;
            }
        default:
            std::cerr << "Error: Unknown operator" << std::endl;
            return 0;
    }
}
void InOrder(Node *root)
{
    if (root == nullptr)
        return;
    InOrder(root->left);
    print(root);
    InOrder(root->right);
}

void PostOrder(Node *root)
{
    if (root == nullptr)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    print(root);
}
int main()
{

    std::string str;

    std::getline(std::cin, str);
    std::string pre, post;
    pre = in_to_pre_expression(str);
    post = in_to_post_expression(str);
    std::cout << "前缀表达式：" << pre << std::endl;
    std::cout << "后缀表达式：" << post << std::endl;
    TreeNode *root;
    int i = 0;
    CreateExpTree(root, pre, i);
    std::cout << "表达式树前序遍历: ";
    PreOrder(root);
    std::cout << std::endl;
    std::cout << "表达式树中序遍历: ";
    InOrder(root);
    std::cout << std::endl;
    std::cout << "表达式树后序遍历: ";
    PostOrder(root);
    std::cout << std::endl;
    std::cout << "表达式树求值: " << CalculateTree(root) << std::endl;
    return 0;
}