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

void destroyNT(void * v1){
	NameTag *nametag = (NameTag*)v1;
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
	int c = 4;
	int e = 5;
	int d = 3;
	int f = 0;
	int g = 9;


	printf("%d %d\n",a,SLInsert(list, (void*)&a));
	printf("%d %d\n",b,SLInsert(list, (void*)&b));
	printf("%d %d\n",c,SLInsert(list, (void*)&c));
	printf("%d %d\n",e,SLInsert(list, (void*)&e));
	printf("%d %d\n",d,SLInsert(list, (void*)&d));
	printf("%d %d\n",f,SLInsert(list, (void*)&f));
	printf("%d %d\n",g,SLInsert(list, (void*)&g));

	testPtr = SLCreateIterator(list);

	// printf("Add something after making the iterator");
	// printf("%d %d\n",g,SLInsert(list, (void*)&g));


	printf("remove item\n");
	SLRemove(list, ((void*)&d));

	int* currlist = (int *)SLGetItem(testPtr);
	while( currlist != NULL){
		printf("Current list item: %d\n",*currlist);
		currlist = (int*)SLNextItem(testPtr);
	}


	// SLRemove(list, ((void*)&e));
	// printf("item just removed!\n");


	// //we just removed something, this is an attempt to print with same iterator
	// int* curr = (int *)SLNextItem(testPtr);
	// while(curr != NULL)
	// {
	// 	printf("current item: %d\n", *curr);
	// 	curr = (int *)SLNextItem(testPtr);
	// }





	// //test NameTag Struct

	// char* nombre = "Michael";
	// char* pat = "Pat Barrett";
	// NameTag *michael = createNT(nombre, 94);
	// NameTag *michaelclone = createNT(nombre, 19);
	// NameTag *patb = createNT(pat, 10);
	// SortedListPtr namelist = SLCreate(compareNameTag, destroyNT);
	// SortedListIteratorPtr nameIT;

	// printf("%s %d\n",michael->name,SLInsert(namelist, (void*)michael));
	// printf("%s %d\n",michaelclone->name,SLInsert(namelist, (void*)michaelclone));
	// printf("%s %d\n",patb->name,SLInsert(namelist, (void*)patb));

	// nameIT = SLCreateIterator(namelist);
	// NameTag* currname = (NameTag *)SLNextItem(nameIT);
	// while( currname != NULL){
	// 		printf("Current list item: %s %d\n",currname->name, currname->id);
	// 		currname = (NameTag*)SLNextItem(nameIT);
	// }

	// return 0;
}










