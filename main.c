#include "sorted-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* lets test for structs too
*  This is a name tag, it holds a Name and userID
*/
typedef struct NameTag_{
	char *name;
	int id;
}NameTag;
int compareInteger(void *v1, void *v2);

NameTag *createNT(char * name, int idnumber){

	//error checking
		if(name == 0 | strlen(name) <= 0) return 0;

		//allocate memory

		NameTag *nt = (NameTag*)malloc(sizeof(NameTag));
		if(nt == NULL)
		{
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		nt->name=strdup(name);
		if(nt->name==NULL){//this is a secret malloc, free later
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		nt->id=idnumber;
		return nt;
}

void destroyNT(NameTag * nametag){
	free(nametag->name);
	free(nametag);
}
int compareNameTag(void *v1, void *v2){
	NameTag *n1 = (NameTag*)v1;
	NameTag *n2 = (NameTag*)v2;
	int compareNum = strcmp(n1->name,n2->name);
	if(compareNum==0)
		return compareInteger((void*)&n1->id,(void*)&n2->id);
	else if(compareNum<0)
		return -1;
	else if(compareNum>0)
		return 1;
	else return 0;

}
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
	int compareNum = strcmp(n1,n2);
	if(compareNum==0)
		return 0;
	else if(compareNum<0)
		return -1;
	else
		return 1;
}

void destroyFunction(void *v)
{
	free(v);
}


int main(int argc, char **argv)
{
	SortedListPtr list = SLCreate(compareInteger, destroyFunction);
	SortedListIteratorPtr testPtr;

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 9;

	SLInsert(list, (void*)&a);
	SLInsert(list, (void*)&b);
	SLInsert(list, (void*)&c);
	SLInsert(list, (void*)&d);

	testPtr = SLCreateIterator(list);

	while(testPtr->current != NULL)
	{
		int* x = (int*)(testPtr->current->data);
		if(x == NULL)
		{
			printf("X IS NULL\n");
			break;
		}
		printf("Current list item: %d\n", *x);
		testPtr->current = testPtr->current->next;//iterate
	}

	//test NameTag Struct

	return 0;
}










