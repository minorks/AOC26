#pragma once

#define MAX_BUF_SIZE 128
#define ARRAY_MULTIPLIER 3

void cleanup(char **arr, int* count);
void print_all_entries(char **arr, int count);
char** extendArray(char **arr,int *ct, int *max);
char** read(char *fName, int* ctPtr);