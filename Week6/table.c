/*
 * File:        table.c
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the public and private function and type
 *              definitions for a set abstract data type for generic
 *              pointer types.  A set is an unordered collection of unique
 *              elements.
 *
 *              This implementation uses a hash table to store the
 *              elements, with linear probing to resolve collisions.
 *              Insertion, deletion, and membership checks are all average
 *              case constant time.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"

# define EMPTY   0
# define FILLED  1
# define DELETED 2

struct set {
    int count;                  /* number of elements in array */
    int length;                 /* length of allocated array   */
    void **data;                /* array of allocated elements */
    char *flags;                /* state of each slot in array */
    int (*compare)();		/* comparison function         */
    unsigned (*hash)();		/* hash function               */
};


/*
 * Function:    search
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Return the location of ELT in the set pointed to by SP.  If
 *		the element is present, then *FOUND is true.  If not
 *		present, then *FOUND is false.  The element is first hashed
 *		to its correct location.  Linear probing is used to examine
 *		subsequent locations.
 */

static int search(SET *sp, void *elt, bool *found)
{
    int available, i, locn, start;


    available = -1;
    start = (*sp->hash)(elt) % sp->length;

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {
            *found = false;
            return available != -1 ? available : locn;

        } else if (sp->flags[locn] == DELETED) {
            if (available == -1)
		available = locn;

        } else if ((*sp->compare)(sp->data[locn], elt) == 0) {
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}
/*
Description: This function takes a set (sp), an array of elements (elts), and the indices of the low and high boundaries of the array. 
It partitions the array around a pivot element by rearranging the elements such that all elements smaller than or equal to the pivot are 
placed before it, and all elements greater than the pivot are placed after it.
Big O Runtime: O(n), where n represents the number of elements in the given partition. 
*/
static int partition(SET* sp, void** elts, int low, int high){
    assert(sp);
    void* pivot = elts[high];//start at beginning index to partition
    int smaller = low - 1;  //index of smaller element
    for (int i = low; i <= high - 1; i++){
        if ((*sp->compare)(elts[i], pivot) <= 0){//if the element in the array is less than or equal to the pivot, swap
            smaller++;//increment index of smaller element
            void* temp = elts[smaller];
            elts[smaller] = elts[i];
            elts[i] = temp;
        }   
    }
    void* swap = elts[smaller + 1];//swap the next element from smaller and return that index
    elts[smaller + 1] = elts[high];
    elts[high] = swap;
    return smaller + 1;
    }
/*
Description: Uses Partition to repeatedly quicksort the array recursively.
Complexity: O(n) 
*/
static void quicksort(SET* sp, void** elts, int low, int high){
    assert(sp);
    if(low < high){//when the "magic walls" collide, stop partitioning
        int partitionIndex = partition(sp, elts, low, high);
        quicksort(sp, elts, low, partitionIndex - 1);//since array is now divided into two (one is all lower than partitionIndex and other is higher than partitionIndex), recursively partition those those two parts
        quicksort(sp, elts, partitionIndex + 1, high);
    }
    return;
}
/*
 * Function:    createSet
 *
 * Complexity:  O(m)
 *
 * Description: Return a pointer to a new set with a maximum capacity of
 *		MAXELTS.
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp;


    assert(compare != NULL && hash != NULL);

    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;

    return sp;
}


/*
 * Function:    destroySet
 *
 * Complexity:  O(m)
 *
 * Description: Deallocate memory associated with the set pointed to by SP.
 *		The elements themselves are not deallocated since we did not
 *		allocate them in the first place.  That's the rule: if you
 *		didn't allocate it, then you don't deallocate it.
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);

    free(sp->flags);
    free(sp->data);
    free(sp);
}


/*
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Return the number of elements in the set pointed to by SP.
 */

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}


/*
 * Function:    addElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Add ELT to the set pointed to by SP.
 */

void addElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (!found) {
	assert(sp->count < sp->length);

	sp->data[locn] = elt;
	sp->flags[locn] = FILLED;
	sp->count ++;
    }
}


/*
 * Function:    removeElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Remove ELT from the set pointed to by SP.  A element is
 *		deleted by changing the state of its slot.
 */

void removeElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (found) {
	sp->flags[locn] = DELETED;
	sp->count --;
    }
}


/*
 * Function:    findElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: If ELT is present in the set pointed to by SP then return
 *		it, otherwise return NULL.
 */

void *findElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);

    locn = search(sp, elt, &found);
    return found ? sp->data[locn] : NULL;
}


/*
 * Function:	getElements
 *
 * Complexity:	O(m)
 *
 * Description:	Allocate and return an array of elements in the set pointed
 *		to by SP.
 */

void *getElements(SET *sp)
{
    int i, j;
    void **elts;


    assert(sp != NULL);

    elts = malloc(sizeof(void *) * sp->count);
    assert(elts != NULL);

    for (i = 0, j = 0; i < sp->length; i ++)
	if (sp->flags[i] == FILLED)
	    elts[j ++] = sp->data[i];
    quicksort(sp, elts, 0, sp->count - 1);
    return elts;
}
