#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>

typedef struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char a) : val(a), left(nullptr), right(nullptr) {}
} Node;

/*
 * 链式结构建立二叉树
 * 输入int
 * 采用非递归形式解决
 */

Node *CreateTree(std::vector<int> order)
{
    char ch;
    if (order.empty())
        return nullptr;
    std::stack<Node *> nodeStack; // 存储结点信息
    Node *root = new Node(order[0]);
    nodeStack.push(root);
    bool flag = true;
    for (int i = 1; i < order.size(); i++)
    {
        if (order[i] != -1)
        {
            Node *newnode = new Node(order[i]);
            if (flag)
            {
                nodeStack.top()->left = newnode;
            }
            else
            {
                nodeStack.top()->right = newnode;
                nodeStack.pop(); // 左右插入完成直接pop
            }
            nodeStack.push(newnode);
            flag = true;
        }
        else // 空结点
        {
            if (flag)
            {
                flag = false; // 填充右子树
            }
            else
            {
                // 右子树为空说明当前结点已插入完成
                nodeStack.pop();
            }
        }
    }
    return root;
}

void PreOrder(Node *root)
{
    if (root==nullptr)
        return ;
    std::cout<<root->val<<" ";
    PreOrder(root->left);
    PreOrder(root->right);
}
void InOrder(Node *root)
{
    if (root==nullptr)
        return ;
    InOrder(root->left);
    std::cout<<root->val<<" ";
    InOrder(root->right);
}
void PostOrder(Node *root)
{
    if(root==nullptr)
        return ;
    PostOrder(root->left);
    PostOrder(root->right);
    std::cout<<root->val<<" ";
}
void LevelOrder(Node *root)
{    
    if(root==nullptr)
        return ;
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        std::cout<<q.front()->val<<" ";
        if(q.front()->left)
        {
            q.push(q.front()->left);
        }
        if(q.front()->right)
        {
            q.push(q.front()->right);
        }
        q.pop();
    }
}

int TreeSize(Node *root) //树的大小吧（结点）
{
    return root==nullptr?0:TreeSize(root->left)+
                           TreeSize(root->right)+1;
}

// 树的高度
int TreeHeight(Node *root)
{
    if(root==nullptr)
        return 0;
    int left=TreeHeight(root->left);
    int right=TreeHeight(root->right);
    return left>right?left+1:right+1;
}

bool DestroyTree(Node* root){//@@@
    if(root == nullptr){
        return false;
    }
    DestroyTree(root->left);
    DestroyTree(root->right);
    free(root);//@@@
    root=nullptr;
    return true;
}

