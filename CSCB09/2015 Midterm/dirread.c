#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int dircheck(const char *path) {
    if (chdir(path) == -1) {
        perror("chdir");
        return -1;
    }
    DIR *folder;
    folder = opendir(".");
    struct dirent *entry;
    struct stat filestat;
    if (folder == NULL) {
        fprintf(stderr, "Unable to read directory\n");
        return -1;
    }
    int sum = 0;
    while( (entry=readdir(folder)) )
    {
        // if (entry->d_type == DT_REG) {
            stat(entry->d_name, &filestat);
            sum += filestat.st_size;
        // }
    }
    return sum;
}

int main(int argc, char *argv[])
{
    printf("%d\n", dircheck(argv[1]));
}