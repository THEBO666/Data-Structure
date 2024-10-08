#pragma once

#include <iostream>
#include <cassert>
#include <cstdio>
#include <string>

template <class T>
struct BTNode
{

    T data;
    BTNode *left = NULL;
    BTNode *right = NULL;
    BTNode() {}
    BTNode(T d) : data(d), left(nullptr), right(nullptr)
    {
    }
};

template <class T>
BTNode<T> *BuyNode(T x)
{
    BTNode<T> *newnode = new BTNode<T>;
    assert(newnode);
    if (newnode == NULL)
    {
        perror("malloc fail");
        return nullptr;
    }
    newnode->data = x;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

template <class T>
void PreOrder(BTNode<T> *root)
{
    if (root == NULL)
        return;
    std::cout << root->data << " ";

    PreOrder(root->left);
    PreOrder(root->right);
}

template <class T>
void InOrder(BTNode<T> *root)
{
    if (root == NULL)
        return;
    InOrder(root->left);

    std::cout << root->data << " ";
    InOrder(root->right);
}

template <class T>
void PostOrder(BTNode<T> *root)
{
    if (root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);

    std::cout << root->data << " ";
}

template <class T>
int TreeSize(BTNode<T> *root)
{
    // if(root==nullptr)
    //     return ;
    // ++(*size);
    // TreeSize(root->left,size);
    // TreeSize(root->right,size);
    return root == nullptr ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}

template <class T>
int TreeHeight(BTNode<T> *root)
{
    if (root == nullptr)
        return 0;
    int left = TreeHeight(root->left);
    int right = TreeHeight(root->right);

    return left > right ? left + 1 : right + 1;
}
template <class T>
int TreeKLevel(BTNode<T> *root,int k)
{
    if(root==nullptr)
        return 0;
    if(k==1)
        return 1;
    // 第k层结点个数为k-1的左右子树结点的和
    return TreeKLevel(root->left,k-1)+TreeKLevel(root->right,k-1);
}
