#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main()
{
	int r, round = 0, *a, i, *b;
	printf("Please input the round number:\n");
	scanf("%d", &r);
	*a = malloc(r*(sizeof(int)));
	*b = malloc(r*(sizeof(int)));
	for (i = 0; i < r; i++)
	{
		printf("Round %d", round);
		srand(time(NULL));
		*a = rand() % 3;
		printf("User(scissors(1),rock(2),paper(3)):\n");
		scanf("%d", &b);
		printf("Computer:%d", *(a + i));
		if (*(a + i) == 2 && *(b + i) == 1)
			printf("Computer wins!\n");
		else if
			(*(a + i) == 3 && *(b + i) == 2)
			printf("Computer wins!\n");
		else if
			(*(a + i) == 3 && *(b + i) == 2)
			printf("Computer wins!\n");
		else
			printf("User wins!\n");
	}
	free(a);
	free(b);
}