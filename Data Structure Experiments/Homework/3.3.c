#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct BinaryTreeNode
{
    char val;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} Node;

void PreOrder(Node *root)
{
    if (root == NULL)
        return;
    printf("%c", root->val);
    PreOrder(root->left);
    PreOrder(root->right);
}

void createTree(Node **root, char *in, char *post, int inStart, int inEnd, int *postIndex)
{
    if (inStart > inEnd)
    {
        *root = NULL;
        return;
    }
    char rootVal = post[*postIndex];
    (*postIndex)--;
    *root = (Node *)malloc(sizeof(Node));
    (*root)->val = rootVal;
    (*root)->left = (*root)->right = NULL;
    int rootIndex = 0;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++)
    {
        if (in[rootIndex] == rootVal)
            break;
    }
    createTree(&((*root)->right), in, post, rootIndex + 1, inEnd, postIndex);
    createTree(&((*root)->left), in, post, inStart, rootIndex - 1, postIndex);
}
int main()
{
    char in[30], post[30];
    memset(in, 0, sizeof(in));
    memset(post, 0, sizeof(post));
    scanf("%s", in);
    scanf("%s", post);
    Node *root = NULL;
    int size = strlen(in) - 1;
    createTree(&root, in, post, 0, size, &size);
    PreOrder(root);
    return 0;
}