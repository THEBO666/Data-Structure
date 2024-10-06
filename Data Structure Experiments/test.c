#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100

typedef struct {
	char ch;
	int flag;
}StackElement;

StackElement stack[MAX_SIZE];
int top = -1;

void push(char ch,int flag)
{
	if (top < MAX_SIZE - 1)
	{
		stack[++top].ch = ch;
		stack[top].flag = flag;
	}
}

StackElement pop()
{
	if (top > -1)
		return(stack[top--]);
	else
		return (StackElement) {'\0',-1 };
}

int isMatchingPair(char open, char close)
{
	return(open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}

int main()
{
	int a = 0;
	char expression[MAX_SIZE];
	scanf("%s", expression);
	for (int i = 0; i < strlen(expression); i++)
	{
		char ch = expression[i];
		if (ch == '(' || ch == '[' || ch == '{')
		{
			push(ch, i);
		}
		else if (ch == ')' || ch == ']' || ch == '}')
		{
			if ((top == -1) || !isMatchingPair(pop().ch, ch))
			{
				printf("N");
				printf("%d\n", i);
				a = 1;
				break;
			}
		}
	}
	if (top == -1 && a==0)
		printf("Y\n");
	else if(top!=-1&&a==0)
		printf("N%d", stack[top].flag);
}