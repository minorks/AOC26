#include <stdio.h>
#include <stdlib.h>

/*
Intent: array of pointers to character strings - i.e., individual
strings need not be collocated in memory.
*/

#define MAX_STR_SIZE 256

// Function to free memory associated with an array and its sub-elements
void clearArray(char** arr, int len) {
    for (size_t i = 0; i < len; i++) {
        free(arr[i]);
    }
    free(arr);
}

int slen(char* str){
    int len = 0;
    while (str[len]!='\0'){
        len++;
    }
    return(len-1);
}

int main(int argc, char *argv[]) {
    if (argc < 1) {
        printf("[file]");
        return 1;
    }

    // Initialize array at trivial size - say, 5
    int allocd = 5;
    char** str_arr = (char**)malloc(allocd * sizeof(char*));

    if (str_arr == NULL) {
        printf("Pointer array failed to initialize due to malloc fault; quitting");
        return 1;
    }

    // Open file as read-only
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Invalid file; quitting.");
        return 1;
    }

    // Create a buffer to hold lines as they are read in
    char buff[MAX_STR_SIZE];
    int ct = -1;
    while (fgets(buff,sizeof(buff),fp) != NULL) {
        
        // Resize the array if necessary
        if (++ct >= allocd) {
            int new_size = allocd*2;
            char** temp_arr = (char**)realloc(str_arr, new_size * sizeof(char*));
            if (temp_arr==NULL) {
                printf("Pointer array failed to initialize due to realloc fault; quitting");
                clearArray(str_arr,--ct);
                return 1;
            }
            str_arr = temp_arr;
            allocd = new_size;
            printf("Resized to %d\n",allocd);
        }

        // Make space for the next line
        str_arr[ct] = (char*)malloc(sizeof(buff));
        if (str_arr[ct]==NULL) {
            printf("Failed to create space for next line; quitting.");
            clearArray(str_arr,ct);
            fclose(fp);
            return 1;
        }
        str_arr[ct] = buff;
        printf("Added \"%s\" at %d\n", str_arr[ct], ct);
    }

    printf("Printing all lines read in:\n");
    printf("String: %s\n",str_arr[0]);
    printf("String: %s\n",str_arr[5]);

    /*
    for (int i = 0; i < ct; i++) {
        printf("Line %d is: %s\n", i, str_arr[i]);
    }
    */

    printf("Closing up!\n");
    clearArray(str_arr,ct);
    fclose(fp);
    return 0;
}