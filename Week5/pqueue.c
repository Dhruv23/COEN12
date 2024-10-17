/*
Dhruv Patel 
Lab 5
5/30/2023
Program Description: A priority queue abstract data type using a binary heap implemented using an array
*/





#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#define PQ struct pqueue
PQ{
    int count;
    int length;
    void** data;
    int (*compare)();
};

//O(1)
//Function to be able to easily go to the left child of an item
static int left(int i){
    return (i*2)+1;
}
//O(1)
//Function to be able to easily go to the right child of an item
static int right(int i){
    return (i*2)+2;
}

//O(1)
//Function to be able to easily go to the parent of an item
static int parent(int i){
    return (i-1)/2;
}
//O(1)
//Create the Prio Queue/set the starting array size to 10
PQ *createQueue(int (*compare)()){
    PQ *pq = malloc(sizeof(PQ));
    assert(pq);
    pq->compare = compare;
    pq->count = 0;
    pq->length = 10;
    pq->data = malloc(sizeof(void*)*10);
    assert(pq->data);
    return pq;
}
//O(n)
//Increment through and destroy the prio queue
void destroyQueue(PQ *pq){
    assert(pq != NULL);
    for(int i = 0; i < pq->count; i++){
        free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
    return;
}
//O(1)
//Return the number of items in the queue
int numEntries(PQ *pq){
    assert(pq);
    return pq->count;
}
//O(logn)
//insert an item into the priority queue
void addEntry(PQ *pq, void *entry){
    assert(pq && entry);
    if(pq->count == pq->length){ //if count equals length, double the array size.
        pq->length *= 2;
        pq->data = realloc(pq->data, sizeof(void*)*pq->length);
    }
    int index = pq->count; 
    pq->data[index] = entry; //store data
    while(pq->count != 0 && (*pq->compare)(pq->data[parent(index)], pq->data[index]) > 0){//swap the child with the parent if the child is smaller than the parent
        void* storeData = pq->data[index];
        pq->data[index] = pq->data[parent(index)];
        pq->data[parent(index)] = storeData;
        index = parent(index);
    }
    pq->count++;//increase the count by one if you insert into the priority queue
    return;
}
//O(logn)
//remove an item from the priority queue
void *removeEntry(PQ *pq){
    assert(pq);
    void *deleted = pq->data[0];
    pq->data[0] = pq->data[pq->count-1];

    int x=0;
    
    while(left(x) <= pq->count-1 ){
        int small = left(x);
        if( right(x) <= pq->count-1 ){  
	            if( (*pq->compare)(pq->data[right(x)], pq->data[left(x)]) < 0 )
                    small =right(x);                       
        }
        if( (*pq->compare)(pq->data[x], pq->data[small]) < 0 ){//if parent smaller than childern
            break;
        }else{ //parent not smallest so swap
          void *temp = pq->data[x];
          pq->data[x] = pq->data[small];
          pq->data[small] = temp;
        }
        x =small;
    }
    pq->count--;
    return deleted;

}