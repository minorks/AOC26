#pragma once

#define MAX_BUF_SIZE 128
#define ARRAY_MULTIPLIER 3

/**
* Struct representing a (dynamic) array of pointers
* to character pointers.
* @param myArray - the array itself
* @param count - the number of pointers in myArray
 */
typedef struct {
    char** myArray;
    int* count;
} readText;

/**
* Frees all memory allocated during the reading process, including
* for every string and also for the overarching array.
* @param arr A pointer to the beginning of an array of pointers to character arrays.
* @param count The number of pointers in the array arr.
 */
void cleanup(readText *lst);

void print_all_entries(readText *lst);
readText extendArray(readText *arr, int *max);
readText read(char *fName);
//int* initialize_read();