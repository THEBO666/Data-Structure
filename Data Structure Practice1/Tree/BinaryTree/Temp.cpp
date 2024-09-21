#include <iostream>
#include <vector>
#include <unordered_map>

struct Node
{
    int data;
    Node *left;
    Node *right;
};

// 创建一个新的节点
Node *createNode(int id)
{
    Node *newnode = new Node;
    newnode->data = id;
    newnode->left = newnode->right = nullptr;
    return newnode;
}

// 前序遍历
void Preorder(Node *root)
{
    if (root == nullptr)
        return;
    std::cout << " " << root->data;
    Preorder(root->left);
    Preorder(root->right);
}

// 中序遍历
void Inorder(Node *root)
{
    if (root == nullptr)
        return;
    Inorder(root->left);
    std::cout << " " << root->data;
    Inorder(root->right);
}

// 后序遍历
void Postorder(Node *root)
{
    if (root == nullptr)
        return;
    Postorder(root->left);
    Postorder(root->right);
    std::cout << " " << root->data;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Node *nodes[30];
    for(int i=0;i<n;i++)
        nodes[i]=createNode(i);
    int id, l, r;
    Node *root=nodes[0];
    for (int i = 0; i < n; i++)
    {
        std::cin >> id >> l >> r;
        if (l != -1)
        {
            nodes[id]->left = nodes[l]; // 连接左孩子
        }
        if (r != -1)
        {
            nodes[id]->right = nodes[r]; // 连接右孩子
        }
    }

    // 前序遍历输出
    std::cout << "Preorder" << std::endl;
    Preorder(root);
    std::cout << std::endl;

    // 中序遍历输出
    std::cout << "Inorder" << std::endl;
    Inorder(root);
    std::cout << std::endl;

    // 后序遍历输出
    std::cout << "Postorder" << std::endl;
    Postorder(root);
    std::cout << std::endl;

    return 0;
}
