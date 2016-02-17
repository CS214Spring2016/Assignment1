#include "sorted-list.h"
#include <stdio.h>
#include <stdlib.h>


//creates a linked list item, with data and a pointer to next
listItem* makeItem(void* data, listItem* next)
{
	listItem* item = (listItem*)malloc(sizeof(listItem));

	//malloc fail check
	if(item != NULL)
	{
		item->data = data;
		item->next = next;
		return item;
	}
	else
	{
		return NULL;
	}
}


//destroys the listitem passed
void freeItem(listItem* item)
{
	free(item);
}


SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
	SortedListPtr list = (SortedListPtr)malloc(sizeof(struct SortedList));
	//is malloc successful
	if(list != NULL)
	{
		list->head = NULL;
		list->compareF = cf;
		list->destroyF = df;
		return list;
	}
	else
	{
		return NULL;
	}
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
	SortedListIteratorPtr sPtr = (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));

	if(sPtr == NULL)
		return NULL;
	else
	{
		sPtr->current = list->head;
		return sPtr;
	}
}


void SLDestroy(SortedListPtr list)
{
	free(list);
}

int SLInsert(SortedListPtr list, void *newObj)
{
	SortedListIteratorPtr iPtr = SLCreateIterator(list);

	if(iPtr == NULL)
	{
		return 0;
	}

	listItem *temp;
	temp = (listItem*)malloc(sizeof(listItem));
	temp->data = newObj;
	temp->next = NULL;
	
	if(list->head == NULL)
	{
		list->head = temp;
	}
	else{//TODO add into the right place
		//put it at the end for now
		printf("something is in the list, ill just throw the new thing on the end for now\n");
		while(iPtr->current->next != NULL){
			iPtr->current = iPtr->current->next;
		}
		iPtr->current->next=temp;

	}

	return 0;
}

int SLRemove(SortedListPtr list, void *newObj)
{
	return 0;
}

void *SLNextItem(SortedListIteratorPtr iter)
{
	return iter->current->next;
}



void SLDestroyIterator(SortedListIteratorPtr iter) 
{
	//return 0;
}

