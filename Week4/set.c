/*
Dhruv Patel 
Lab 4
5/13/2023
Program Description: a Set ADT using a hash table with 'chaining' which implements linked lists.
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"
# include "list.h" 
# define NODE struct node 
NODE{
	void* data;
	NODE* next;
	NODE* prev;
};
LIST
{
	int count; 
	struct node *head; 
    int (*compare) ();
};

SET 
{
	int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
    LIST **data; 
};
//O(n)
//creates a set with length maxElts with each element having the capability to be a linked list 
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{    
	int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count=0;
    sp->length=maxElts/20;
    sp->data=malloc(sizeof(LIST*) * sp->length);
    sp->compare=compare;
    sp->hash=hash;
    for(i=0;i<sp->length;i++){
        sp->data[i]=createList(compare);
    }
    assert(sp->data !=  NULL);
    return sp;
}

//O(n)
//uses a for loop to delete every list in the set 
void destroySet(SET *sp)
{
	int i;
    for(i=0;i<sp->length;i++){
        destroyList(sp->data[i]);
    }
    free(sp);
}

//O(1)
//returns the number of elements in the set provided
int numElements(SET *sp)
{
	assert(sp != NULL);
    return sp->count;
}

//O(1)
//adds an element
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    unsigned index = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->data[index],elt) == NULL)
    {
        addFirst(sp->data[index] , elt);
        sp->count++;
    }
}

//O(n)
//removes an element from the set provided
void removeElement(SET *sp, void *elt)
{
	    assert(sp != NULL && elt != NULL);
    	unsigned index = (*sp->hash)(elt)%sp->length;
    	if(findItem(sp->data[index],elt) != NULL)
    	{
        	removeItem(sp->data[index], elt);
        	sp->count--;
    	}
}



//O(n)
//returns an element if it is in the set
void *findElement(SET *sp, void *elt)
{
	    assert(sp != NULL && elt != NULL);
    	unsigned index = (*sp->hash)(elt) % sp->length;
    	return findItem(sp->data[index], elt); 
}


//O(n)
//returns the data of the set provided
void *getElements(SET *sp)
{
	assert(sp != NULL);
    NODE *temp;
    void **elts = malloc(sizeof(void*)*sp->count);
    int i, j;
    j = 0; 
    for(i = 0; i < sp->length; i++)
    {
        int num = numItems(sp->data[i]);
        if(num != 0)
        {
            temp = sp->data[i]->head->next;
            while(temp != sp->data[i]->head){
                elts[j] = temp->data;
                num++;
                j++;
                temp = temp->next;
            }
        }
    }
    return elts; 
}