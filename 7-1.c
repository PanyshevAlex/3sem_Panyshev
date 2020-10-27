#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

int fcp(char *source_path, char  *target_dir_path, char *file_name)
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
    char target_path[PATH_MAX];
    snprintf(target_path, sizeof(target_path), "%s/%s", target_dir_path, file_name);
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
    struct timespec am_time[2] = {{stat_buf.st_atime, 0},{stat_buf.st_mtime, 0}};

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
    if (futimens(dst_fd, am_time) == -1)
    {
        perror("Failed to futimens");
        return -1;
    }
    close(src_fd);
    close(dst_fd);
    return 1;
}

void getname(char *path, char *name)
{
    int i, len = strlen(path); 
    
    for(; len > 0 && *(path+len) != '/'; len--);

    for(i = 0, len++; *(path+len) != 0;len++)  
    name[i++] = *(path+len);
    name[i] = 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s [source dir] [target dir]", argv[1]);
        return 1;
    }
    char dirname[20];
    getname(argv[1], dirname);
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
    char target_path[PATH_MAX];
    snprintf(target_path, sizeof(target_path), "%s/%s", argv[2], dirname);
    if (mkdir(target_path, 0755) == -1)
    {
        perror("Failed to mkdir:");
        return -1;
    }



    struct dirent *dir;
    while ((dir = readdir(dir_str)) != NULL)
    {
        char source_path[PATH_MAX];
        snprintf(source_path, sizeof(source_path), "%s/%s", argv[1], dir->d_name);
        if (fcp(source_path, target_path, dir->d_name) == -1)
        {
            perror("Failed to copy ");
        }
        else
            printf("%s has been copied\n", dir->d_name);
    }


    close(dir_fd);
    closedir(dir_str);
    return 1;
}
