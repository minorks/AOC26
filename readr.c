#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readr.h"

void cleanup(readText* lst) {
    for (int i=0; i < lst->count; i++) {
        char *str = lst->myArray[i];
        free(lst->myArray[i]);
    }
    free(lst);
}

void print_all_entries(const readText *lst) {
    int ct = lst->count;
    for (int i = 0; i < ct; i++) {
        printf("The text at %d is: %s\n",i,lst->myArray[i]);
    }
}

readText extendArray(readText* lst, int* max) {
    printf("Resizing to %d; printing all current entries:\n",2*(*max));
    readText temp;
    temp.myArray = realloc(lst->myArray, 2*(*max)*sizeof(char *));
    if (temp.myArray == NULL) {
        printf("Failed to reallocate memory for increased array size.");
        cleanup(lst);
        exit(1);
    }

    // Success! Assign back to array.
    lst->myArray = temp.myArray;
    *max = 2*(*max);
    printf("Array expanded - new max entries is: %d\n",*max);
    return(*lst);
}

readText read(char *fName) {
    readText lst;

    // Initialize an array of pointers to character arrays with initial
    int max = ARRAY_MULTIPLIER;
    int* maxPtr = &max;
    lst.myArray = (char **)malloc(ARRAY_MULTIPLIER * sizeof(char *)); 
    //char **array = (char **)malloc(ARRAY_MULTIPLIER * sizeof(char *)); 
    if (lst.myArray == NULL) {
        printf("Failed to allocate memory for array.");
        exit(1);
    }
    int ct = 0;
    lst.count = ct;

    FILE *fp = fopen(fName, "r");
    if (fp == NULL) {
        printf("Invalid file; quitting.");
        exit(2);
    }

    char buff[MAX_BUF_SIZE];
    while (fgets(buff,sizeof(buff),fp) != NULL) {

        // Check to see if the array requires extension due to allocated size...
        if (lst.count >= max) {
            printf("Count is: %d; max is: %d\n",lst.count,*maxPtr);
            lst = extendArray(&lst,maxPtr);
        }

        // For each argument, create a pointer to a new area of memory
        // to receive the new string.
        char *ptr = (char *)malloc(MAX_BUF_SIZE);
        if (ptr == NULL) {
            printf("Failed to allocate memory for individual buffer at sequence %d.\n",lst.count);
            cleanup(&lst);
            exit(1);
        }

        // Read input - strip trailing newline character
        buff[strcspn(buff, "\n")] = '\0';
        strcpy(ptr,buff);
        lst.myArray[lst.count] = ptr;
        lst.count += 1;
    }

    return lst;
}

/*
int main(int argc,char* argv[]) {
    readText myArray = read(argv[1]);
    printf("\nPrinting all %d entries:\n",*myArray.count);
    print_all_entries(&myArray);
    printf("\n");
    cleanup(&myArray);
    printf("Finished!\n");
    return 0;
}
    */

/*
int* initialize_read() {
    int ct = 0;
    int* ctPtr = &ct;
    return ctPtr;
}
*/