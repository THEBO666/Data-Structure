#include<iostream>
#include<stdio.h>
using namespace std;

typedef struct LTree
{
    int data; // 改为 int
    struct LTree *lchild;
    struct LTree *rchild;
} LTree, *Tree;

void push(Tree &T, int a)
{
    if (T == NULL)
    {
		throw 1;
        /*T = new LTree;
        T->data = a;
        T->lchild = NULL;
        T->rchild = NULL;*/
    }
    else
    {
        if (a < T->data)
        {
            push(T->lchild, a);
        }
        else if (a > T->data)
        {
            push(T->rchild, a);
        }
    }
}

void first(Tree &T)
{
    if (T == NULL)
    {
        return;
    }
    cout << T->data << " ";
    first(T->lchild);
    first(T->rchild);
}

int main()
{
    Tree T = NULL; // 初始化为NULL
    for (int i = 0; i < 4; i++)
    {
        int a;
        cin >> a;
        push(T, a);
    }
    first(T);
}
