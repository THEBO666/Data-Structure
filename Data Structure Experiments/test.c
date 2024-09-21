#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int data;
    struct Stack* next;
}Stack;

void InitStack(Stack* s)
{
    s->next=NULL;
}
Stack* createStack()
{
    Stack* newStack=(Stack*)malloc(sizeof(Stack));
    newStack->next=NULL;
    return newStack;
}

int panduan(Stack* s)
{
    return s==NULL;
}

void Push(Stack** s,int x)
{
    Stack* t=createStack();
    t->data=x;
    t->next=*s;
    *s=t;
}

void Pop(Stack** s,int* y)
{
    if(!panduan(*s))
    {
        Stack *t=*s;
        *y=t->data;
        *s=t->next;
        free(t);
    }
}

int main()
{
    Stack* s=NULL;
    int b;
    Push(&s,10);
    Push(&s,20);
    Push(&s,30);
    while(!panduan(s))
    {
        Pop(&s,&b);
        printf("%d\n",b);
    }
    
    return 0;
}

