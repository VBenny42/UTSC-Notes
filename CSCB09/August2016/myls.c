#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    DIR *directory = opendir(".");
    if (directory == NULL) {
        fprintf(stderr, "Directory could not be opened\n");
        return 1;
    }
    struct dirent *entry;
    entry = readdir(directory);
    while (entry != NULL) {
        if ((entry->d_type == DT_DIR) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
            switch (fork()) {
                case -1:
                {
                    perror("fork");
                    exit(1);
                    break;
                }
                case 0:
                {
                    execlp("ls", "ls", entry->d_name, (char *) NULL);
                    fprintf(stderr, "ERROR: exec should not return \n"); // This line is only reached when exec fails somehow
                    break;
                }
                default:
                {   
                    int s;
                    // Waits for child to finish
                    wait(&s);
                    break;
                }
            }
        }
        entry = readdir(directory);
    }
    return 0;
}
