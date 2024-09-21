#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} Node;

Node *createNode(int x)
{
    Node *newnode=(Node*)malloc(sizeof(Node));
    newnode->val=x;
    newnode->next=NULL; 
    return newnode;
}

Node *mergeLists(Node *l1,Node *l2)
{
    if(l1==NULL) return l2;
    if(l2==NULL) return l1;
    Node *res=createNode(0);
    Node *cur=res;
    while(l1!=NULL&&l2!=NULL)
    {
        if(l1->val<=l2->val)
        {
            Node *temp=createNode(l1->val);
            cur->next=temp;
            cur=cur->next;
            l1=l1->next;
        }
        else
        {
            Node *temp=createNode(l2->val);
            cur->next=temp;
            cur=cur->next;
            l2=l2->next;
        }
    }
    if(l1!=NULL)
    {
        while(l1)
        {
            Node *temp=createNode(l1->val);
            cur->next=temp;
            cur=cur->next;
            l1=l1->next;
        }
    }
    if(l2)
    {
        while(l2)
        {
            Node *temp=createNode(l2->val);
            cur->next=temp;
            cur=cur->next;
            l2=l2->next;
        }
    }
    cur=res->next;
    return res->next;
}
int main()
{
    Node *l1=createNode(0),*l2=createNode(0);
    int temp;
    Node *cur=l1;
    while (scanf("%d",&temp))
    {
        Node *node=createNode(temp);
        cur->next=node;
        cur=cur->next;
        if(getchar()!=' ') break;
    }
    cur=l2;
    while(scanf("%d",&temp))
    {
        Node *node=createNode(temp);
        cur->next=node;
        cur=cur->next;
        if(getchar()!=' ') break;
    }
    Node *sortList=mergeLists(l1->next,l2->next);
    while(sortList)
    {
        printf("%d ",sortList->val);
        sortList=sortList->next;
    }
    return 0;
}