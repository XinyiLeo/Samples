#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX(a,b) (a>=b ? a:b)

void main()
{
	int n, i, r, *a, max, *b, c[200] = { 0 }, cnt = 0;
	printf("Please input the size of an array: ");
	scanf("%d", &n);
	a = (int*)malloc(n*sizeof(int));
	b = (int*)malloc(n*sizeof(int));
	printf("Please input the array: ");
	fflush(stdin);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}

	for (i = 0; i < n; i++)
	{
		b[i] = a[i];
	}
	for (i = 1; i < n; i++)
	{
		b[i] = MAX(b[i - 1], b[i]);
	}
	max = b[n - 1];
	srand(time(NULL));
	r = rand() % max;
	printf("The random number is: %d\n", r);
	for (i = 0; i < n; i++)
	{
		if (a[i]>r)
		{
		c[cnt] = a[i];
		cnt++;
		}
	}
	
	printf("In the array");
	for (i = 0; i < cnt; i++)
	{
		printf(",%d", c[i]);
	}
	
	printf("is larger than the random number.");

	free(a);
}