#include "dataset.h"
/*
 * Function:	dataset.c
 *
 * Copyright:	06/3/2023, Dhruv Patel, COEN12
 *
 * Description:	This code defines a data structure for managing a list of students, where each student is 
 * represented by a NODE structure. 
 */


//Defines the node student

NODE{
    int age;
    int studentID;
    int filled;
};

//Defines the list that holds data for all students.
LIST{
    NODE** student;
    int count;
    int length;
};


// Description: Creates a list that holds data for all students.
// Big O Runtime: O(n), where n = maxStudents
LIST* createDataSet(int maxStudents){
    int i;
    LIST *lp = malloc(sizeof(LIST));
    assert(lp);
    lp->length = maxStudents;
    int studentsize = sizeof(NODE*) * maxStudents; //each student needs memory for one Node, so the whole class is that times maxStudents
    lp->student = malloc(studentsize);
    assert(lp->student);
    for(i=0; i<lp->length; i++){
        lp->student[i] = malloc(sizeof(NODE));
        lp->student[i]->filled = 0;
        assert(lp->student[i]);
    }
    return lp;
}


// Description: Deletes the list that holds data for all students and frees the memory.
// Big O Runtime: O(n), where n = maxStudents
void destroyDataSet(LIST *lp){
    printf("Destroying Set \n");
    if (lp != NULL) {
        if (lp->student != NULL) {
            for (int i = 0; i < lp->length; i++) {
                if (lp->student[i] != NULL) {
                    free(lp->student[i]);
                }
            }
            free(lp->student);
        }
        free(lp);
    }
    printf("Set Destroyed \n\n");
}

// Description: Searches the list by ID to see if a student exists and prints their data.
// Big O Runtime: O(1)
int searchID(LIST * lp, int studentID){
    assert(lp != NULL);
    printf("Searching for ID: %d\n", studentID);
    if(lp->student[studentID]->filled == 1){
        printf("Student Found! Data listed below: \nStudent Age: %d\n Student ID: %d \n", lp->student[studentID]->age, studentID);
        return studentID;
    }
    else{
        printf("Student with ID %d Not Found :( \n", studentID);
    }
    return -1;
}


// Description: Inserts a new student element at the index of the ID.
// Big O Runtime: O(1)
void addElt(LIST * lp, int studentID, int studentAge){
    assert(lp);
    lp->student[studentID]->studentID = studentID;
    lp->student[studentID]->age = studentAge;
    lp->count++;
    lp->student[studentID]->filled = 1; 
    printf("Student Added with ID of %d and age %d \n", studentID, studentAge);
}


// Description: Searches the list for the element with the given ID and deletes it.
// Big O Runtime: O(1)
void removeElt(LIST* lp, int studentID) {
    assert(lp);
    int index = searchID(lp, studentID);
    if (index == -1) {
        printf("ID not found, try entering a valid ID\n");
    } else {
        printf("\nStudent Deleted. Data listed below: \nStudent Age: %d\n Student ID: %d \n", lp->student[studentID]->age, studentID);
        free(lp->student[index]);
        lp->student[index] = NULL; //Set the pointer to NULL after freeing the memory to ensure no Double Free errors.
        lp->count--;
    }
}
