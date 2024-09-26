#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
	int data;
	struct queue* next;
}queue;

void initqueue(queue** f, queue** r)
{
	queue* t = (queue*)malloc(sizeof(queue));
	t->next = NULL;
	t->data=0;
	*f = t;
	*r = t;
}

int pankong(queue* f, queue* r)
{
	return (f == r);
}

void Push(queue** r, int x)
{
	queue* t = (queue*)malloc(sizeof(queue));
	queue* T = *r;
	t->data = x;
	t->next = NULL;
	T->next = t;
	*r = t;
}

void Pop(queue** f, queue** r, int* y)
{
	queue* t = *f;
	*y = t->data;
	*f = t->next;
}

int main()
{
	queue* front = NULL;
	queue* rear = NULL;
	initqueue(&front, &rear);
	Push(&rear, 30);
	Push(&rear, 20);
	Push(&rear, 10);
	int y = 0;
	while (!pankong(front, rear))
	{
		Pop(&front, &rear, &y);
		printf("%d\n", y);
	}
	return 0;
}
