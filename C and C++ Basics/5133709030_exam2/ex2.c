#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>



int main()
{
	FILE *fd, *fp;
	fd = fopen("d.txt", "r");
	fp = fopen("details2.txt", "w");
	int  i,j,t,k,f;
	char str[150], c[4] = { "com" }, string[3][150];
	fgets(str, 150, fd);
	
		for (i = 0; i < 200; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if ((int)(str[i + j]) != (int)(c[j]))
				{
					break;
				}
				if (j = 3)
				{
					
					str[k][150]=
				}
			}
		}
	
	while
	
	
	
	fclose(fd);
	fclose(fp);
}

