/*
Dhruv Patel 
Lab 5
5/30/2023
Program Description: implement a huffman tree given a prio queue 
*/


#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

static NODE* mkNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCmp(NODE* np1, NODE* np2);

	int ascii[257];
	NODE* nodes[257];

int main(int argc, char* argv[])
{
	  if(argc == 2)
		{
	   	 puts("Missing and/or added insufficient number of files!");
	    	 return 0;
		}
  	  else
		{
 		FILE* fp = fopen(argv[1], "r");
 	 	if(fp == NULL)
		{
    		puts("File cannot be opened. Smh fam");
   	 
   		}
		 int x = getc(fp);
	  	while(x != EOF)
	  	 {
   		 ascii[x]++;
   		 x = getc(fp);
  		 }
 	 fclose(fp);
  
	}
  
 int i, j; 
 PQ *pq = createQueue(nodeCmp);
  for(i = 0; i < 256; i++)
  {
    if(ascii[i] > 0){
      nodes[i] = mkNode(ascii[i], NULL, NULL);
      addEntry(pq, nodes[i]);
    }
  }
  nodes[256] = mkNode(0, NULL, NULL);
  addEntry(pq, nodes[256]);
  while(numEntries(pq) > 1)
  {
    NODE* left = removeEntry(pq);
    NODE* right = removeEntry(pq);
    NODE* parent = mkNode(left->count + right->count, left, right);
    addEntry(pq, parent);
  }
  for( j = 0; j < 256; j++)
  { 
    if(nodes[j] != NULL){
      printf(isprint(j) ? "%c" : "%03o", j);
      printf(": %d x %d bits = %d bits\n", ascii[j], depth(nodes[j]), ascii[j]*depth(nodes[j]));
    }
  }
  pack(argv[1], argv[2], nodes);
  destroyQueue(pq);
  return 0;
}







//create a new node with a left and right side pointing at the parent 
static NODE* mkNode(int data, NODE* left, NODE* right)
{
  NODE* root = malloc(sizeof(NODE));
  assert(root);
  root->count = data;
  root->parent = NULL;
  if(left != NULL)
  {
    left->parent = root;
  }
  if(right != NULL){
    right->parent = root;
  }
  return root;
}





//return the height of the tree
static int depth(NODE* np)
{ 
  assert(np);
  if(np->parent == NULL){
    return 0;
  }
  return depth(np->parent) + 1;
}





//comapre which nodes are bigger 
static int nodeCmp(NODE* np1, NODE* np2)
{
  assert(np1 != NULL && np2 != NULL);
  return (np1->count < np2->count) ? -1 : (np1->count > np2->count);
}


