#include<stdio.h>
#include<stdlib.h>

struct stacknode
{
    char data;
    struct stacknode *next;
};

struct stacklist
{
    struct stacknode *top;
    int count;
};

void push(struct stacklist *s, char c)
{
    struct stacknode *p = (struct stacknode*)malloc(sizeof(struct stacknode));
    p->data = c;
    p->next = s->top;
    s->top = p;
    s->count++;
}

void pop(struct stacklist *s)
{
    struct stacknode *p = s->top;
    s->top = p->next;
    s->count--;
    free(p);
}

char topp(struct stacklist *s)
{
    return s->top->data;
}

int main()
{
    char c[50];
    int j = 0;
    struct stacklist *s = (struct stacklist*)malloc(sizeof(struct stacklist));
    s->count = 0;
    while (scanf("%c", &c[j]))
    {
        if (c[j] == '(')
        {
            push(s, c[j]);
        }
        else if (c[j] == '{')
        {
            push(s, c[j]);
        }
        else if (c[j] == '[')
        {
            push(s, c[j]);
        }
        else if (c[j] == ')')
        {
            if (topp(s) == '(')
            {
                pop(s);
            }
            else
            {
                printf("N");
                printf("%d", j);
                return 0;
            }
        }
        else if (c[j] == '}')
        {
            if (topp(s) == '{')
            {
                pop(s);
            }
            else
            {
                printf("N");
                printf("%d", j);
                return 0;
            }
        }
        else if (c[j] == ']')
        {
            if (topp(s) == '[')
            {
                pop(s);
            }
            else
            {
                printf("N");
                printf("%d", j);
                return 0;
            }
        }
        else
        {

        }
        j++;
        if (getchar() == '\n')
        {
            break;
        }
    }
    free(s);
    return 0;
}