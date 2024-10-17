/*
Program Description: An abstract data set for a generic data type with the implementations described in set.h.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

//Create struct set with data, length, count, compare, hash
typedef struct set{
    void **data;
    int length;
    int count;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
}SET;
SET *sp;


//create a set with max capacity defined by MaxElts. return pointer to set.
//O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    assert(compare && hash);

    sp = malloc(sizeof(SET));
    assert(sp);
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data);
    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (int i=0; i<maxElts; i++){
        sp->flags[i] = EMPTY;
    }
    return sp;
}

//delete set pointed to by sp.
//O(1)
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->flags);
    free(sp->data);
    free(sp);
}

//return count, number of elements in set sp
//O(1)
int numElements(SET *sp) {
    assert(sp);
    return sp->count;
}

//add an element to the set 
//O(n)
void addElement(SET *sp, void *elt) {
    assert(sp && elt);
    bool found;
    int index = search(sp, elt, &found);
    if(!found) {
        assert(sp->count < sp->length);
        sp->data[index] = elt;
        sp->flags[index] = FILLED;
        sp->count++;
    }
}

//delete an element from the set pointed to by sp 
//O(1)
void removeElement(SET *sp, void *elt) {
    bool found;
    int index = search(sp, elt, &found);
    assert(sp && elt);
    if(found) {
        sp->flags[index] = DELETED;
        sp->count--;
    }
}

//find an element and return the data if its there, if not, return NULL.
//O(n)
void *findElement(SET *sp, void *elt) {
    bool found;
    assert(sp && elt);
    int index = search(sp, elt, &found);
    if(found){
        return sp->data[index];
    }
    else{
        return NULL;
    }
}

//make an array of elements from the set pointed to by sp 
//O(n)
void *getElements(SET *sp) {
    void **elts;
    elts = malloc(sizeof(void*)*sp->count);
    int j=0;
    for(int i=0; i<sp->length; i++) {
        if(sp->flags[i]==FILLED) {
            elts[j]=sp->data[i];
            j++;
        }
    }
    return elts;
}

//search for the element and if it exists and return its position.
//O(n)
static int search(SET *sp, void *elt, bool found) {
    assert(sp);
    int exists, index;
    exists = -1;
    int start = (*sp->hash)(elt) % sp->length;
    for(int i=0; i<sp->length; i++) {
        index = (start + i) % sp->length;
        if(sp->flags[index] == EMPTY) {
            found = false;
            if(exists != -1){
                return exists;
            }
            else{
                return index;
            }
        }
        else if (sp->flags[index] == DELETED) {
            if(exists == -1)
                exists = index;
        }
        else if ((*sp->compare)(sp->data[index], elt) == 0) {
            found = true;
            return index;
        }
    }
    found = false;
    return exists;
    }
