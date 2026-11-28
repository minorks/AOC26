#include <stdio.h>
#include <string.h>
#include "readr.h"

void getOptions() {
    printf("1: Read text file\n");
    printf("2: View text file\n");
    printf("q: Quit\n");
}

int* runModule(char *val, readText *data) {
    int toRet;
    switch(*val) {
        case 'q':
            return NULL;
        case '2':
            if (data == NULL) {
                printf("No data loaded.\n");
                break;
            }
            print_all_entries(data);
            toRet = 2;
            break;

        case '1':  
            printf("Enter a file name to read in: ");
            char file[120];
            if (fgets(file,sizeof(file),stdin) != NULL) {
                file[strcspn(file, "\n")] = '\0';
                readText temp = read(file);
                *data = temp;
            }
            toRet = 1;
            break;
        default:
            printf("Invalid input - try again!\n");
            toRet = -1;
    }
    int *ptr = &toRet;
    return ptr;
}

int main() {
    printf("Welcome to Kyle's Advent of Code program!\n");
    char resp[3];
    readText data;
    int* val;
    getOptions();

    while(1) {
        if(fgets(resp,sizeof(resp),stdin) != NULL) {
            resp[strcspn(resp, "\n")] = '\0';
            val = runModule(resp,&data);
            if (val == NULL) {
                printf("Exiting program!\n");
                return 0; // Exit program
            }
            getOptions();
        } else {return 1;}
    }
}