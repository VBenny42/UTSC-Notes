#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64 

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* POSIX.1 says each process has at least 20 file descriptors.
 * Three of those belong to the standard streams.
 * Here, we use a conservative estimate of 15 available;
 * assuming we use at most two for other uses in this program,
 * we should never run into any problems.
 * Most trees are shallower than that, so it is efficient.
 * Deeper trees are traversed fine, just a bit slower.
 * (Linux allows typically hundreds to thousands of open files,
 *  so you'll probably never see any issues even if you used
 *  a much higher value, say a couple of hundred, but
 *  15 is a safe, reasonable value.)
*/
#ifndef USE_FDS
#define USE_FDS 15
#endif

int sum = 0;

int list_entry(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{
    /* const char *const filename = filepath + pathinfo->base; */
    const double bytes = (double)info->st_size; /* Not exact if large! */
    struct tm mtime;
    sum += info->st_size;
    localtime_r(&(info->st_mtime), &mtime);

    printf("%04d-%02d-%02d %02d:%02d:%02d",
           mtime.tm_year+1900, mtime.tm_mon+1, mtime.tm_mday,
           mtime.tm_hour, mtime.tm_min, mtime.tm_sec);

    if (bytes >= 1099511627776.0)
        printf(" %9.3f TiB", bytes / 1099511627776.0);
    else
    if (bytes >= 1073741824.0)
        printf(" %9.3f GiB", bytes / 1073741824.0);
    else
    if (bytes >= 1048576.0)
        printf(" %9.3f MiB", bytes / 1048576.0);
    else
    if (bytes >= 1024.0)
        printf(" %9.3f KiB", bytes / 1024.0);
    else
        printf(" %9.0f B  ", bytes);

    if (typeflag == FTW_SL) {
        char   *target;
        size_t  maxlen = 1023;
        ssize_t len;

        while (1) {

            target = malloc(maxlen + 1);
            if (target == NULL)
                return ENOMEM;

            len = readlink(filepath, target, maxlen);
            if (len == (ssize_t)-1) {
                const int saved_errno = errno;
                free(target);
                return saved_errno;
            }
            if (len >= (ssize_t)maxlen) {
                free(target);
                maxlen += 1024;
                continue;
            }

            target[len] = '\0';
            break;
        }

        printf(" %s -> %s\n", filepath, target);
        free(target);

    } else
    if (typeflag == FTW_SLN)
        printf(" %s (dangling symlink)\n", filepath);
    else
    if (typeflag == FTW_F)
        printf(" %s\n", filepath);
    else
    if (typeflag == FTW_D || typeflag == FTW_DP)
        printf(" %s/\n", filepath);
    else
    if (typeflag == FTW_DNR)
        printf(" %s/ (unreadable)\n", filepath);
    else
        printf(" %s (unknown)\n", filepath);

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