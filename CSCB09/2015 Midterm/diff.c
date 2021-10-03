#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define MAX_STR 1000

int main(int argc, char *argv[])
{
    char file1[MAX_STR], file2[MAX_STR];
    FILE *f1, *f2;
    if ( ((f1 = fopen(argv[1], "r")) == NULL) || ((f2 = fopen(argv[2], "r")) == NULL) ) {   // Opens both files from args and checks for errors
        fprintf(stderr, "Error reading file\n");
        return -1;
    }
    // Uses fgets to read from file, and if fgets fails, puts '\0' as the first element of array
    if (( (fgets(file1, MAX_STR, f1) == NULL) && (file1[0] = '\0')) || ((fgets(file2, MAX_STR, f2) == NULL) && (file2[0] = '\0')) ) {
        fprintf(stderr, "File could not be read");
    }
    if (strcmp(file1, file2) == 0) {
        return 0;
    }
    else if (file1[0] == '\0') {
        printf("0a1\n> %s", file2);
    }
    else if (file2[0] == '\0') {
        printf("1d0\n< %s", file1);
    }
    else {
        printf("1c1\n< %s---\n> %s", file1, file2);
    }
    return 0;
}