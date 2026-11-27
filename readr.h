#pragma once

#define MAX_BUF_SIZE 128
#define ARRAY_MULTIPLIER 3
/**
* Frees all memory allocated during the reading process, including
* for every string and also for the overarching array.
* @param arr A pointer to the beginning of an array of pointers to character arrays.
* @param count The number of pointers in the array arr.
 */
void cleanup(char **arr, int count);

void print_all_entries(char **arr, int count);
char** extendArray(char **arr,int *ct, int *max);
char** read(char *fName, int* ctPtr);
int* initialize_read();