#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct Stack
{
	char data[MAX];
	int top;
} Stack;

void initStack(Stack *s)
{
	s->top = -1;
}

int panduan(Stack *s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void Push(Stack *s, char c)
{
	if (s->top < MAX - 1)
	{
		s->data[++s->top] = c;
	}
}

void Pop(Stack *s)
{
	if (!panduan(s))
	{
		s->top--;
		
	}
}

char Top(Stack *s)
{
	if(!panduan(s))
	{
		return s->data[s->top];
	}
}
void check(char *a)
{
	Stack s;
	initStack(&s);
	int i = 0;
	for (i = 0; i < strlen(a); i++)
	{
		char c = a[i];
		if (c == '(' || c == '[' || c == '{')
		{
			Push(&s, c);
		}
		else
		{
			if (c == ')' || c == ']' || c == '}')
			{
				if (panduan(&s))
				{
					printf("N%d\n", i);
					return;
				}
				char ch = Top(&s);
				if ((c == ')' && ch != '(') || (c == ']' && ch != '[') || (c == '}' && ch != '{'))
				{
					printf("N%d\n", i);
					return;
				}
				else
				{
					Pop(&s);
				}
			}
		}
	}
	if (!panduan(&s))
	{
		printf("N%d\n", strlen(a));
	}
	else
	{
		printf("Y\n");
		return;
	}
}
int main()
{
	char c[MAX];
	scanf("%s", c);
	check(c);
	return 0;
}
