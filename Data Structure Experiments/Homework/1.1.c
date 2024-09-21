#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} Node;

int main()
{
    int n, temp;
    int size = 0;
    Node *head = (Node *)malloc(sizeof(Node));
    head->val = 0;
    head->next = NULL;
    Node *cur = head;
    scanf("%d", &n);
    while (scanf("%d", &temp) != EOF)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->val = temp;
        cur->next = newnode;
        cur = cur->next;
        size++;
    }
    if (n > 0 && n <= size)
    {
        n = size - n + 1;
        while (n--)
        {
            head = head->next;
        }
        printf("%d", head->val);
        }
    else
    {
        printf("Not Found");
    }
    return 0;
}