#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct BSTNode
{
    int val;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *BSTInsert(BSTNode *root, int key)
{
    if (root == NULL) // 如果为空就插入
    {
        BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
        node->left = node->right = NULL;
        node->val = key;
        return node;
    }

    if (key < root->val)
        root->left=BSTInsert(root->left,key);
    else
        root->right=BSTInsert(root->right, key);
    return root;
}

BSTNode *findMin(BSTNode *root)
{
    while(root->left!=NULL)
    {
        root=root->right;
    }
    return root;
}
BSTNode *BSTDelete(BSTNode *root,int key)
{
    if(root==NULL)
        return root;
    // 首先要找到结点
    if(key<root->val)
        root->left=BSTDelete(root->left,key);
    else if(key>root->val)
        root->right=BSTDelete(root->right,key);
    else
    {
        // 找到后开始删除，考虑不同的情况
        if(root->left==NULL) // 只有左子树为空
        {
            BSTNode *temp=root->right;
            free(root);
            return temp;

        }else if(root->right==NULL) // 只有右子树
        {
            BSTNode *temp=root->left;
            free(root);
            return temp;
        }
        // 若有两个结点
        else
        {
            BSTNode *temp=findMin(root->right);// 找到右子树最小值
            root->val=temp->val;
            root->right=BSTDelete(root->right,temp->val);// 然后把问题转化成前面两种情况
        }
    }
    return root;

}
void Inorder(BSTNode *root)
{
    if (root == NULL)
        return;
    Inorder(root->left);
    printf("%d ", root->val);
    Inorder(root->right);
}
int main()
{
    BSTNode *root = NULL;
    root = BSTInsert(root, 2);
    root = BSTInsert(root, 1);
    root = BSTInsert(root, 7);
    root = BSTInsert(root, 8);
    root = BSTInsert(root, 6);
    Inorder(root);
    root=BSTDelete(root,7);
    Inorder(root);
}