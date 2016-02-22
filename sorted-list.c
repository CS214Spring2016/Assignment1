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
		if(sPtr->current != NULL)
		{
			sPtr->current->viewers++;
		}
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
			int compcurr = list->compareF(temp->data,iPtr->current->data);
			int compnext = list->compareF(temp->data, iPtr->current->next->data );
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
				//SLDestroyIterator(iPtr);
				return 1;
			}
			else
				iPtr->current = iPtr->current->next;
		}
		int compcurr = list->compareF(temp->data, iPtr->current->data);
		if(compcurr == -1){
			printf("put at end\n");
			iPtr->current->next = temp;//put it in the right place
			iPtr->current = iPtr->current->next;//iterate
			//SLDestroyIterator(iPtr);
			return 1;
		}
		else{
			printf("put at beginning\n");
			swap = list->head;
			list->head = temp;
			iPtr->current =  list->head;
			iPtr->current->next = swap;
			//SLDestroyIterator(iPtr);

			return 1;

		}
	}


	return 1;
}

int SLRemove(SortedListPtr list, void *newObj)
{

	SortedListIteratorPtr ptr = SLCreateIterator(list);
	if(ptr == NULL)
	{
		return 0;
	}

	listItem* cur;
	listItem* prev;


	//checking at head
	int compcur = list->compareF(newObj,list->head->data);
	if(compcur == 0)
	{
		//move head
		list->head = list->head->next;
		//if been viewed once, free
		if(ptr->current->viewers==1)
		{
			freeItem(ptr->current);
		}
		SLDestroyIterator(ptr);
		return 1;
	}

	cur = ptr->current->next;
	prev = ptr->current;

	while(ptr->current != NULL && prev != NULL)
	{
		compcur = list->compareF(newObj, SLNextItem(ptr));
		if(compcur == 0)
		{
			prev->next = cur->next;
			if(cur->viewers == 1)
			{
				freeItem(cur);
			}
			SLDestroyIterator(ptr);
			return 1;
		}

		prev = cur;
		cur = cur->next;


	}
	SLDestroyIterator(ptr);
	printf("we should not have gotten here");
	return 0;





}

void *SLNextItem(SortedListIteratorPtr iter)
{
	listItem* temp = iter->current->next;

	if(iter->current->viewers == 0)
	{
		freeItem(iter->current);
	}
	else
	{
		//decrement view count
		iter->current->viewers--;
	}

	iter->current = temp;

	if(iter->current == NULL)
	{
		return NULL;
	}
	else
	{
		//increment viewed count, return data
		iter->current->viewers++;
		return iter->current->data;
	}

}
void * SLGetItem( SortedListIteratorPtr iter ){
	//check for null and return item currently pointed at
	listItem* temp = iter->current;
	if(temp == NULL)
		return NULL;
	return temp->data;

}



void SLDestroyIterator(SortedListIteratorPtr iter) 
{
	//check at current node
	if(iter->current != NULL)
	{
		//if not viewed more than once, free current node
		if(iter->current->viewers <= 0)
		{
			freeItem(iter->current);
		}
		else
		{
			iter->current->viewers--;
		}
	}

	//remove iterator
	free(iter);
}

