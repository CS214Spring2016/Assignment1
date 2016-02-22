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

	//int test
	printf("Regular int test \n");
	SortedListPtr list = SLCreate(compareInteger, destroyFunction);
	SortedListIteratorPtr testPtr;

	int a = 1;
	int b = 29;
	int c = 4;
	int e = 5;
	int d = 3;
	int f = 0;


	printf("%d %d\n",a,SLInsert(list, (void*)&a));
	printf("%d %d\n",b,SLInsert(list, (void*)&b));
	printf("%d %d\n",c,SLInsert(list, (void*)&c));
	printf("%d %d\n",d,SLInsert(list, (void*)&e));
	printf("%d %d\n",e,SLInsert(list, (void*)&d));
	printf("%d %d\n",f,SLInsert(list, (void*)&f));


	testPtr = SLCreateIterator(list);


	int* currlist = (int *)SLGetItem(testPtr);
	while( currlist != NULL){
		printf("Current list item: %d\n",*currlist);
		currlist = (int*)SLNextItem(testPtr);
	}




	//int with removal
	printf("int removal test \n\n");
	SortedListPtr list2 = SLCreate(compareInteger, destroyFunction);
	SortedListIteratorPtr testPtr2;

	int a3 = 1;
	int b3 = 29;
	int c3 = 4;
	int e3 = 5;
	int d3 = 3;
	int f3 = 0;


	printf("%d %d\n",a3,SLInsert(list2, (void*)&a3));
	printf("%d %d\n",b3,SLInsert(list2, (void*)&b3));
	printf("%d %d\n",c3,SLInsert(list2, (void*)&c3));
	printf("%d %d\n",d3,SLInsert(list2, (void*)&e3));
	printf("%d %d\n",e3,SLInsert(list2, (void*)&d3));
	printf("%d %d\n",f3,SLInsert(list2, (void*)&f3));


	testPtr2 = SLCreateIterator(list2);

	//removed the number after iterator created
	SLRemove(list2,(void*)&d3);


	int* currlist2 = (int *)SLGetItem(testPtr2);
	while( currlist2 != NULL){
		printf("Current list item: %d\n",*currlist2);
		currlist2 = (int*)SLNextItem(testPtr2);
	}




	//double test
	printf("double test\n\n");

	SortedListPtr dublist = SLCreate(compareDouble, destroyFunction);
	SortedListIteratorPtr dubPtr;

	double a1 = 11.1;
	double b1 = 29.7;
	double c1 = 77.6;
	double e1 = 8.1;
	double d1 = 3.25;
	double f1 = 0.12;



	printf("%f %d\n",a1,SLInsert(dublist, (void*)&a1));
	printf("%f %d\n",b1,SLInsert(dublist, (void*)&b1));
	printf("%f %d\n",c1,SLInsert(dublist, (void*)&c1));
	printf("%f %d\n",d1,SLInsert(dublist, (void*)&e1));
	printf("%f %d\n",e1,SLInsert(dublist, (void*)&d1));
	printf("%f %d\n",f1,SLInsert(dublist, (void*)&f1));


	dubPtr = SLCreateIterator(dublist);


	double* dubList = (double *)SLGetItem(dubPtr);
	while( dubList != NULL){
		printf("Current list item: %f\n",*dubList);
		dubList = (double*)SLNextItem(dubPtr);
	}


	//string test
	printf("strign test\n\n");
	SortedListPtr strlist = SLCreate(compareString, destroyFunction);
	SortedListIteratorPtr strPtr;

	char* a2 = "ab";
	char* b2 = "cd";
	char* c2 = "ef";
	char* d2 = "zz";
	char* e2 = "yz";
	char* f2 = "qqq";
	char* z2 = "help";

	SLInsert(strlist, (void*)&a2);
	SLInsert(strlist, (void*)&b2);
	SLInsert(strlist, (void*)&c2);
	SLInsert(strlist, (void*)&d2);
	SLInsert(strlist, (void*)&e2);
	SLInsert(strlist, (void*)&f2);
	SLInsert(strlist, (void*)&z2);

	strPtr = SLCreateIterator(strlist);

	char** strThing = (char **)SLGetItem(strPtr);
	while( strThing != NULL){
		printf("Current list item: %s\n",*strThing);
		strThing = (char**)SLNextItem(strPtr);
	}










	//test NameTag Struct
	printf("nametag struct test\n\n");

	char* nombre = "Michael";
	char* pat = "Pat Barrett";
	NameTag *michael = createNT(nombre, 94);
	NameTag *michaelclone = createNT(nombre, 19);
	NameTag *patb = createNT(pat, 10);
	SortedListPtr namelist = SLCreate(compareNameTag, destroyNT);
	SortedListIteratorPtr nameIT;

	printf("%s %d\n",michael->name,SLInsert(namelist, (void*)michael));
	printf("%s %d\n",michaelclone->name,SLInsert(namelist, (void*)michaelclone));
	printf("%s %d\n",patb->name,SLInsert(namelist, (void*)patb));

	nameIT = SLCreateIterator(namelist);
	NameTag* currname = (NameTag *)SLNextItem(nameIT);
	while( currname != NULL){
			printf("Current list item: %s %d\n",currname->name, currname->id);
			currname = (NameTag*)SLNextItem(nameIT);
	}

	// return 0;
}










