#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct stat filestat;
    if (argc != 3) {
        printf("Incorrect number of arguments\n");
        return -1;
    }
    if (stat(argv[2], &filestat) == -1) {
        perror("stat");
        return -1;
    }
    if (strcmp(argv[1], "-f") == 0) {
        (S_ISREG(filestat.st_mode)) ? (printf("File exists and is a plain file\n")) : printf("File exists but is not a plain file\n");
    }
    else if (strcmp(argv[1], "-d") == 0) {
        (S_ISDIR(filestat.st_mode)) ? (printf("File exists and is a directory\n")) : printf("File exists but is not a directory\n");
    }
    else if (strcmp(argv[1], "-s") == 0) {
        ((S_ISREG(filestat.st_mode)) && ((int)filestat.st_size > 0)) ? (printf("File exists, is a plain file and non-zero sized\n")) : printf("File exists but is not a plain file and non-zero sized\n");
    }
    return 0;
}