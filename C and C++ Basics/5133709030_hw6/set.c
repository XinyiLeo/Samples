#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void newSet(uset *set, int type)
{
	set->elem = malloc(INITSETSIZE*type);
	set->card = 0;
	set->type = type;
}

void deletSet(uset *set)
{
	free(set->elem);
	set->card = 0;
}

void addElem(void *elem, uset *set)
{
	int i;
	if (set->type = CHAR)
	{
		for (i = 0; i < set->card; i++)
		{
			if (((char*)set->elem)[i] == *((char*)elem))
			{
				return;
			}
		}
		if (set->card % INITSETSIZE == 0)
		{
			realloc(set->elem, set->card*CHAR + INITSETSIZE);
		}
		((char*)set->elem)[set->card++] = *((char*)elem);
		return;
	}
	
	if (set->type = INT)
	{
		for (i = 0; i < set->card; i++)
		{
			if (((int*)set->elem)[i] == *((int*)elem))
			{
				return;
			}
		}
		if (set->card % INITSETSIZE == 0)
		{
			realloc(set->elem, set->card*INT + INITSETSIZE);
		}
		((int*)set->elem)[set->card++] = *((int*)elem);
		return;
	}
	
	if (set->type = DOUBLE)
	{
		for (i = 0; i < set->card; i++)
		{
			if (((double*)set->elem)[i] == *((double*)elem))
			{
				return;
			}
		}
		if (set->card % INITSETSIZE == 0)
		{
			realloc(set->elem, set->card*DOUBLE + INITSETSIZE);
		}
		((double*)set->elem)[set->card++] = *((double*)elem);
		return;
	}
}

void remElem(void *elem, uset *set)
{
	int j, k; void* new;
	if (set->type = CHAR)
	{
		for (j = 0; j < (set->card); j++)
		{
			if (((char*)set->elem)[j] != *((char*)elem))
			{
				continue;
			}
			else if (((char*)set->elem)[j] = *((char*)elem))
			{
				k = j;
			}
			if (j = set->card-1)
			{
				return;
			}
		}
		
		new = malloc(set->card*CHAR);
		for (j = 0; j <= k-1; j++)
		{
			((char*)new)[j] = ((char*)set->elem)[j];
		}
		for (j = k; j < set->card-1; j++)
		{
			((char*)new)[j] = ((char*)set->elem)[j+1];
		}
		for (j = 0; j <= set->card; j++)
		{
			((char*)set->elem)[j] = ((char*)new)[j];
		}
		if (set->card % INITSETSIZE == 0 && set->card != 0)
		{
			realloc(set->elem, set->card*CHAR - INITSETSIZE);
		}
    }

	if (set->type = DOUBLE)
	{
		for (j = 0; j < (set->card); j++)
		{
			if (((double*)set->elem)[j] != *((double*)elem))
			{
				continue;
			}
			else if (((double*)set->elem)[j] = *((double*)elem))
			{
				k = j;
			}
			if (j = set->card - 1)
			{
				return;
			}
		}

		new = malloc(set->card*DOUBLE);
		for (j = 0; j <= k - 1; j++)
		{
			((double*)new)[j] = ((double*)set->elem)[j];
		}
		for (j = k; j < set->card - 1; j++)
		{
			((double*)new)[j] = ((double*)set->elem)[j + 1];
		}
		for (j = 0; j <= set->card; j++)
		{
			((double*)set->elem)[j] = ((double*)new)[j];
		}
		if (set->card % INITSETSIZE == 0 && set->card != 0)
		{
			realloc(set->elem, set->card*DOUBLE - INITSETSIZE);
		}
	}

	if (set->type = INT)
	{
		for (j = 0; j < (set->card); j++)
		{
			if (((int*)set->elem)[j] != *((int*)elem))
			{
				continue;
			}
			else if (((int*)set->elem)[j] = *((int*)elem))
			{
				k = j;
			}
			if (j = set->card - 1)
			{
				return;
			}
		}

		new = malloc(set->card*INT);
		for (j = 0; j <= k - 1; j++)
		{
			((int*)new)[j] = ((int*)set->elem)[j];
		}
		for (j = k; j < set->card - 1; j++)
		{
			((int*)new)[j] = ((int*)set->elem)[j + 1];
		}
		for (j = 0; j <= set->card; j++)
		{
			((int*)set->elem)[j] = ((int*)new)[j];
		}
		if (set->card % INITSETSIZE == 0 && set->card != 0)
		{
			realloc(set->elem, set->card*INT - INITSETSIZE);
		}
	}
	free(new);
}