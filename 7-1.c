#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

int regfilecp(char *source_path, char  *target_dir_path, char *file_name)
{
    int src_fd = open(source_path, O_RDONLY);
    if (src_fd == -1)
    {
        perror("Failed to open source file:");
        return -1;
    }
    struct stat stat_buf;
     if (lstat(source_path, &stat_buf) == -1)
    {
        perror("Failed to stat");
        return -1;
    }
    char *target_path;
    if (asprintf(&target_path, "%s/%s", target_dir_path, file_name))
    {
        printf("Failed to asprintf: Insufficient storage space is available.");
        return 1;
    }
    int dst_fd = open(target_path, O_WRONLY|O_CREAT|O_TRUNC, stat_buf.st_mode);
    if (dst_fd == -1){
        perror("Failed to open target file:");
        return -1;
    }
    if (fchmod(dst_fd, stat_buf.st_mode) == -1)
    {
        perror("Failed to fchmod");
        return -1;
    }
#ifdef __APPLE__
    struct timespec am_time[2] = {stat_buf.st_atimespec,stat_buf.st_mtimespec};
#else
    struct timespec am_time[2] = {stat_buf.st_atim,stat_buf.st_mtim};
#endif
    while (1){
        uint8_t buf[4096];
        ssize_t buf_size = read(src_fd, buf, sizeof(buf));

        if (buf_size == -1){
            perror("Failed to read a block");
            close(src_fd);
            close(dst_fd);
        }
        if (buf_size == 0){
            break;
        }
        size_t local_buf_size = (size_t)buf_size;
        size_t bytes_written = 0;
        while (bytes_written < local_buf_size){
            ssize_t write_result = write(dst_fd, &buf[bytes_written], local_buf_size - bytes_written);
            fsync(dst_fd);
            if (write_result == -1){
                perror("Failed to write");
                close(src_fd);
                close(dst_fd);
                return -1;
            }
            bytes_written += (size_t)write_result;
        }

    }
    int err = 0;
    if (fsync(dst_fd))
    {
        perror("Failed to fsync");
        err = -1;
    }
    if (futimens(dst_fd, am_time) == -1)
    {
        perror("Failed to futimens");
        err = -1;
    }
    close(src_fd);
    close(dst_fd);
    return err;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s source dir target dir", argv[1]);
        return 1;
    }
    char *dirname;
    dirname = strchr(argv[1], '/');
    DIR *dir_str = opendir(argv[1]);
    if (dir_str == NULL)
    {
        perror("Failed to opendir");
        return -1;
    }
   
    int dir_fd;
    if ((dir_fd = dirfd(dir_str)) == -1)
    {
        perror("Failed to dirfd: ");
        return -1;
    }
    char *target_path;
    if (asprintf(&target_path, "%s/%s", target_dir_path, file_name))
    {   
        printf("Failed to asprintf: Insufficient storage space is available.");
        return 1;
    } 
    if (mkdir(target_path, 0755) == -1)
    {
        perror("Failed to mkdir:");
        return -1;
    }



    struct dirent *dir;
    while ((dir = readdir(dir_str)) != NULL)
    {
        char *source_path;
        struct stat stat_buf;
        asprintf(&source_path, "%s/%s", argv[1], dir->d_name);
        if (lstat(source_path, &stat_buf) == -1)
        {
            perror("Failed to lstat:");
            continue;
        }
        if (S_ISREG(stat_buf.st_mode))
        {
            if (regfilecp(source_path, target_path, dir->d_name) == -1)
            {
                perror("Failed to copy ");
            }
            else
                printf("%s has been copied\n", dir->d_name);
        }
        else if (S_ISDIR(stat_buf.st_mode))
        {
            char *target_dir_path;
            asprintf(&target_dir_path, "%s/%s", target_path, dir->d_name);
            if (mkdir(target_dir_path, stat_buf.st_mode) == -1)
            {
                printf("%s has been copied\n", dir->d_name);
            }
        }
    }


    close(dir_fd);
    closedir(dir_str);
    return 1;
}
