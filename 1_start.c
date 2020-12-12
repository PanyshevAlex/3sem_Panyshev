#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#ifdef S_BLKSIZE
#define BL_SIZE S_BLKSIZE
#else 
#include <sys/param.h>
#define BL_SIZE DEV_BSIZE
#endif
int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Usage: %s some.file\n", argv[0]);
        return 1;
    }
    struct stat stat_buf;
    if (lstat(argv[1], &stat_buf) == -1){
        perror("Failed to stat");
        return 2;
    }
    printf("File: \"%s\"\n", argv[0]);
    printf("Type:  ");
    switch (stat_buf.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }
    printf("Size: %llu\n", (unsigned long long)stat_buf.st_size);
    printf("Used space: %llu\n", (unsigned long long)stat_buf.st_blocks * BL_SIZE);
    printf("UID: %d\n", stat_buf.st_uid);
    printf("GID: %d\n", stat_buf.st_gid);
    printf("atime: %ld sec %ld nanosec\n", stat_buf.st_atimespec.tv_sec, stat_buf.st_atimespec.tv_nsec);
    printf("mtime: %ld sec %ld nanosec\n", stat_buf.st_mtimespec.tv_sec, stat_buf.st_mtimespec.tv_nsec);
    printf("ctime: %ld sec %ld nanosec\n", stat_buf.st_ctimespec.tv_sec, stat_buf.st_ctimespec.tv_nsec);
    return 0;
}
