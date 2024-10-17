/*
Dhruv Patel 
Lab 2
Final version on 4/17/2023
*/

//#include "set.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct set{
  char** string;
  int length;
  int count;
}SET;
SET *sp;

static int search(SET*, char*);

SET *createSet(int maxElts){ //creates a set with a max length of maxelts.
    SET *sp = malloc(sizeof(SET)); //allocate memory
    assert(sp != NULL); 
    sp->length = maxElts; //assign max length to maxelts from parent function
    sp->count = 0;
    sp->string = malloc(sizeof(char*)*maxElts); //allocate memory for the string datatype
    assert(sp->string != NULL);
    return sp;
}

void destroySet(SET *sp){ //deletes set pointed to by sp incrementally
    assert(sp !=NULL);
    int i;
    for(i = 0; i<sp->count; i++){
        free(sp->string[i]);
    }
    free(sp->string);
    free(sp);
}

int numElements(SET *sp){ //returns numer of elemebnts pointed to by count
    assert(sp !=NULL);
    return sp->count;
}


void addElement(SET *sp, char *elt){ //adds an element (at end) after ensuring that it doesnt already exist
    assert(sp !=NULL);
    if(search(sp, elt)==-1) {
        sp->string[sp->count] = strdup(elt);
        sp->count++;
    }
}

void removeElement(SET *sp, char *elt){ //removes element in sp pointed to by elt
    assert(sp !=NULL);
    int array_index = search(sp, elt);
    if(array_index >=0){
        free(sp->string[array_index]);
        sp->string[array_index] = sp->string[sp->count - 1]; //replaces deleted item with last item to fill in the gap
        sp->count--;

    }
}

char *findElement(SET *sp, char *elt){ //finds element in set sp pointed to by elt using search function
    assert(sp !=NULL);
    int array_index = search(sp, elt);
    if(array_index >=0){
        return sp->string[array_index];
    }
    else{
        return NULL;
    }
    
}

char **getElements(SET *sp){ //returns elements as an array 
    assert(sp !=NULL);
    char **string_output;
    int i;
    assert(string_output !=NULL);
    string_output = malloc(sizeof(char*)*sp->count);
    // for(i = 0; i<sp->count; i++){
    //     string_output[i] = sp->string[i];
    // }
    memcpy(string_output, sp->string, sizeof(char*)*sp->count);
    return string_output;
}

static int search(SET *sp, char *elt) { //sequential search function
    assert(sp!=NULL);
    for(int i=0; i<sp->count; i++) {
        if(strcmp(sp->string[i], elt) == 0){
            return i;
        }
    }
    return -1;
}
