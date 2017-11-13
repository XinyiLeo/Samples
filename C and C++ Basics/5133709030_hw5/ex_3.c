#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void main()
{
	char str[200] = { '*' }, c[200] = { '*' };
	int i, j, cnt = 0, ct = 0, cnnt = 0;
	printf("Input a sentence: ");
	gets(str);
	printf("Input a string: ");
	gets(c);
	
	for (i = 0; i < 200; i++)
	{
		if ((int)(str[i]) != 0)
		{
			cnt++;
		}
	}
	for (i = 0; i < 200; i++)
	{
		if ((int)(c[i]) != 0)
		{
			ct++;
		}
	}


	
	for (i = 0; i < cnt - ct + 1; i++)
	{
		for (j = 0; j < ct; j++)
		{
			if ((int)(str[i + j]) != (int)(c[j]))
			{
				break;
			}
			if (j == ct - 1)
			{
				cnnt++;
			}
		}
	}
	printf("The string '%s' occurs %d times", c, cnnt);
}