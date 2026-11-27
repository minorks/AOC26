#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readr.h"

void cleanup(char **arr, int count) {
    for (int i=0; i < count; i++) {
        char *str = arr[i];
        free(arr[i]);
    }
    free(arr);
}

void print_all_entries(char **arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("The text at %d is: %s",i,arr[i]);
    }
}

char** extendArray(char **arr,int *ct, int *max) {
    printf("Resizing to %d; printing all current entries:\n",2*(*max));
    char **temp = realloc(arr, 2*(*max)*sizeof(char *));
    if (temp == NULL) {
        printf("Failed to reallocate memory for increased array size.");
        cleanup(arr, (*ct)-1);
        exit(1);
    }

    // Success! Assign back to array.
    arr = temp;
    *max = 2*(*max);
    printf("Array expanded - new max entries is: %d\n",*max);
    return(arr);
}

char** read(char *fName, int* ctPtr) {
    // Initialize an array of pointers to character arrays with initial
    int max = ARRAY_MULTIPLIER;
    int* maxPtr = &max;
    char **array = (char **)malloc(ARRAY_MULTIPLIER * sizeof(char *)); 
    if (array == NULL) {
        printf("Failed to allocate memory for array.");
        exit(1);
        return NULL;
    }

    FILE *fp = fopen(fName, "r");
    if (fp == NULL) {
        printf("Invalid file; quitting.");
        exit(2);
        return NULL;
    }

    char buff[MAX_BUF_SIZE];
    while (fgets(buff,sizeof(buff),fp) != NULL) {

        // Check to see if the array requires extension due to allocated size...
        if (*ctPtr >= max) {
            printf("Count is: %d; max is: %d\n",*ctPtr,*maxPtr);
            array = extendArray(array,ctPtr,maxPtr);
        }

        // For each argument, create a pointer to a new area of memory
        // to receive the new string.
        char *ptr = (char *)malloc(MAX_BUF_SIZE);
        if (ptr == NULL) {
            printf("Failed to allocate memory for individual buffer at sequence %d.\n",*ctPtr);
            cleanup(array, *ctPtr);
            exit(1);
            return NULL;
        }

        // Read input
        strcpy(ptr,buff);
        array[*ctPtr] = ptr;
        *ctPtr += 1;
    }

    return array;
}

int* initialize_read() {
    int ct = 0;
    int* ctPtr = &ct;
    return ctPtr;
}

/*
int main(int argc, char *argv[]) {
    //int ct = 0;
    //int* ctPtr = &ct;

    int* ctPtr = initialize_read();
    char **myArray = read(argv[1], ctPtr);
    printf("\nPrinting all %d entries:\n",*ctPtr);
    print_all_entries(myArray,*ctPtr);
    printf("\n");
    cleanup(myArray, *ctPtr);
    printf("Finished!\n");
    return 0;
}
    */