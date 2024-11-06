#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int cmp(const void *a, const void *b)    
{
    return *(int*)a - *(int*)b;
}



int main()
{
	int a[30] = {0};
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	int sum=0;
	for(int i = 0 ;i<n-1;i++)
	{
		qsort(a+i,n-i,sizeof(int),cmp);
		a[i+1]+=a[i];
		sum+=a[i+1];
	}
	qsort(a, n, sizeof(int), cmp);
	printf("%d\n",sum);
	return 0;
}
