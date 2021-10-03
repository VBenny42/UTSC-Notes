#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64 

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef USE_FDS
#define USE_FDS 15
#endif

int sum = 0;

int list_entry(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{
    sum += info->st_size;
    return 0;
}


int list_directory_tree(const char *const dirpath)
{
    int result;

    /* Invalid directory path? */
    if (dirpath == NULL || *dirpath == '\0')
        return errno = EINVAL;

    result = nftw(dirpath, list_entry, USE_FDS, FTW_PHYS);
    if (result >= 0)
        errno = result;

    return errno;
}

int main(int argc, char *argv[])
{
    if (list_directory_tree("/")) {
        fprintf(stderr, "%s.\n", strerror(errno));
        return EXIT_FAILURE;
    }
    fprintf(stderr, "%d\n", sum);
    return EXIT_SUCCESS;
}