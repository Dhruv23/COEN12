/*
 * Function:	college.c
 *
 * Copyright:	06/3/2023, Dhruv Patel, COEN12
 *
 * Description:	This file contains the functions that test the dataset.c file as described
 * in the doc provided by the TA's
 */

#include "dataset.h"

int randID() {
    int number = rand() % 2 + 1;  // Generate a random number between 1 and 2

    return number;
}
int randAge(){
    int number = rand() % 13 + 18;  // Generate a random number between 18 and 30
    return number;
}
int randSearch(int maxID){
    int number = rand() % maxID + 0;
    return number;
}


int main(){
    srand(time(NULL));  // Seed the random number generator with the current time
    int i, studentID, prevID, studentAge, maxID, searchInput;
    prevID = 0;
    LIST* class;
    class = createDataSet();
    for(i = 0; i<1000; i++){
        studentID=prevID +randID();
        studentAge = randAge();
        prevID = studentID;
        addElt(class, studentID, studentAge);
        printf("Inserted Student with ID: %d and Age: %d\n", studentID, studentAge);
        if(i == 999){
            maxID = studentID; //used to have a bound when searching.
            printf("Max ID is %d \n", maxID);
        }
       
    }
    //printList(class);
    searchInput = randSearch(maxID);
    int searchAgeInput = randAge();
    searchAge(class, searchAgeInput);
    maxAgeGap(class);
    searchID(class, searchInput); 
    removeElt(class, searchInput);
    destroyDataSet(class);
    




}
