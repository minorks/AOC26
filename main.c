#include <stdio.h>
#include <string.h>
#include "readr.h"

void getOptions() {
    printf("1: Read text file\n");
    printf("2: View text file\n");
    printf("q: Quit\n");
}

void* runModule(char* val, void* ptr) {
    switch(*val) {
        case 'q':
            return NULL;
        case '2':
            if (ptr == NULL) {
                printf("No data loaded in.\n");
                break;
            }
            print_all_entries((char**) ptr, int count)

        case '1':  
            printf("Enter a file name to read in: ");
            char file[120];
            if (fgets(file,sizeof(file),stdin) != NULL) {
                file[strcspn(file, "\n")] = '\0';
                int* ctPtr = initialize_read();
                return (read(file, ctPtr));
            }
            break;
    }
    printf("Invalid input - try again!\n");
    int toRet = -1;
    int* x = &toRet;
    return (x);
}

int main() {
    printf("Welcome to Kyle's Advent of Code program!\n");
    char resp[5];
    void* ptr;
    getOptions();

    while(1) {
        if(fgets(resp,sizeof(resp),stdin) != NULL) {
            resp[strcspn(resp, "\n")] = '\0';
            ptr = runModule(resp,ptr);
            if (ptr == NULL) {
                printf("Exiting program!\n");
                return 0; // Exit program
            }
            getOptions();
        } else {return 1;}
    }
}