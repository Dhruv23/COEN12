# include "dataset.h"
/*
* File: dataset.c
* Copyright: Dhruv Patel, 06/04/2023
* Description: This file implements a circular doubly linked list data type in C. 
* The list is sorted based on the age of the students in ascending order.
*/

//define the Node structure
NODE{
    int studentID;
    int studentAge; 
    NODE* next;
    NODE* prev;
};

//define the list structure
LIST{
    NODE* head;
    int count;
};


// Description: Creates an empty list.
// Big O Runtime: O(1)
LIST* createDataSet(void) {
    LIST* lp = malloc(sizeof(LIST));
    assert(lp);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}


// Description: Destroys the list and frees the memory.
// Big O Runtime: O(n), where n is the number of students in the list.
void destroyDataSet(LIST* lp) {
    assert(lp);
    NODE* deleting = lp->head;
    NODE* next;
    do {
        next = deleting->next;
        free(deleting);
        deleting = next;
    } while (deleting != lp->head);
    free(lp);
    printf("List deleted \n");
}


// Description: Searches for students with a specific age and prints their data.
// Big O Runtime: O(n), where n is the number of students in the list.
void searchAge(LIST* lp, int age) {
    NODE* current = lp->head->next;
    while (current != lp->head) {
        if (current->studentAge == age) {
            printf("Student Found!!! Student ID: %d, Age: %d\n", current->studentID, current->studentAge);
        }
        current = current->next;
    }
}


// Description: Searches for a student with a specific ID and prints their data.
// Big O Runtime: O(n), where n is the number of students in the list.
void searchID(LIST* lp, int id) {
    NODE* current = lp->head->next;
    while (current != lp->head) {
        if (current->studentID == id) {
            printf("Student ID: %d, Age: %d\n", current->studentID, current->studentAge);
            return;
        }
        current = current->next;
    }
    printf("Student with ID %d not found!\n", id);
}


// Description: Adds a new student to the list in a sorted manner based on age.
// Big O Runtime: O(n), where n is the number of students in the list.
void addElt(LIST* lp, int id, int age) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->studentID = id;
    newNode->studentAge = age;
    if (lp->count == 0) {
        newNode->next = lp->head;
        newNode->prev = lp->head;
        lp->head->next = newNode;
        lp->head->prev = newNode;
    } else {
        NODE* current = lp->head->next;
        while (current != lp->head && current->studentAge < age) {
            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    lp->count++;
}


// Description: Removes a student with a specific ID from the list.
// Big O Runtime: O(n), where n is the number of students in the list.
void removeElt(LIST* lp, int id) {
    assert(lp);
    NODE* temp = lp->head->next;
    for (int i = 0; i < lp->count; i++) {
        if (temp->studentID == id) {
            printf("\nStudent found with ID of %d and age %d. Deleting...\n", id, temp->studentAge);
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            printf("Student Deleted. \n\n");
            lp->count--;
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d does not exist, nothing to delete. \n", id);
}


// Description: Calculates and returns the maximum age gap between students in the list.
// Big O Runtime: O(1)
int maxAgeGap(LIST* lp) {
    if (lp->count < 2) {
        return 0; // Not enough students in the list
    }
    int maxGap = lp->head->prev->studentAge - lp->head->next->studentAge;
    printf("\nMinimum age is %d, Maximum age is %d, Max Age gap is %d \n", lp->head->prev->studentAge, lp->head->next->studentAge, maxGap);
    return maxGap;
}
