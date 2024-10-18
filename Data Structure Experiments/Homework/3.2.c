#include <stdio.h>
#include <stdlib.h>

int cmp(void *e1, void *e2)
{
	if (*(int *)e1 - *(int *)e2 > 0)
		return 1;
	else if (*(int *)e1 - *(int *)e2 < 0)
		return -1;
	else
		return 0;
}

int main()
{
	int a[20];
	int i = 0;
	while (1)
	{
		scanf("%d", a[i++]);
		if (getchar() != ' ')
			break;
	}
	qsort(a, i, sizeof(a), cmp);

	return 0;
}
