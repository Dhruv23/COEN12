#include <stdio.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

 
int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Invalid Input, add name of text file");
        return 0;
    }
    FILE *fp;
    int word_count = 0;
    char max_length[MAX_WORD_LENGTH];
    fp = fopen(argv[1], "r");
    while(fscanf(fp, "%s", max_length) == 1){
        word_count++;
    }
    printf("Word count is %d", word_count);
}