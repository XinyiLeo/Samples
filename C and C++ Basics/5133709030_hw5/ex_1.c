#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>



int main()
{
	FILE *fd, *fp;
	fd = fopen("input.txt", "r");
	fp = fopen("output.txt", "w");
	int n, A[10][10], B[10][10], C[10][10] = { 0 }, D[10][10] = { 0 }, E[10][10] = { 0 }, F[10][10] = { 0 }, G[10][10] = { 0 }, i, j,k,m=1;
	char str[20];
	fgets(str,20,fd);
	fseek(fd, 0, SEEK_SET);
	for (i = 0; i < 20; i++)
	{
		if ((int)(str[i] == 32))
		{
			m++;
		}
	}


    for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
			fscanf(fd, "%d", &A[i][j]);
	}


	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
			fscanf(fd, "%d", &B[i][j]);
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
			if (C[i][j] >= 0 && C[i][j] < 10)
				fprintf(fp, "%d    ", C[i][j]);
			if (C[i][j] >= 10 && C[i][j]  < 100)
				fprintf(fp, "%d   ", C[i][j]);
			if (C[i][j] >= 100 && C[i][j]  < 1000)
				fprintf(fp, "%d  ", C[i][j]);
			if (C[i][j] >= 1000 && C[i][j]  < 10000)
				fprintf(fp, "%d ", C[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			for (k = 0; k < m; k++)
			{
				D[i][j] += A[i][k] * B[k][j];
			}
			if (D[i][j] >= 0 && D[i][j] < 10)
				fprintf(fp, "%d    ", D[i][j]);
			if (D[i][j] >= 10 && D[i][j]  < 100)
				fprintf(fp, "%d   ", D[i][j]);
			if (D[i][j] >= 100 && D[i][j]  < 1000)
				fprintf(fp, "%d  ", D[i][j]);
			if (D[i][j] >= 1000 && D[i][j]  < 10000)
				fprintf(fp, "%d ", D[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			E[i][j] = A[j][i];
		}
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			F[i][j] = B[j][i];
		}
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			for (k = 0; k < m; k++)
			{
				G[i][j] += E[i][k] * F[k][j];
			}
			if (G[i][j] >= 0 && G[i][j] < 10)
				fprintf(fp, "%d    ", G[i][j]);
			if (G[i][j] >= 10 && G[i][j]  < 100)
				fprintf(fp, "%d   ", G[i][j]);
			if (G[i][j] >= 100 && G[i][j]  < 1000)
				fprintf(fp, "%d  ", G[i][j]);
			if (G[i][j] >= 1000 && G[i][j]  < 10000)
				fprintf(fp, "%d ", G[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fd);
	fclose(fp);
} 

