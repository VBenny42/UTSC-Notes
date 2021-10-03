#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int dircheck(const char *path, int *sum, struct stat *filestat, char *relative_path) {
    if (chdir(path) == -1) {
        perror("chdir");
        printf("%s\n", path);
        return -1;
    }
    DIR *folder;
    folder = opendir(".");
    struct dirent *entry;
    if (folder == NULL) {
        fprintf(stderr, "Unable to read directory\n");
        return -1;
    }
    while( (entry=readdir(folder)) )
    {   
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // printf("%s", entry->d_name);
        stat(entry->d_name, filestat);
        (*sum) += filestat->st_size;
        if (entry->d_type == DT_DIR) {
            sprintf(relative_path, "%s/%s", relative_path, entry->d_name);
            dircheck(relative_path, sum, filestat, relative_path);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    struct stat filestat;
    int sum = 0;
    char relative_path[1024];
    if (dircheck("/", &sum, &filestat, relative_path) == -1) {
        fprintf(stderr, "dircheck errror\n");
    }
    printf("%d\n", sum);
}