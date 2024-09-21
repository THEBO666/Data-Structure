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
    BTNode(T d, BTNode *l, BTNode *r) : data(d), left(l), right(r)
    {
    }
};

template <class T>
BTNode<T> *BuyNode(T x)
{
    BTNode<T> *newnode = new BTNode<T>;
    assert(newnode);
    if(newnode==NULL)
    {
        perror("malloc fail");
        return ;
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
    if(root == NULL)
        return ;
    InOrder(root->left);
    
    std::cout<<root->data<<" ";
    InOrder(root->right);
}

template <class T>
void PostOrder(BTNode<T> *root)
{
    if(root == NULL)
        return ;
    PostOrder(root->left);
    PostOrder(root->right);
    
    std::cout<<root->data<<" ";
}

