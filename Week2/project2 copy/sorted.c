/*
Dhruv Patel 
Lab 2
Final version on 4/17/2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


typedef struct set{//define abstract data type as a struct with ints length and count, char pointer string
  int length;
  int count;
  char** string;
}SET;
SET *sp;

static int binsearch(SET*, char*); //define binary search function as it isnt in the .h file
/*
Most functions below share functionality with unsorted.c so are copy pasted with minor changes to accomodate a sorted array
*/

SET *createSet(int maxElts) { //returns a pointer to a dataset with max capacity of maxElts
    SET *sp = malloc(sizeof(SET)); //allocate memory
    assert(sp!=NULL);
    sp->length = maxElts; //set max lenght to maxelts defined by parent functions
    sp->count = 0;
    sp->string = malloc(sizeof(char*)*maxElts); //assign memory of size maxelts for string datatype
    assert(sp->string!=NULL);
    return sp;
}

void destroySet(SET *sp) { //removes set sp from memory
    assert(sp!=NULL);
    for(int i=0; i<sp->count; i++){
        free(sp->string[i]); //increment through sp and free all strings
    }
    free(sp->string); //free pointer to string
    free(sp); //free pointer to set
}

//return the number of elements in the set pointed to by sp
int numElements(SET *sp) {
    assert(sp !=NULL);
    return sp->count;
}


void addElement(SET *sp, char *elt) { //add elt to set pointed by sp. 
    assert(sp !=NULL);  
    if(binsearch(sp, elt) == -1) { //makes sure elt is already not in set using binary search
        int i = sp->count; //set i equal to number of entries in set sp
        while(i > 0 && strcmp(sp->string[i-1], elt) > 0) { //while loop to increment through the set and insert string in correct index
            sp->string[i] = strdup(sp->string[i-1]);
            i--;
        }
        sp->string[i] = strdup(elt); //assign elt into the right element and increment count
        sp->count++;
    }  
}


void removeElement(SET *sp, char *elt) { //remove elt from set
    assert(sp !=NULL);
    int index = binsearch(sp, elt); //make sure element is in array 
    if(index >= 0) { //if elt is in array
        
    for(int i=index+1; i<sp->count; i++){
        sp->string[i-1] = sp->string[i]; //move other elements up to fill blank space
    }
        
    sp->count--;
    }
}


char *findElement(SET *sp, char *elt) {//find elt in set sp, else return null
    assert(sp !=NULL);
    int index = binsearch(sp, elt); //make sure element is in aray
    if(index >= 0){
        return sp->string[index]; //if element is in array return element.
    }   
    else{
        return NULL;
    }
    
}


char **getElements(SET *sp) {//make an array of elements from set sp 
    assert(sp!=NULL);
    char **elts;
    assert(elts != NULL);
    elts = malloc(sizeof(char*)*sp->count);
    memcpy(elts, sp->string, sizeof(char*)*sp->count);
    return elts;
}


static int binsearch(SET *sp, char *elt) {//binary search for elements and return index, else return -1.
    assert(sp != NULL);
    int high = sp->count-1;
    int low = 0;
    int middle;
    while(high >= low) {
        middle = (high+low)/2;
        int temp = strcmp(sp->string[middle], elt);
        if(temp == 0){
            return middle;
        } 
        else if(temp > 0){
            high = middle-1;
        }    
        else if(temp < 0){
            low = middle+1;
        } 
    }
    return -1;
}
