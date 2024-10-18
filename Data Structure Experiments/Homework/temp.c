#include <stdio.h>
#include <string.h>
#include <stdlib.h> // 添加stdlib以使用malloc函数

#define MAX_SIZE 26

// 节点定义
typedef struct TreeNode {
    char val; // 节点的值，存储一个字符
    struct TreeNode *left;  // 指向左子树的指针
    struct TreeNode *right; // 指向右子树的指针
} TreeNode;

// 构造二叉树函数
void buildTree(TreeNode** root, char* inorder, char* postorder, int inStart, int inEnd, int* postIndex) {
    // 如果中序遍历的起始索引大于结束索引，说明当前子树为空，返回 NULL
    if (inStart > inEnd) {
        *root = NULL;
        return;
    }

    // 创建当前根节点，根节点的值是当前后序遍历序列的最后一个节点
    char rootVal = postorder[*postIndex];
    (*postIndex)--;
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    if (*root == NULL) {
        exit(1);
    }
    (*root)->val = rootVal;
    (*root)->left = (*root)->right = NULL;

    // 在中序遍历中找到根节点的位置，以此分割出左子树和右子树
    int rootIndex;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
        if (inorder[rootIndex] == rootVal) {
            break;
        }
    }

    // 递归构造右子树和左子树
    // 注意先构造右子树，因为后序遍历的顺序是左 -> 右 -> 根
    buildTree(&((*root)->right), inorder, postorder, rootIndex + 1, inEnd, postIndex);
    buildTree(&((*root)->left), inorder, postorder, inStart, rootIndex - 1, postIndex);
}

// 前序遍历函数
void preorderTraversal(TreeNode* root) {
    // 如果当前节点为空，直接返回
    if (root == NULL) {
        return;
    }
    // 打印当前节点的值
    printf("%c", root->val);
    // 递归遍历左子树
    preorderTraversal(root->left);
    // 递归遍历右子树
    preorderTraversal(root->right);
}

// 释放二叉树内存函数
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char inorder[MAX_SIZE], postorder[MAX_SIZE];
    // 输入中序遍历和后序遍历序列，以空格分隔
    scanf("%s %s", inorder, postorder);
    

    // 计算遍历序列的长度
    int length = strlen(inorder);
    // 初始化后序遍历序列的索引，指向最后一个元素
    int postIndex = length - 1;

    // 构造二叉树，返回根节点
    TreeNode* root = NULL;
    buildTree(&root, inorder, postorder, 0, length - 1, &postIndex);

    // 前序遍历并打印结果
    preorderTraversal(root);
    printf("\n");

    // 释放分配的内存
    freeTree(root);

    return 0;
}