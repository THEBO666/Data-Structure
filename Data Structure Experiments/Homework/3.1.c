#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct BinarySearchTreeNode
{
    int val;
    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
} Node;

bool verifyBST(int *post, int start, int end)
{
    if (start >= end)
    {
        return true;
    }
    int root = post[end];
    int i = 0;
    while (i < end && post[i] < root)
    {
        i++;
    }

    int m = i;
    while (i < end)
    {
        if (post[i] < root)
            return false;
        i++;
    }

    bool left = verifyBST(post, start, m - 1);
    bool right = verifyBST(post, m, end - 1);

    return left && right;
}
int main()
{
    int a[100];
    memset(a, 0, sizeof(a));
    int i = 0;
    while (scanf("%d", &a[i++]) != EOF)
    {
        if (getchar() != ' ')
            break;
    }
    if (verifyBST(a, 0, i - 1))
        printf("true\n");
    else
        printf("false\n");
    return 0;
}