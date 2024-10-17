/*
Dhruv Patel 
Lab 4
5/13/2023
Program Description: a List ADT using a linked list with a sentinel/dummy pointer to the head.
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "list.h"
# define NODE struct node 
NODE{
	void* data;
	NODE* next;
	NODE* prev;
};

LIST{
	int count;
	NODE *head;
	int (*compare)();
};

//O(1)
//creates and initializes a LIST with a dummy node pointixng at the start
LIST *createList(int (*compare)()){
    LIST *lp;
	lp=malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count=0;
	NODE *dummy = malloc(sizeof(NODE));
	assert(dummy != NULL);
	dummy->next=dummy;
	dummy->prev=dummy;
	lp->head=dummy;
	lp->compare=compare;
	return lp;
}

//O(n)
//destroys the LIST
void destroyList(LIST *lp){
    NODE* headPt = lp->head;
	assert(headPt != NULL && lp != NULL);
	NODE *nextNode=headPt->next;
	while(headPt!=nextNode){
		NODE *temp=nextNode;
		nextNode=nextNode->next;
		free(temp);
	}
	free(headPt);
	free(lp);
}

//O(1)
//returns count (number of items in list)
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count;
}

//O(1)
//add item at start of list 
void addFirst(LIST *lp, void *item){
    NODE *headPt = lp->head;
	assert(headPt != NULL&&lp!=NULL);
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->prev=headPt;
	temp->next=headPt->next;
    temp->data=item;
	headPt->next->prev=temp;
	headPt->next=temp;
	lp->count++;
}

//O(1)
//add item at the end of the list 
void addLast(LIST *lp, void *item){
    NODE *headPt = lp->head;
	assert(headPt != NULL && lp != NULL);
	NODE *temp;
	temp=malloc(sizeof(NODE));
	assert(temp!=NULL);
	temp->data=item;
	temp->prev=headPt->prev;
	temp->next=headPt;
	headPt->prev->next=temp;
	headPt->prev=temp;
	lp->count++;
}


//O(1)
//remove the first item
void *removeFirst(LIST *lp) {
    NODE *headPt = lp->head;
	assert(headPt != NULL && lp != NULL && lp->count>0);
	NODE *temp=headPt->next;
	headPt->next=temp->next;
	temp->next->prev=headPt;
	lp->count--;
	void* dataTemp=temp->data;
	free(temp);
	return dataTemp;
}

//O(1)
//remove the last item
void *removeLast(LIST *lp) {
    NODE *headPt = lp->head;
	assert(headPt != NULL && lp != NULL && lp->count>0);
    NODE *temp = malloc(sizeof(NODE));
	temp=headPt->prev;
	headPt->prev=temp->prev;
	temp->prev->next=headPt;
	lp->count--;
	void* dataTemp=temp->data;
	free(temp);
	return dataTemp;
}

//O(1)
//returns the first item in list
void *getFirst(LIST *lp) {
	assert(lp != NULL && lp->count>0);
	return lp->head->next->data;
}

//O(1)
//returns the last item in list
void *getLast(LIST *lp) {
	assert(lp != NULL && lp->count>0);
	return lp->head->prev->data;
}

//O(n)
//finds an item and removes it
void removeItem(LIST *lp, void *item) {
    NODE *headPt = lp->head;
	assert(headPt != NULL && lp != NULL && lp->compare!=NULL);
	if(lp->count>0) {
		NODE *nextNode=headPt->next;
		while(nextNode!=headPt){
			if((lp->compare)(nextNode->data,item)==0) {
				nextNode->prev->next=nextNode->next;
				nextNode->next->prev=nextNode->prev;
				free(nextNode);
				return;
			}
			nextNode=nextNode->next;
		}
	}
}

//O(n)
//finds and returns an item
void *findItem(LIST *lp, void *item) {
	NODE *headPt = lp->head;
	assert(headPt != NULL && lp != NULL && lp->compare!=NULL);
	if(lp->count>0) {
		NODE *nextNode=headPt->next;
		while(nextNode!=headPt){
			if((lp->compare)(nextNode->data,item)==0)
				return nextNode->data;
			nextNode=nextNode->next;
		}
	}
	return NULL;
}

//O(n)
//creates array of all items
void *getItems(LIST *lp) {
    int i;
    assert(lp != NULL);
    void **elts = malloc(sizeof(void*)*lp->count);
    NODE *p = lp->head->next;
    for(i=0; i<lp->count; i++) {
        elts[i] = p->data;
        p = p->next;
    }
    return elts;
}
