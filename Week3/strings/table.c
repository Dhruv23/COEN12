/*
Program Description: An abstract data set for a string with the implementations described in set.h, using a hash table.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
# define EMPTY 0
# define FILLED 1
# define DELETED 2

//Create struct set with data, length, count
typedef struct set{
    char** data;
    int length;
    int count;
    char *flags;
}SET;
SET *sp;


//create a set with max capacity defined by MaxElts. return pointer to set.
//O(1)
SET *createSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp);
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(sizeof(char*) * maxElts);
    assert(sp->data);
    sp->flags=malloc(sizeof(char)*maxElts);
    for(int i=0;i<maxElts;i++){
        sp->flags[i]=EMPTY;
    }
    return sp;
}

//hash function
//O(logn)
unsigned strhash(char *s){
    unsigned hash = 0;
    while(*s != '\0'){
        hash = 31 * hash + *s ++;
    }
    return hash;
}

//delete set pointed to by sp.
//O(1)
void destroySet(SET *sp) {
    for(int i=0; i<sp->length; i++){
    if(sp->flags[i]==FILLED)
        free(sp->data[i]);
    }
    free(sp->flags);
    free(sp->data);
    free(sp);
}

//return count, number of elements in set sp
//O(1)
int numElements(SET *sp) {
    return sp->count;
}

//add an element to the set 
//O(n)
//search for the element and if it exists, return its position
// O(n)
static int search(SET *sp, char *elt, bool *found) {
    assert(sp);
    unsigned index = strhash(elt)%sp->length;
    bool firstDelete=true;
    int indexFirstDelete;
    if(sp->flags[index]==EMPTY){
        *found=false;
        return index;
    }
    else while(sp->flags[index]==FILLED||sp->flags[index]==DELETED){
        if(sp->flags[index]==DELETED){
            if(firstDelete){
                firstDelete=false;
                indexFirstDelete=index;
            }
        }
        else {
            if(strcmp(elt,sp->data[index])==0){
                *found=true;
                return index;
            }
        }
    index=(index+1)%sp->length;
    }
    *found=false;
    if(!firstDelete){
        return indexFirstDelete;
    }
    return index;
}
void addElement(SET *sp, char *elt) {
    assert(sp || elt);    
    bool found;
    int index = search(sp, elt, &found);
    if(found){
        return;
    }
    sp->flags[index]=FILLED;
    sp->data[index]=strdup(elt);
    sp->count++;
}

//delete an element from the set pointed to by sp 
//O(1)
void removeElement(SET *sp, char *elt) {
    bool found;
    int index = search(sp, elt, &found);
    if(found) {
        free(sp->data[index]);
        sp->flags[index]=DELETED;
        sp->count--;
    }
}
//find an element and return the data if its there, if not, return NULL.
//O(n)
char *findElement(SET *sp, char *elt) {
    assert(sp);
    bool found;
    int index = search(sp, elt, &found);
    if(found){
        return sp->data[index];
    }
    return NULL;
}

//make an array of elements from the set pointed to by sp 
//O(1)
char **getElements(SET *sp) {
    char **elts;
    elts = malloc(sizeof(char*)*sp->count);
    int j=0;
    for(int i=0; i<sp->length; i++) {
        if(sp->flags[i]==FILLED) {
            elts[j]=sp->data[i];
            j++;
        }
    }
    return elts;
}

