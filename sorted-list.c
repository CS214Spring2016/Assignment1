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
		item->viewers=0;
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
	listItem *swap;
	temp = (listItem*)malloc(sizeof(listItem));

	if(temp == NULL){
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	temp->data = newObj;
	temp->next = NULL;
	
	if(list->head == NULL)
	{
		printf("first item\n");
		list->head = temp;

	}
	else{

		while(iPtr->current->next != NULL){
			int compcurr = list->compareF(iPtr->current->data, temp->data);
			int compnext = list->compareF(iPtr->current->next->data, temp->data);
			if(compcurr==0){
				printf("already here\n");

				return 0;
			}
			else if(compcurr == -1 && compnext == 1){//found the right place
				printf("Put in middle\n");
				swap = iPtr->current->next;//save the next one
				iPtr->current->next = temp;//put it in the right place
				iPtr->current = iPtr->current->next;//iterate
				iPtr->current->next = swap; //place the saved one
				return 1;
			}
			else
				iPtr->current = iPtr->current->next;
		}
		int compcurr = list->compareF(iPtr->current->data, temp->data);
		if(compcurr == -1){
			printf("put at end\n");
			iPtr->current->next = temp;//put it in the right place
			iPtr->current = iPtr->current->next;//iterate
			return 1;
		}
		else{
			printf("put at beginning\n");
			swap = list->head;
			list->head = temp;
			iPtr->current =  list->head;
			iPtr->current->next = swap;

			return 1;

		}
	}


	return 1;
}

int SLRemove(SortedListPtr list, void *newObj)
{
	return 0;
}

void *SLNextItem(SortedListIteratorPtr iter)
{
	listItem* temp = iter->current;
	if(temp == NULL)
		return NULL;
	--iter->current->viewers;
	iter->current=iter->current->next;
	++iter->current->viewers;
	return temp->data;
}
void * SLGetItem( SortedListIteratorPtr iter ){
	listItem* temp = iter->current;
	if(temp == NULL)
		return NULL;
	return temp->data;

}



void SLDestroyIterator(SortedListIteratorPtr iter) 
{
	//return 0;
}

