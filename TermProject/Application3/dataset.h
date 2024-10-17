/*
 * Function:	dataset.h
 *
 * Copyright:	2023, Dhruv Patel
 *
 * Description:	This file contains the public function and type
 *		declarations for a linked list data type with the following functions.
 */
#ifndef DATASET_H
#define DATASET_H


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

# define LIST struct list
# define NODE struct node

LIST *createDataSet(void);

void destroyDataSet(LIST *lp);

void searchAge(LIST *lp, int age);

void searchID(LIST *lp, int id);

void addElt(LIST *lp, int id, int age);

void removeElt(LIST *lp, int id);

int maxAgeGap(LIST *lp);

#endif