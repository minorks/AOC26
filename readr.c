#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_SIZE 80
#define ARRAY_MULTIPLIER 3

void cleanup(char **arr) {
    printf("I'm in the cleanup method!\n");

    printf("Cleaning up individual strings\n");
    for (int i=0;arr[i] != NULL; i++) {
        char *str = arr[i];
        printf("Cleaning up #%d: %s\n",i,str);
        free(arr[i]);
    }

    printf("Cleaning up pointer array\n");
    free(arr);
}

void print_all_entries(char **arr) {
    for (int i = 0; arr[i] != NULL; i++) {
        printf("The text at %d is: %s\n",i,arr[i]);
    }
}

int main(int argc, char *argv[]) {

    printf("Arguments entered: %d\n",argc);

    // Initialize an array of pointers to character arrays with initial
    // size ARRAY MULTIPLIER and initial count 0.
    int ct = 0;
    int max = ARRAY_MULTIPLIER;
    char **array = (char **)malloc(ARRAY_MULTIPLIER * sizeof(char *)); 
    if (array == NULL) {
        printf("Failed to allocate memory for array.");
        exit(1);
    }

    for (size_t i = 1; i < argc; i++) {

        if (ct >= max) {
            printf("Resizing to %d; printing all current entries:\n",2*max);
            print_all_entries(array);
            char **temp = realloc(array, 2*max*sizeof(char *));
            if (temp == NULL) {
                printf("Failed to reallocate memory for increased array size.");
                cleanup(array);
                exit(1);
            }
            max = 2*max;
            printf("Array expanded - new max entries is: %d\n",max);
        }

        // For each argument, create a pointer to a new area of memory
        // to receive the new string.
        char *ptr = (char *)malloc(MAX_BUF_SIZE);
        if (ptr == NULL) {
            printf("Failed to allocate memory for individual buffer at sequence %d.\n",(int) i);
            cleanup(array);
            exit(1);
        }

        // Read input from the user
        strcpy(ptr,argv[i]);
        array[ct] = ptr;
        printf("Added %s at space %d.\n",ptr,ct++);
    }

    printf("\n");
    print_all_entries(array);

    /*
    for (int i = 0; array[i] != NULL; i++) {
        printf("The text at %d is: %s\n",i,array[i]);
    }

    for (int i=0;array[i] != NULL; i++) {
        printf("Cleaning up string #%d\n",i);
        free(array[i]);
    }

    printf("Cleaning up master array\n");
    free(array);
    */

    cleanup(array);
    return 0;
}