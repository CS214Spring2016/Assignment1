#include "sorted-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//for all comparators:
//-1 if first is smaller than second, 0 if equal, 1 if first is bigger
int compareInteger(void *v1, void *v2)
{
	int n1 = *(int*)v1;
	int n2 = *(int*)v2;

	if(n1 == n2)
	{
		return 0;
	}
	else
	{
		return((n1>n2) ? 1:-1);
	}
}

int compareDouble(void *v1, void *v2)
{
	double n1 = *(double*)v1;
	double n2 = *(double*)v2;

	if(n1 == n2)
	{
		return 0;
	}
	else
	{
		return((n1>n2) ? 1:-1);
	}
}

int compareString(void *v1, void *v2)
{
	char *n1 = v1;
	char *n2 = v2;

	return strcmp(n1,n2);
}


int main(int argc, char **argv)
{
	printf("test\n");
	return 0;
}